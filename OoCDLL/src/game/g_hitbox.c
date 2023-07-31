#include <stdlib.h>
#include <string.h>

#include "defs/d_common.h"
#include "defs/d_constants.h"
#include "game/g_hitbox.h"

Hitbox_t hbox_new(Point3 a, Point3 b, Point3 c, Point3 d, Point3 e, Point3 f, Point3 g, Point3 h) {
    Hitbox_t hb = { 0 };
    hb.A = a;
    hb.B = b;
    hb.C = c;
    hb.D = d;
    hb.E = e;
    hb.F = f;
    hb.G = g;
    hb.H = h;
    return hb;
}