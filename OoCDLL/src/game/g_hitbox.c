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

// TODO: this is dumb
Hitbox_t hbox_newdefault() {
    Hitbox_t hb = { 0 };
    hb.B.x = 32;
    hb.C.y = 32;
    hb.D.x = 32;
    hb.D.y = 32;
    hb.E.z = 32;
    hb.F.x = 32;
    hb.F.z = 32;
    hb.G.y = 32;
    hb.G.z = 32;
    hb.H.x = 32;
    hb.H.y = 32;
    hb.H.z = 32;
    return hb;
}