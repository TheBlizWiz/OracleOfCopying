#ifndef G_HITBOX_H
#define G_HITBOX_H

#include "defs/d_common.h"

/**
    Hitbox looks like this:

     G---------H
    / |      / |
   /  |     /  |
  E--------F   |
  |   |    |   |
  |   |    |   |
  |   |    |   |
  |   C----|---D
  |  /     |  /
  | /      | /
  |/       |/
  A--------B

  */
DLLINCLUDE typedef struct Hitbox Hitbox_t;

struct Hitbox{
    Point3 A;
    Point3 B;
    Point3 C;
    Point3 D;

    Point3 E;
    Point3 F;
    Point3 G;
    Point3 H;
};


DLLINCLUDE Hitbox_t hbox_new(Point3, Point3, Point3, Point3, Point3, Point3, Point3, Point3);
DLLINCLUDE Hitbox_t hbox_newdefault();
/*
DLLINCLUDE Hitbox_t hbox_new(u8, u8, u8, u8, u8, u8, u8, u8, i16, i16);
DLLINCLUDE Hitbox_t hbox_newsquished(u16, u16, u16, u16, i16, i16);
*/

#endif