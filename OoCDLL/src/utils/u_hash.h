#ifndef U_HASH_H
#define U_HASH_H

#include <stdbool.h>

#include "defs/d_common.h"
#include "libs/hashmap/hashmap.h"

// using hashmap.c found at https://github.com/tidwall/hashmap.c 
// thanks for doing the heavy lifting :)

DLLINCLUDE int hash_imgcmp(const void *, const void *, void *);

DLLINCLUDE bool hash_imgiter(const void *, void *);

DLLINCLUDE u64 hash_imghash(const void *, u64, u64);

DLLINCLUDE void hash_imgfree(void *);

#endif