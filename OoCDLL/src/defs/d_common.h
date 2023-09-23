#ifndef D_COMMON_H
#define D_COMMON_H

#ifdef OOCDLL_EXPORTS
#define DLLINCLUDE __declspec(dllexport)
#else
#define DLLINCLUDE __declspec(dllimport)
#endif

#include <stdint.h>

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

// yeah these break the rules but i also use them frequently and writing _t got annoying

DLLINCLUDE typedef struct _TWO_U32S      Coordinate;
DLLINCLUDE typedef struct _TWO_DOUBLES   Point2;
DLLINCLUDE typedef struct _THREE_DOUBLES Point3;
DLLINCLUDE typedef struct _TWO_DOUBLES   Vector2;
DLLINCLUDE typedef struct _THREE_DOUBLES Vector3;
DLLINCLUDE typedef struct _TWO_DOUBLES   Scalar2;
DLLINCLUDE typedef struct _THREE_DOUBLES Scalar3;
DLLINCLUDE typedef struct _TWO_DOUBLES   Angle2;
DLLINCLUDE typedef struct _THREE_DOUBLES Angle3;
DLLINCLUDE typedef struct _FOUR_DOUBLES  Quaternion;

DLLINCLUDE typedef Error_t(*free_fnptr)(void *data);
DLLINCLUDE typedef i32(*cmp_fnptr)(const void *data, const void *tgtdata);

union color {
    struct {
        u8 a;
        u8 b;
        u8 g;
        u8 r;
    };
    u32 rgba;
};

// Coord
struct _TWO_U32S {
    u32 x;
    u32 y;
};

// Point2, Vector2, Scalar2, Angle2
struct _TWO_DOUBLES {
    union {
        double x;
        double pitch;
    };
    union {
        double y;
        double yaw;
    };
};

// Point3, Vector3, Scalar3, Angle3
struct _THREE_DOUBLES {
    union {
        double x;
        double pitch;
    };
    union {
        double y;
        double yaw;
    };
    union {
        double z;
        double roll;
    };
};

// Quaternion
struct _FOUR_DOUBLES {
    double w;
    double x;
    double y;
    double z;
};

#endif