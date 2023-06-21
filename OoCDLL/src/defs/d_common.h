#ifndef D_COMMON_H
#define D_COMMON_H

#ifdef OOCDLL_EXPORTS
#define D_COMMON_API __declspec(dllexport)
#else
#define D_COMMON_API __declspec(dllimport)
#endif

#include <stdint.h>

D_COMMON_API typedef uint8_t  u8;
D_COMMON_API typedef uint16_t u16;
D_COMMON_API typedef uint32_t u32;
D_COMMON_API typedef uint64_t u64;
D_COMMON_API typedef int8_t   i8;
D_COMMON_API typedef int16_t  i16;
D_COMMON_API typedef int32_t  i32;
D_COMMON_API typedef int64_t  i64;

// _t is for structs only but these are an exception since
// they already have a _t in them

D_COMMON_API typedef uint64_t Size_t;
D_COMMON_API typedef int64_t  Ssize_t;
D_COMMON_API typedef int64_t  Error_t;

D_COMMON_API typedef struct  {
    u32 key;
    void *data;
    struct TreeNode_t *left;
    struct TreeNode_t *right;
} TreeNode_t;

D_COMMON_API typedef struct {
    u32 key;
    void *data;
    struct ListNode_t *next;
    struct ListNode_t *prev;
} ListNode_t;

#endif