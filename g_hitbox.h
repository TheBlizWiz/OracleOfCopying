#ifndef G_HITBOX_H
#define G_HITBOX_H

#include "d_common.h"

/**
    Hitbox looks like this:

     C---------D
    / |      / |
   /  |     /  |   z = ztop
  A--------B   |
  |   |    |   |
  |   |    |   |
  |   |    |   |
  |   C----|---D
  |  /     |  /
  | /      | /    z = zbottom
  |/       |/
  A--------B

    The top and bottom is always flat, so we can reuse the same values
    for A, B, C, D for both the top and bottom faces

    Viewed from above it looks like this:

    C--------D
    |        |
    |        |  z = ztop
    |        |
    A--------B
  */
typedef struct {
    u16 yxA, yxB, yxC, yxD;
    i16 ztop;
    i16 zbottom;
} Hitbox_t;

Hitbox_t hbox_new(u8, u8, u8, u8, u8, u8, u8, u8, i16, i16);
Hitbox_t hbox_newdefault();
Hitbox_t hbox_newsquished(u16, u16, u16, u16, i16, i16);

u8 *hbox_getpoint(u16);

#endif