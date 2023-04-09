#ifndef G_POINT_H
#define G_POINT_H

#include "d_common.h"

typedef struct {
    u8 x, y;
} LocalPoint_t;

typedef struct {
    i32 x, y;
} GlobalPoint_t;

LocalPoint_t lpoint_new(u8, u8);
GlobalPoint_t gpoint_new(i32, i32);

#endif