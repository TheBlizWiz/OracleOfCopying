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


Room_t *room_new(u64 tags, u8 id);
Error_t room_free(Room_t *room, App_t *app);
Error_t room_draw(Room_t *room, App_t *app);
Error_t room_drawfloor(Room_t *room, App_t *app);
Error_t room_drawtiles(Room_t *room, App_t *app);

#endif