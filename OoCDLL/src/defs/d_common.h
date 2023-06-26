#ifndef D_COMMON_H
#define D_COMMON_H

#ifdef OOCDLL_EXPORTS
#define D_COMMON_API __declspec(dllexport)
#else
#define D_COMMON_API __declspec(dllimport)
#endif

#include <stdint.h>

#ifdef _DEBUG
#define errprintf printf
#endif

#ifdef NDEBUG
#define errprintf //
#endif

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

D_COMMON_API typedef struct TreeNode TreeNode_t;
D_COMMON_API typedef struct Tree Tree_t;
D_COMMON_API typedef struct ListNode ListNode_t;
D_COMMON_API typedef struct List List_t;

D_COMMON_API typedef Error_t(*DataFree_fnptr)(void *data);
D_COMMON_API typedef i32(*DataCmp_fnptr)(const void *nodedata, const void *tgtdata);

struct TreeNode {
    u32 key;
    void *data;
    struct TreeNode *left;
    struct TreeNode *right;

    DataFree_fnptr datafree;
    DataCmp_fnptr datacmp;
};

struct Tree {
    struct TreeNode_t **root;
    Size_t size;
};

struct ListNode {
    u32 key;
    void *data;
    struct ListNode *next;

    DataFree_fnptr datafree;
    DataCmp_fnptr datacmp;
};

struct List {
    struct ListNode **headptr;
    Size_t size;
};

#endif