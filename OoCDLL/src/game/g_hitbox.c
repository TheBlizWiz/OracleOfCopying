#include <stdlib.h>

#ifdef DLL_EXPORT
#define G_HITBOX_API __declspec(dllexport)
#else
#define G_HITBOX_API __declspec(dllimport)
#endif

#include "oocdll.h"
#include "game/g_hitbox.h"

Hitbox_t hbox_new(u8 xa, u8 ya, u8 xb, u8 yb, u8 xc, u8 yc, u8 xd, u8 yd, i16 zb, i16 zt) {
    Hitbox_t hbx;
    hbx.Ax = xa;
    hbx.Ay = ya;
    hbx.Bx = xb;
    hbx.By = yb;
    hbx.Cx = xc;
    hbx.Cy = yc;
    hbx.Dx = xd;
    hbx.Dy = yd;
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
    hbx.Ax = (u8) yxa;
    hbx.Ay = (u8) (yxa >> 8);
    hbx.Bx = (u8) yxb;
    hbx.By = (u8) (yxb >> 8);
    hbx.Cx = (u8) yxc;
    hbx.Cy = (u8) (yxc >> 8);
    hbx.Dx = (u8) yxd;
    hbx.Dy = (u8) (yxd >> 8);
    hbx.ztop = zt;
    hbx.zbottom = zb;
    return hbx;
}