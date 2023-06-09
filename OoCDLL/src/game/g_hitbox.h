#ifndef G_HITBOX_H
#define G_HITBOX_H

#ifdef OOCDLL_EXPORTS
#define G_HITBOX_API __declspec(dllexport)
#else
#define G_HITBOX_API __declspec(dllimport)
#endif

#include "defs/d_common.h"

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
G_HITBOX_API typedef struct {
    u8 Ax, Ay, Bx, By, Cx, Cy, Dx, Dy;
    i16 ztop;
    i16 zbottom;
} Hitbox_t;

G_HITBOX_API Hitbox_t hbox_new(u8, u8, u8, u8, u8, u8, u8, u8, i16, i16);
G_HITBOX_API Hitbox_t hbox_newdefault();
G_HITBOX_API Hitbox_t hbox_newsquished(u16, u16, u16, u16, i16, i16);

#endif