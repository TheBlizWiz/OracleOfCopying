#ifndef D_COMMON_H
#define D_COMMON_H

#ifdef OOCDLL_EXPORTS
#define DLLINCLUDE __declspec(dllexport)
#else
#define DLLINCLUDE __declspec(dllimport)
#endif

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#ifdef _DEBUG
#define errprintf printf
#endif

#ifdef NDEBUG
#define errprintf //
#endif

#define zeroset(ptr, sz) memset(ptr, 0, sz)
#define strncopy(dst, src, szdst) do { strncpy_s(dst, sizeof(dst[0]) * szdst, src, sizeof(dst[0]) * (szdst - 1)); dst[szdst - 1] = '\0'; } while(0)

DLLINCLUDE typedef uint8_t  u8;
DLLINCLUDE typedef uint16_t u16;
DLLINCLUDE typedef uint32_t u32;
DLLINCLUDE typedef uint64_t u64;
DLLINCLUDE typedef int8_t   i8;
DLLINCLUDE typedef int16_t  i16;
DLLINCLUDE typedef int32_t  i32;
DLLINCLUDE typedef int64_t  i64;

DLLINCLUDE typedef uint8_t boolean;

DLLINCLUDE typedef union color Color_u;

// _t is for structs only but these are an exception since
// they already have a _t in them

DLLINCLUDE typedef uint64_t Size_t;
DLLINCLUDE typedef int64_t  Ssize_t;
DLLINCLUDE typedef int64_t  Error_t;

DLLINCLUDE typedef struct TreeNode TreeNode_t;
DLLINCLUDE typedef struct Tree Tree_t;

// yeah these break the rules but i also use them frequently and writing _t got annoying

DLLINCLUDE typedef struct _TWO_DOUBLES   Point2;
DLLINCLUDE typedef struct _THREE_DOUBLES Point3;
DLLINCLUDE typedef struct _TWO_DOUBLES   Vector2;
DLLINCLUDE typedef struct _THREE_DOUBLES Vector3;
DLLINCLUDE typedef struct _TWO_DOUBLES   Scalar2;
DLLINCLUDE typedef struct _THREE_DOUBLES Scalar3;
DLLINCLUDE typedef struct _FOUR_DOUBLES  Quaternion;

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

union color {
    struct {
        u8 a;
        u8 b;
        u8 g;
        u8 r;
    };
    u32 rgba;
};

// Point2, Vector2, Scalar2
struct _TWO_DOUBLES {
    double x;
    double y;
};

// Point3, Vector3, Scalar3
struct _THREE_DOUBLES {
    double x;
    double y;
    double z;
};

// Quaternion
struct _FOUR_DOUBLES {
    double w;
    double x;
    double y;
    double z;
};

#endif