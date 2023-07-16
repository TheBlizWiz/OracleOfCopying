#ifndef G_ROOM_H
#define G_ROOM_H

#include "defs/d_common.h"
#include "defs/d_constants.h"
#include "game/g_tile.h"

typedef struct {
    u64 tags;
    u8 id;
    Tile_t *tiles[ROOM_SIZE_X][ROOM_SIZE_Y];
} Room_t;

Room_t *room_new(u64 tags, u8 roomid);
Error_t room_free(Room_t *room);

#endif