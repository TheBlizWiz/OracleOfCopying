#include <string.h>

#include "engine/e_app.h"
#include "g_room.h"
#include "g_tile.h"

Error_t room_draw(Room_t *room, App_t *app) {
    Error_t e1 = room_drawfloor(room, app);
    Error_t e2 = room_drawtiles(room, app);
    return e1 + e2;
}

Error_t room_drawfloor(Room_t *room, App_t *app) {
    Error_t e = ERROR_NOERROR;
    Coordinate c = { 0 };
    for (u8 y = 0; y < ROOM_SIZE_Y, y++) {
        for (u8 x = 0; x < ROOM_SIZE_X; x++) {
            e += tile_drawfloor(room->tiles[x][y], c, app);
            c.x += TILE_PX_SIZE_X;
        }
        c.y += TILE_PX_SIZE_Y;
    }
    return e;
}

Error_t room_drawtiles(Room_t *room, App_t *app) {
    Error_t e = ERROR_NOERROR;
    Coordinate c = { 0 };
    for (u8 y = 0; y < ROOM_SIZE_Y, y++) {
        for (u8 x = 0; x < ROOM_SIZE_X; x++) {
            e += tile_drawtiles(room->tiles[x][y], c, app);
            c.x += TILE_PX_SIZE_X;
        }
        c.y += TILE_PX_SIZE_Y;
    }
    return e;
}