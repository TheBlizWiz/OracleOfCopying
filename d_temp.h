#ifndef D_TEMP_H
#define D_TEMP_H

#include <stdbool.h>

#include "d_common.h"
#include "d_string.h"
#include "g_hitbox.h"

typedef struct {
    String_t name;
    i16 elevation;
    Hitbox_t hitbox;
    bool hasalpha;
    String_t basetex, alphatex, floortex;
} StaticTile;

StaticTile *stctile_new(String_t nme, i16 elv, Hitbox_t hbox, bool hasalp, String_t btex, String_t atex, String_t ftex);
void stctile_free(StaticTile *stct);
void stctile_printf(StaticTile *stct);

#endif