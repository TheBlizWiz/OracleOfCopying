#ifndef D_COMMON_H
#define D_COMMON_H

#include <stdint.h>

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t   i8;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;

// commons dont usually have _t after them but since these are
// redefines of existing _t I include them anyway
typedef uint64_t Size_t;
typedef int64_t  Ssize_t;
typedef int64_t  Error_t;

#endif