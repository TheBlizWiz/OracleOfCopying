#include "d_common.h"
#include "g_hitbox.h"
#include "d_constants.h"

#include <stdlib.h>

Hitbox_t hbox_new(u8 xa, u8 ya, u8 xb, u8 yb, u8 xc, u8 yc, u8 xd, u8 yd, i16 zb, i16 zt) {
    Hitbox_t hbx;
    hbx.A = lpoint_new(xa, ya);
    hbx.B = lpoint_new(xb, yb);
    hbx.C = lpoint_new(xc, yc);
    hbx.D = lpoint_new(xd, yd);
    hbx.ztop = zt;
    hbx.zbottom = zb;
    return hbx;
}

Hitbox_t hbox_newdefault() {
    return hbox_newsquished(A_POS_DEFAULT, B_POS_DEFAULT, C_POS_DEFAULT, D_POS_DEFAULT, ZT_POS_DEFAULT, ZB_POS_DEFAULT);
}

// a relic of when i thought it was a good idea to store points as a single u16 and then bitmask on the fly
// it was a bad idea, it broke immediately
// but i still have the constants for it in constants.h and it saves space in that giant file
// so i'll keep it this way

// just use hbox_new
Hitbox_t hbox_newsquished(u16 yxa, u16 yxb, u16 yxc, u16 yxd, i16 zt, i16 zb) {
    Hitbox_t hbx;
    hbx.A = lpoint_new((u8) yxa, (u8) (yxa >> 8));
    hbx.B = lpoint_new((u8) yxb, (u8) (yxb >> 8));
    hbx.C = lpoint_new((u8) yxc, (u8) (yxc >> 8));
    hbx.D = lpoint_new((u8) yxd, (u8) (yxd >> 8));
    hbx.ztop = zt;
    hbx.zbottom = zb;
    return hbx;
}