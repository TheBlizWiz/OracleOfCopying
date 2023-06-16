#ifndef U_HASH_H
#define U_HASH_H

#ifdef OOCDLL_EXPORTS
#define U_HASH_API __declspec(dllexport)
#else
#define U_HASH_API __declspec(dllimport)
#endif

#include <stdbool.h>

#include "defs/d_common.h"
#include "libs/hashmap/hashmap.h"

// using hashmap.c found at https://github.com/tidwall/hashmap.c 
// thanks for doing the heavy lifting :)

U_HASH_API int hash_imgcmp(const void *, const void *, void *);

U_HASH_API bool hash_imgiter(const void *, void *);

U_HASH_API u64 hash_imghash(const void *, u64, u64);


#endif