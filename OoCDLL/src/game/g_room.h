#ifndef G_ROOM_H
#define G_ROOM_H

#include "defs/d_common.h"
#include "defs/d_constants.h"
#include "game/g_tile.h"

DLLINCLUDE typedef struct Room Room_t;

struct Room {
    u64 tags;
    u8 id;
    Tile_t *tiles[ROOM_SIZE_X][ROOM_SIZE_Y];
};

#endif