#ifndef D_COMMON_H
#define D_COMMON_H

#ifdef OOCDLL_EXPORTS
#define D_COMMON_API __declspec(dllexport)
#else
#define D_COMMON_API __declspec(dllimport)
#endif

#include <stdint.h>
#include "SDL.h"

D_COMMON_API typedef uint8_t  u8;
D_COMMON_API typedef uint16_t u16;
D_COMMON_API typedef uint32_t u32;
D_COMMON_API typedef uint64_t u64;
D_COMMON_API typedef int8_t   i8;
D_COMMON_API typedef int16_t  i16;
D_COMMON_API typedef int32_t  i32;
D_COMMON_API typedef int64_t  i64;

// commons dont usually have _t after them but since these are
// redefines of existing _t I include them anyway

D_COMMON_API typedef uint64_t Size_t;
D_COMMON_API typedef int64_t  Ssize_t;
D_COMMON_API typedef int64_t  Error_t;

#endif