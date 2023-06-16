// Copyright 2020 Joshua J Baker. All rights reserved.
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file.

#ifndef HASHMAP_H
#define HASHMAP_H

#ifdef OOCDLL_EXPORTS
#define HASHMAP_H_API __declspec(dllexport)
#else
#define HASHMAP_H_API __declspec(dllimport)
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "defs/d_common.h"

HASHMAP_H_API typedef struct hashmap Hashmap_t;

// hashmap is an open addressed hash map using robinhood hashing.
HASHMAP_H_API struct hashmap {
    void *(*malloc) (Size_t);
    void *(*realloc) (void *, Size_t);
    void (*free) (void *);
    Size_t elsize;
    Size_t cap;
    u64 seed0;
    u64 seed1;
    u64 (*hash) (const void *item, u64 seed0, u64 seed1);
    int (*compare) (const void *a, const void *b, void *udata);
    void (*elfree) (void *item);
    void *udata;
    Size_t bucketsz;
    Size_t nbuckets;
    Size_t count;
    Size_t mask;
    Size_t growat;
    Size_t shrinkat;
    uint8_t growpower;
    bool oom;
    void *buckets;
    void *spare;
    void *edata;
};

HASHMAP_H_API Hashmap_t *hashmap_new(
    Size_t elsize,
    Size_t cap,
    u64 seed0,
    u64 seed1,
    u64 (*hash) (const void *item, u64 seed0, u64 seed1),
    int (*compare) (const void *a, const void *b, void *udata),
    void (*elfree) (void *item),
    void *udata
);

HASHMAP_H_API Hashmap_t *hashmap_new_with_allocator(
    void *(*malloc) (Size_t),
    void *(*realloc) (void *, Size_t),
    void (*free) (void *),
    Size_t elsize,
    Size_t cap,
    u64 seed0,
    u64 seed1,
    u64 (*hash) (const void *item, u64 seed0, u64 seed1),
    int (*compare) (const void *a, const void *b, void *udata),
    void (*elfree) (void *item),
    void *udata);

HASHMAP_H_API void hashmap_free(Hashmap_t *map);
HASHMAP_H_API void hashmap_clear(Hashmap_t *map, bool update_cap);
HASHMAP_H_API Size_t hashmap_count(Hashmap_t *map);
HASHMAP_H_API bool hashmap_oom(Hashmap_t *map);
HASHMAP_H_API const void *hashmap_get(Hashmap_t *map, const void *item);
HASHMAP_H_API const void *hashmap_set(Hashmap_t *map, const void *item);
HASHMAP_H_API const void *hashmap_delete(Hashmap_t *map, const void *item);
HASHMAP_H_API const void *hashmap_probe(Hashmap_t *map, u64 position);
HASHMAP_H_API bool hashmap_scan(Hashmap_t *map, bool (*iter)(const void *item, void *udata), void *udata);
HASHMAP_H_API bool hashmap_iter(Hashmap_t *map, Size_t *i, void **item);

HASHMAP_H_API u64 hashmap_sip(const void *data, Size_t len, u64 seed0, u64 seed1);
HASHMAP_H_API u64 hashmap_murmur(const void *data, Size_t len, u64 seed0, u64 seed1);
HASHMAP_H_API u64 hashmap_xxhash3(const void *data, Size_t len, u64 seed0, u64 seed1);

HASHMAP_H_API const void *hashmap_get_with_hash(Hashmap_t *map, const void *key, u64 hash);
HASHMAP_H_API const void *hashmap_delete_with_hash(Hashmap_t *map, const void *key, u64 hash);
HASHMAP_H_API const void *hashmap_set_with_hash(Hashmap_t *map, const void *item, u64 hash);
HASHMAP_H_API void hashmap_set_grow_by_power(Hashmap_t *map, Size_t power);


// DEPRECATED: use `hashmap_new_with_allocator`
HASHMAP_H_API void hashmap_set_allocator(void *(*malloc)(Size_t), void (*free)(void *));

#endif
