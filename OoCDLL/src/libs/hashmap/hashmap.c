// Copyright 2020 Joshua J Baker. All rights reserved.
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file.

#pragma warning(suppress:4244)
#pragma warning(suppress:4334)
#pragma warning(suppress:6297)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include "hashmap.h"

#include "defs/d_common.h"

#define GROW_AT   0.60
#define SHRINK_AT 0.10

static void *(*__malloc)(Size_t) = NULL;
static void *(*__realloc)(void *, Size_t) = NULL;
static void (*__free)(void *) = NULL;

// hashmap_set_allocator allows for configuring a custom allocator for
// all hashmap library operations. This function, if needed, should be called
// only once at startup and a prior to calling hashmap_new().
void hashmap_set_allocator(void *(*malloc)(Size_t), void (*free)(void *)) {
    __malloc = malloc;
    __free = free;
}

struct bucket {
    u64 hash : 48;
    u64 dib : 16;
};

void hashmap_set_grow_by_power(Hashmap_t *map, Size_t power) {
    map->growpower = power < 1 ? 1 : power > 16 ? 16 : power;
}

static struct bucket *bucket_at0(void *buckets, Size_t bucketsz, Size_t i) {
    return (struct bucket *) (((char *) buckets) + (bucketsz * i));
}

static struct bucket *bucket_at(Hashmap_t *map, Size_t index) {
    return bucket_at0(map->buckets, map->bucketsz, index);
}

static void *bucket_item(struct bucket *entry) {
    return ((char *) entry) + sizeof(struct bucket);
}

static u64 clip_hash(u64 hash) {
    return hash & 0xFFFFFFFFFFFF;
}

static u64 get_hash(Hashmap_t *map, const void *key) {
    return clip_hash(map->hash(key, map->seed0, map->seed1));
}

// hashmap_new_with_allocator returns a new hash map using a custom allocator.
// See hashmap_new for more information information
Hashmap_t *hashmap_new_with_allocator(void *(*_malloc)(Size_t),
    void *(*_realloc)(void *, Size_t), void (*_free)(void *),
    Size_t elsize, Size_t cap, u64 seed0, u64 seed1,
    u64(*hash)(const void *item, u64 seed0, u64 seed1),
    int (*compare)(const void *a, const void *b, void *udata),
    void (*elfree)(void *item),
    void *udata) {
    _malloc = _malloc ? _malloc : __malloc ? __malloc : malloc;
    _realloc = _realloc ? _realloc : __realloc ? __realloc : realloc;
    _free = _free ? _free : __free ? __free : free;
    Size_t ncap = 16;
    if (cap < ncap) {
        cap = ncap;
    }
    else {
        while (ncap < cap) {
            ncap *= 2;
        }
        cap = ncap;
    }
    // printf("%d\n", (int)cap);
    Size_t bucketsz = sizeof(struct bucket) + elsize;
    while (bucketsz & (sizeof(uintptr_t) - 1)) {
        bucketsz++;
    }
    // hashmap + spare + edata
    Size_t size = sizeof(Hashmap_t) + bucketsz * 2;
    Hashmap_t *map = _malloc(size);
    if (!map) {
        return NULL;
    }
    memset(map, 0, sizeof(Hashmap_t));
    map->elsize = elsize;
    map->bucketsz = bucketsz;
    map->seed0 = seed0;
    map->seed1 = seed1;
    map->hash = hash;
    map->compare = compare;
    map->elfree = elfree;
    map->udata = udata;
    map->spare = ((char *) map) + sizeof(Hashmap_t);
    map->edata = (char *) map->spare + bucketsz;
    map->cap = cap;
    map->nbuckets = cap;
    map->mask = map->nbuckets - 1;
    map->buckets = _malloc(map->bucketsz * map->nbuckets);
    if (!map->buckets) {
        _free(map);
        return NULL;
    }
    memset(map->buckets, 0, map->bucketsz * map->nbuckets);
    map->growpower = 1;
    map->growat = map->nbuckets * GROW_AT;
    map->shrinkat = map->nbuckets * SHRINK_AT;
    map->malloc = _malloc;
    map->realloc = _realloc;
    map->free = _free;
    return map;
}

// hashmap_new returns a new hash map. 
// Param `elsize` is the size of each element in the tree. Every element that
// is inserted, deleted, or retrieved will be this size.
// Param `cap` is the default lower capacity of the hashmap. Setting this to
// zero will default to 16.
// Params `seed0` and `seed1` are optional seed values that are passed to the 
// following `hash` function. These can be any value you wish but it's often 
// best to use randomly generated values.
// Param `hash` is a function that generates a hash value for an item. It's
// important that you provide a good hash function, otherwise it will perform
// poorly or be vulnerable to Denial-of-service attacks. This implementation
// comes with two helper functions `hashmap_sip()` and `hashmap_murmur()`.
// Param `compare` is a function that compares items in the tree. See the 
// qsort stdlib function for an example of how this function works.
// The hashmap must be freed with hashmap_free(). 
// Param `elfree` is a function that frees a specific item. This should be NULL
// unless you're storing some kind of reference data in the hash.
Hashmap_t *hashmap_new(Size_t elsize, Size_t cap, u64 seed0,
    u64 seed1,
    u64(*hash)(const void *item, u64 seed0, u64 seed1),
    int (*compare)(const void *a, const void *b, void *udata),
    void (*elfree)(void *item),
    void *udata) {
    return hashmap_new_with_allocator(NULL, NULL, NULL, elsize, cap, seed0,
        seed1, hash, compare, elfree, udata);
}

static void free_elements(Hashmap_t *map) {
    if (map->elfree) {
        for (Size_t i = 0; i < map->nbuckets; i++) {
            struct bucket *bucket = bucket_at(map, i);
            if (bucket->dib) map->elfree(bucket_item(bucket));
        }
    }
}

// hashmap_clear quickly clears the map. 
// Every item is called with the element-freeing function given in hashmap_new,
// if present, to free any data referenced in the elements of the hashmap.
// When the update_cap is provided, the map's capacity will be updated to match
// the currently number of allocated buckets. This is an optimization to ensure
// that this operation does not perform any allocations.
void hashmap_clear(Hashmap_t *map, bool update_cap) {
    map->count = 0;
    free_elements(map);
    if (update_cap) {
        map->cap = map->nbuckets;
    }
    else if (map->nbuckets != map->cap) {
        void *new_buckets = map->malloc(map->bucketsz * map->cap);
        if (new_buckets) {
            map->free(map->buckets);
            map->buckets = new_buckets;
        }
        map->nbuckets = map->cap;
    }
    memset(map->buckets, 0, map->bucketsz * map->nbuckets);
    map->mask = map->nbuckets - 1;
    map->growat = map->nbuckets * 0.75;
    map->shrinkat = map->nbuckets * 0.10;
}

static bool resize0(Hashmap_t *map, Size_t new_cap) {
    Hashmap_t *map2 = hashmap_new_with_allocator(map->malloc, map->realloc,
        map->free, map->elsize, new_cap, map->seed0, map->seed1, map->hash,
        map->compare, map->elfree, map->udata);
    if (!map2) return false;
    for (Size_t i = 0; i < map->nbuckets; i++) {
        struct bucket *entry = bucket_at(map, i);
        if (!entry->dib) {
            continue;
        }
        entry->dib = 1;
        Size_t j = entry->hash & map2->mask;
        while (1) {
            struct bucket *bucket = bucket_at(map2, j);
            if (bucket->dib == 0) {
                memcpy(bucket, entry, map->bucketsz);
                break;
            }
            if (bucket->dib < entry->dib) {
                memcpy(map2->spare, bucket, map->bucketsz);
                memcpy(bucket, entry, map->bucketsz);
                memcpy(entry, map2->spare, map->bucketsz);
            }
            j = (j + 1) & map2->mask;
            entry->dib += 1;
        }
    }
    map->free(map->buckets);
    map->buckets = map2->buckets;
    map->nbuckets = map2->nbuckets;
    map->mask = map2->mask;
    map->growat = map2->growat;
    map->shrinkat = map2->shrinkat;
    map->free(map2);
    return true;
}

static bool resize(Hashmap_t *map, Size_t new_cap) {
    return resize0(map, new_cap);
}

// hashmap_set_with_hash works like hashmap_set but you provide your
// own hash. The 'hash' callback provided to the hashmap_new function
// will not be called
const void *hashmap_set_with_hash(Hashmap_t *map, const void *item,
    u64 hash) {
    hash = clip_hash(hash);
    map->oom = false;
    if (map->count == map->growat) {
        if (!resize(map, map->nbuckets * (1 << map->growpower))) {
            map->oom = true;
            return NULL;
        }
    }

    struct bucket *entry = map->edata;
    entry->hash = hash;
    entry->dib = 1;
    void *eitem = bucket_item(entry);
    memcpy(eitem, item, map->elsize);

    void *bitem;
    Size_t i = entry->hash & map->mask;
    while (1) {
        struct bucket *bucket = bucket_at(map, i);
        if (bucket->dib == 0) {
            memcpy(bucket, entry, map->bucketsz);
            map->count++;
            return NULL;
        }
        bitem = bucket_item(bucket);
        if (entry->hash == bucket->hash && (!map->compare ||
            map->compare(eitem, bitem, map->udata) == 0)) {
            memcpy(map->spare, bitem, map->elsize);
            memcpy(bitem, eitem, map->elsize);
            return map->spare;
        }
        if (bucket->dib < entry->dib) {
            memcpy(map->spare, bucket, map->bucketsz);
            memcpy(bucket, entry, map->bucketsz);
            memcpy(entry, map->spare, map->bucketsz);
            eitem = bucket_item(entry);
        }
        i = (i + 1) & map->mask;
        entry->dib += 1;
    }
}

// hashmap_set inserts or replaces an item in the hash map. If an item is
// replaced then it is returned otherwise NULL is returned. This operation
// may allocate memory. If the system is unable to allocate additional
// memory then NULL is returned and hashmap_oom() returns true.
const void *hashmap_set(Hashmap_t *map, const void *item) {
    return hashmap_set_with_hash(map, item, get_hash(map, item));
}

// hashmap_get_with_hash works like hashmap_get but you provide your
// own hash. The 'hash' callback provided to the hashmap_new function
// will not be called
const void *hashmap_get_with_hash(Hashmap_t *map, const void *key,
    u64 hash) {
    hash = clip_hash(hash);
    Size_t i = hash & map->mask;
    while (1) {
        struct bucket *bucket = bucket_at(map, i);
        if (!bucket->dib) return NULL;
        if (bucket->hash == hash) {
            void *bitem = bucket_item(bucket);
            if (!map->compare || map->compare(key, bitem, map->udata) == 0) {
                return bitem;
            }
        }
        i = (i + 1) & map->mask;
    }
}

// hashmap_get returns the item based on the provided key. If the item is not
// found then NULL is returned.
const void *hashmap_get(Hashmap_t *map, const void *key) {
    return hashmap_get_with_hash(map, key, get_hash(map, key));
}

// hashmap_probe returns the item in the bucket at position or NULL if an item
// is not set for that bucket. The position is 'moduloed' by the number of 
// buckets in the hashmap.
const void *hashmap_probe(Hashmap_t *map, u64 position) {
    Size_t i = position & map->mask;
    struct bucket *bucket = bucket_at(map, i);
    if (!bucket->dib) {
        return NULL;
    }
    return bucket_item(bucket);
}

// hashmap_delete_with_hash works like hashmap_delete but you provide your
// own hash. The 'hash' callback provided to the hashmap_new function
// will not be called
const void *hashmap_delete_with_hash(Hashmap_t *map, const void *key,
    u64 hash) {
    hash = clip_hash(hash);
    map->oom = false;
    Size_t i = hash & map->mask;
    while (1) {
        struct bucket *bucket = bucket_at(map, i);
        if (!bucket->dib) {
            return NULL;
        }
        void *bitem = bucket_item(bucket);
        if (bucket->hash == hash && (!map->compare ||
            map->compare(key, bitem, map->udata) == 0)) {
            memcpy(map->spare, bitem, map->elsize);
            bucket->dib = 0;
            while (1) {
                struct bucket *prev = bucket;
                i = (i + 1) & map->mask;
                bucket = bucket_at(map, i);
                if (bucket->dib <= 1) {
                    prev->dib = 0;
                    break;
                }
                memcpy(prev, bucket, map->bucketsz);
                prev->dib--;
            }
            map->count--;
            if (map->nbuckets > map->cap && map->count <= map->shrinkat) {
                // Ignore the return value. It's ok for the resize operation to
                // fail to allocate enough memory because a shrink operation
                // does not change the integrity of the data.
                resize(map, map->nbuckets / 2);
            }
            return map->spare;
        }
        i = (i + 1) & map->mask;
    }
}

// hashmap_delete removes an item from the hash map and returns it. If the
// item is not found then NULL is returned.
const void *hashmap_delete(Hashmap_t *map, const void *key) {
    return hashmap_delete_with_hash(map, key, get_hash(map, key));
}

// hashmap_count returns the number of items in the hash map.
Size_t hashmap_count(Hashmap_t *map) {
    return map->count;
}

// hashmap_free frees the hash map
// Every item is called with the element-freeing function given in hashmap_new,
// if present, to free any data referenced in the elements of the hashmap.
void hashmap_free(Hashmap_t *map) {
    if (!map) return;
    free_elements(map);
    map->free(map->buckets);
    map->free(map);
}

// hashmap_oom returns true if the last hashmap_set() call failed due to the 
// system being out of memory.
bool hashmap_oom(Hashmap_t *map) {
    return map->oom;
}

// hashmap_scan iterates over all items in the hash map
// Param `iter` can return false to stop iteration early.
// Returns false if the iteration has been stopped early.
bool hashmap_scan(Hashmap_t *map,
    bool (*iter)(const void *item, void *udata), void *udata) {
    for (Size_t i = 0; i < map->nbuckets; i++) {
        struct bucket *bucket = bucket_at(map, i);
        if (bucket->dib && !iter(bucket_item(bucket), udata)) {
            return false;
        }
    }
    return true;
}

// hashmap_iter iterates one key at a time yielding a reference to an
// entry at each iteration. Useful to write simple loops and avoid writing
// dedicated callbacks and udata structures, as in hashmap_scan.
//
// map is a hash map handle. i is a pointer to a Size_t cursor that
// should be initialized to 0 at the beginning of the loop. item is a void
// pointer pointer that is populated with the retrieved item. Note that this
// is NOT a copy of the item stored in the hash map and can be directly
// modified.
//
// Note that if hashmap_delete() is called on the hashmap being iterated,
// the buckets are rearranged and the iterator must be reset to 0, otherwise
// unexpected results may be returned after deletion.
//
// This function has not been tested for thread safety.
//
// The function returns true if an item was retrieved; false if the end of the
// iteration has been reached.
bool hashmap_iter(Hashmap_t *map, Size_t *i, void **item) {
    struct bucket *bucket;
    do {
        if (*i >= map->nbuckets) return false;
        bucket = bucket_at(map, *i);
        (*i)++;
    } while (!bucket->dib);
    *item = bucket_item(bucket);
    return true;
}


//-----------------------------------------------------------------------------
// SipHash reference C implementation
//
// Copyright (c) 2012-2016 Jean-Philippe Aumasson
// <jeanphilippe.aumasson@gmail.com>
// Copyright (c) 2012-2014 Daniel J. Bernstein <djb@cr.yp.to>
//
// To the extent possible under law, the author(s) have dedicated all copyright
// and related and neighboring rights to this software to the public domain
// worldwide. This software is distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along
// with this software. If not, see
// <http://creativecommons.org/publicdomain/zero/1.0/>.
//
// default: SipHash-2-4
//-----------------------------------------------------------------------------
static u64 SIP64(const u8 *in, const Size_t inlen, u64 seed0,
    u64 seed1) {
#define U8TO64_LE(p) \
    {  (((u64)((p)[0])) | ((u64)((p)[1]) << 8) | \
        ((u64)((p)[2]) << 16) | ((u64)((p)[3]) << 24) | \
        ((u64)((p)[4]) << 32) | ((u64)((p)[5]) << 40) | \
        ((u64)((p)[6]) << 48) | ((u64)((p)[7]) << 56)) }
#define U64TO8_LE(p, v) \
    { U32TO8_LE((p), (u32)((v))); \
      U32TO8_LE((p) + 4, (u32)((v) >> 32)); }
#define U32TO8_LE(p, v) \
    { (p)[0] = (u8)((v)); \
      (p)[1] = (u8)((v) >> 8); \
      (p)[2] = (u8)((v) >> 16); \
      (p)[3] = (u8)((v) >> 24); }
#define ROTL(x, b) (u64)(((x) << (b)) | ((x) >> (64 - (b))))
#define SIPROUND \
    { v0 += v1; v1 = ROTL(v1, 13); \
      v1 ^= v0; v0 = ROTL(v0, 32); \
      v2 += v3; v3 = ROTL(v3, 16); \
      v3 ^= v2; \
      v0 += v3; v3 = ROTL(v3, 21); \
      v3 ^= v0; \
      v2 += v1; v1 = ROTL(v1, 17); \
      v1 ^= v2; v2 = ROTL(v2, 32); }
    u64 k0 = U8TO64_LE((u8 *) &seed0);
    u64 k1 = U8TO64_LE((u8 *) &seed1);
    u64 v3 = UINT64_C(0x7465646279746573) ^ k1;
    u64 v2 = UINT64_C(0x6c7967656e657261) ^ k0;
    u64 v1 = UINT64_C(0x646f72616e646f6d) ^ k1;
    u64 v0 = UINT64_C(0x736f6d6570736575) ^ k0;
    const u8 *end = in + inlen - (inlen % sizeof(u64));
    for (; in != end; in += 8) {
        u64 m = U8TO64_LE(in);
        v3 ^= m;
        SIPROUND; SIPROUND;
        v0 ^= m;
    }
    const int left = inlen & 7;
    u64 b = ((u64) inlen) << 56;
    switch (left) {
        case 7: b |= ((u64) in[6]) << 48; /* fall through */
        case 6: b |= ((u64) in[5]) << 40; /* fall through */
        case 5: b |= ((u64) in[4]) << 32; /* fall through */
        case 4: b |= ((u64) in[3]) << 24; /* fall through */
        case 3: b |= ((u64) in[2]) << 16; /* fall through */
        case 2: b |= ((u64) in[1]) << 8; /* fall through */
        case 1: b |= ((u64) in[0]); break;
        case 0: break;
    }
    v3 ^= b;
    SIPROUND; SIPROUND;
    v0 ^= b;
    v2 ^= 0xff;
    SIPROUND; SIPROUND; SIPROUND; SIPROUND;
    b = v0 ^ v1 ^ v2 ^ v3;
    u64 out = 0;
    U64TO8_LE((u8 *) &out, b);
    return out;
}

//-----------------------------------------------------------------------------
// MurmurHash3 was written by Austin Appleby, and is placed in the public
// domain. The author hereby disclaims copyright to this source code.
//
// Murmur3_86_128
//-----------------------------------------------------------------------------
static u64 MM86128(const void *key, const int len, u32 seed) {
#define	ROTL32(x, r) ((x << r) | (x >> (32 - r)))
#define FMIX32(h) h^=h>>16; h*=0x85ebca6b; h^=h>>13; h*=0xc2b2ae35; h^=h>>16;
    const u8 *data = (const u8 *) key;
    const int nblocks = len / 16;
    u32 h1 = seed;
    u32 h2 = seed;
    u32 h3 = seed;
    u32 h4 = seed;
    u32 c1 = 0x239b961b;
    u32 c2 = 0xab0e9789;
    u32 c3 = 0x38b34ae5;
    u32 c4 = 0xa1e38b93;
    const u32 *blocks = (const u32 *) (data + nblocks * 16);
    for (int i = -nblocks; i; i++) {
        u32 k1 = blocks[i * 4 + 0];
        u32 k2 = blocks[i * 4 + 1];
        u32 k3 = blocks[i * 4 + 2];
        u32 k4 = blocks[i * 4 + 3];
        k1 *= c1; k1 = ROTL32(k1, 15); k1 *= c2; h1 ^= k1;
        h1 = ROTL32(h1, 19); h1 += h2; h1 = h1 * 5 + 0x561ccd1b;
        k2 *= c2; k2 = ROTL32(k2, 16); k2 *= c3; h2 ^= k2;
        h2 = ROTL32(h2, 17); h2 += h3; h2 = h2 * 5 + 0x0bcaa747;
        k3 *= c3; k3 = ROTL32(k3, 17); k3 *= c4; h3 ^= k3;
        h3 = ROTL32(h3, 15); h3 += h4; h3 = h3 * 5 + 0x96cd1c35;
        k4 *= c4; k4 = ROTL32(k4, 18); k4 *= c1; h4 ^= k4;
        h4 = ROTL32(h4, 13); h4 += h1; h4 = h4 * 5 + 0x32ac3b17;
    }
    const u8 *tail = (const u8 *) (data + nblocks * 16);
    u32 k1 = 0;
    u32 k2 = 0;
    u32 k3 = 0;
    u32 k4 = 0;
    switch (len & 15) {
        case 15: k4 ^= tail[14] << 16; /* fall through */
        case 14: k4 ^= tail[13] << 8; /* fall through */
        case 13: k4 ^= tail[12] << 0;
            k4 *= c4; k4 = ROTL32(k4, 18); k4 *= c1; h4 ^= k4;
            /* fall through */
        case 12: k3 ^= tail[11] << 24; /* fall through */
        case 11: k3 ^= tail[10] << 16; /* fall through */
        case 10: k3 ^= tail[9] << 8; /* fall through */
        case  9: k3 ^= tail[8] << 0;
            k3 *= c3; k3 = ROTL32(k3, 17); k3 *= c4; h3 ^= k3;
            /* fall through */
        case  8: k2 ^= tail[7] << 24; /* fall through */
        case  7: k2 ^= tail[6] << 16; /* fall through */
        case  6: k2 ^= tail[5] << 8; /* fall through */
        case  5: k2 ^= tail[4] << 0;
            k2 *= c2; k2 = ROTL32(k2, 16); k2 *= c3; h2 ^= k2;
            /* fall through */
        case  4: k1 ^= tail[3] << 24; /* fall through */
        case  3: k1 ^= tail[2] << 16; /* fall through */
        case  2: k1 ^= tail[1] << 8; /* fall through */
        case  1: k1 ^= tail[0] << 0;
            k1 *= c1; k1 = ROTL32(k1, 15); k1 *= c2; h1 ^= k1;
            /* fall through */
    };
    h1 ^= len; h2 ^= len; h3 ^= len; h4 ^= len;
    h1 += h2; h1 += h3; h1 += h4;
    h2 += h1; h3 += h1; h4 += h1;
    FMIX32(h1); FMIX32(h2); FMIX32(h3); FMIX32(h4);
    h1 += h2; h1 += h3; h1 += h4;
    h2 += h1; h3 += h1; h4 += h1;
    return (((u64) h2) << 32) | h1;
}

//-----------------------------------------------------------------------------
// xxHash Library
// Copyright (c) 2012-2021 Yann Collet
// All rights reserved.
// 
// BSD 2-Clause License (https://www.opensource.org/licenses/bsd-license.php)
//
// xxHash3
//-----------------------------------------------------------------------------
#define XXH_PRIME_1 11400714785074694791ULL
#define XXH_PRIME_2 14029467366897019727ULL
#define XXH_PRIME_3 1609587929392839161ULL
#define XXH_PRIME_4 9650029242287828579ULL
#define XXH_PRIME_5 2870177450012600261ULL

static u64 XXH_read64(const void *memptr) {
    u64 val;
    memcpy(&val, memptr, sizeof(val));
    return val;
}

static u32 XXH_read32(const void *memptr) {
    u32 val;
    memcpy(&val, memptr, sizeof(val));
    return val;
}

static u64 XXH_rotl64(u64 x, int r) {
    return (x << r) | (x >> (64 - r));
}

static u64 xxh3(const void *data, Size_t len, u64 seed) {
    const u8 *p = (const u8 *) data;
    const u8 *const end = p + len;
    u64 h64;

    if (len >= 32) {
        const u8 *const limit = end - 32;
        u64 v1 = seed + XXH_PRIME_1 + XXH_PRIME_2;
        u64 v2 = seed + XXH_PRIME_2;
        u64 v3 = seed + 0;
        u64 v4 = seed - XXH_PRIME_1;

        do {
            v1 += XXH_read64(p) * XXH_PRIME_2;
            v1 = XXH_rotl64(v1, 31);
            v1 *= XXH_PRIME_1;

            v2 += XXH_read64(p + 8) * XXH_PRIME_2;
            v2 = XXH_rotl64(v2, 31);
            v2 *= XXH_PRIME_1;

            v3 += XXH_read64(p + 16) * XXH_PRIME_2;
            v3 = XXH_rotl64(v3, 31);
            v3 *= XXH_PRIME_1;

            v4 += XXH_read64(p + 24) * XXH_PRIME_2;
            v4 = XXH_rotl64(v4, 31);
            v4 *= XXH_PRIME_1;

            p += 32;
        } while (p <= limit);

        h64 = XXH_rotl64(v1, 1) + XXH_rotl64(v2, 7) + XXH_rotl64(v3, 12) +
            XXH_rotl64(v4, 18);

        v1 *= XXH_PRIME_2;
        v1 = XXH_rotl64(v1, 31);
        v1 *= XXH_PRIME_1;
        h64 ^= v1;
        h64 = h64 * XXH_PRIME_1 + XXH_PRIME_4;

        v2 *= XXH_PRIME_2;
        v2 = XXH_rotl64(v2, 31);
        v2 *= XXH_PRIME_1;
        h64 ^= v2;
        h64 = h64 * XXH_PRIME_1 + XXH_PRIME_4;

        v3 *= XXH_PRIME_2;
        v3 = XXH_rotl64(v3, 31);
        v3 *= XXH_PRIME_1;
        h64 ^= v3;
        h64 = h64 * XXH_PRIME_1 + XXH_PRIME_4;

        v4 *= XXH_PRIME_2;
        v4 = XXH_rotl64(v4, 31);
        v4 *= XXH_PRIME_1;
        h64 ^= v4;
        h64 = h64 * XXH_PRIME_1 + XXH_PRIME_4;
    }
    else {
        h64 = seed + XXH_PRIME_5;
    }

    h64 += (u64) len;

    while (p + 8 <= end) {
        u64 k1 = XXH_read64(p);
        k1 *= XXH_PRIME_2;
        k1 = XXH_rotl64(k1, 31);
        k1 *= XXH_PRIME_1;
        h64 ^= k1;
        h64 = XXH_rotl64(h64, 27) * XXH_PRIME_1 + XXH_PRIME_4;
        p += 8;
    }

    if (p + 4 <= end) {
        h64 ^= (u64) (XXH_read32(p)) * XXH_PRIME_1;
        h64 = XXH_rotl64(h64, 23) * XXH_PRIME_2 + XXH_PRIME_3;
        p += 4;
    }

    while (p < end) {
        h64 ^= (*p) * XXH_PRIME_5;
        h64 = XXH_rotl64(h64, 11) * XXH_PRIME_1;
        p++;
    }

    h64 ^= h64 >> 33;
    h64 *= XXH_PRIME_2;
    h64 ^= h64 >> 29;
    h64 *= XXH_PRIME_3;
    h64 ^= h64 >> 32;

    return h64;
}

// hashmap_sip returns a hash value for `data` using SipHash-2-4.
u64 hashmap_sip(const void *data, Size_t len, u64 seed0,
    u64 seed1) {
    return SIP64((u8 *) data, len, seed0, seed1);
}

// hashmap_murmur returns a hash value for `data` using Murmur3_86_128.
u64 hashmap_murmur(const void *data, Size_t len, u64 seed0,
    u64 seed1) {
    (void) seed1;
    return MM86128(data, len, seed0);
}

u64 hashmap_xxhash3(const void *data, Size_t len, u64 seed0,
    u64 seed1) {
    (void) seed1;
    return xxh3(data, len, seed0);
}