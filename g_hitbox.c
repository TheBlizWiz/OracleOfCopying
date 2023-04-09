#include "d_common.h"
#include "g_hitbox.h"
#include "d_constants.h"

#include <stdlib.h>

Hitbox_t hbox_new(u8 xa, u8 ya, u8 xb, u8 yb, u8 xc, u8 yc, u8 xd, u8 yd, i16 zb, i16 zt) {
    Hitbox_t hbx;
    hbx.yxA = (u16) ya << 8 | xa;
    hbx.yxB = (u16) yb << 8 | xb;
    hbx.yxC = (u16) yc << 8 | xc;
    hbx.yxD = (u16) yd << 8 | xd;
    hbx.ztop = zt;
    hbx.zbottom = zb;
    return hbx;
}

Hitbox_t hbox_newdefault() {
    return hbox_newsquished(A_POS_DEFAULT, B_POS_DEFAULT, C_POS_DEFAULT, D_POS_DEFAULT, ZT_POS_DEFAULT, ZB_POS_DEFAULT);
}

Hitbox_t hbox_newsquished(u16 yxa, u16 yxb, u16 yxc, u16 yxd, i16 zt, i16 zb) {
    Hitbox_t hbx;
    hbx.yxA = yxa;
    hbx.yxB = yxb;
    hbx.yxC = yxc;
    hbx.yxD = yxd;
    hbx.ztop = zt;
    hbx.zbottom = zb;
    return hbx;
}

u8 *hbox_getpoint(u16 ABCD) {
    u8 *xy = malloc(sizeof(u8) * 2);
    u8 xABCD = (u8) ABCD;
    u8 yABCD = (u8) (ABCD >> 8); // with no () it bitshifts second...
    xy[0] = xABCD;
    xy[1] = yABCD;
    return xy;
}