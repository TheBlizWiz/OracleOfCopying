#ifndef D_COMMON_H
#define D_COMMON_H

#ifdef OOCDLL_EXPORTS
#define DLLINCLUDE __declspec(dllexport)
#else
#define DLLADD __declspec(dllimport)
#endif

#include <stdint.h>

#ifdef _DEBUG
#define errprintf printf
#endif

#ifdef NDEBUG
#define errprintf //
#endif

#define IF_PTR_RETURN_PTR(x) do { if(x) { return x; } } while(0)

DLLINCLUDE typedef uint8_t  u8;
DLLINCLUDE typedef uint16_t u16;
DLLINCLUDE typedef uint32_t u32;
DLLINCLUDE typedef uint64_t u64;
DLLINCLUDE typedef int8_t   i8;
DLLINCLUDE typedef int16_t  i16;
DLLINCLUDE typedef int32_t  i32;
DLLINCLUDE typedef int64_t  i64;

// _t is for structs only but these are an exception since
// they already have a _t in them

DLLINCLUDE typedef uint64_t Size_t;
DLLINCLUDE typedef int64_t  Ssize_t;
DLLINCLUDE typedef int64_t  Error_t;

DLLINCLUDE typedef struct TreeNode TreeNode_t;
DLLINCLUDE typedef struct Tree Tree_t;

DLLINCLUDE typedef void *(*DataMalloc_fnptr)(void *dataptr, Size_t datasize);
DLLINCLUDE typedef void *(*DataXalloc_fnptr)(void *dataptr, Size_t datasize, Size_t numelements);
DLLINCLUDE typedef Error_t(*DataFree_fnptr)(void *data);
DLLINCLUDE typedef i32(*DataCmp_fnptr)(const void *data, const void *tgtdata);

struct TreeNode {
    u32 key;
    void *data;
    DataFree_fnptr datafree;
    DataCmp_fnptr datacmp;

    struct TreeNode *left;
    struct TreeNode *right;
};

struct Tree {
    struct TreeNode_t **root;
    Size_t size;
};

#endif