#include "d_common.h"
#include "g_point.h"

LocalPoint_t lpoint_new(u8 lx, u8 ly) {
    LocalPoint_t lp;
    lp.x = lx;
    lp.y = ly;
    return lp;
}

GlobalPoint_t gpoint_new(i32 gx, i32 gy) {
    GlobalPoint_t gp;
    gp.x = gx;
    gp.y = y;
    return gp;
}