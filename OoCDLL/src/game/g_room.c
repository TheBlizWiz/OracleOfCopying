#include <string.h>

#include "defs/d_macros.h"
#include "engine/e_app.h"
#include "g_room.h"
#include "g_tile.h"

Room_t *room_new(u64 t, u8 id) {
    Room_t *room = (Room_t *) malloc(sizeof(Room_t));
    if (room) {
        zeroset(room, sizeof(Room_t));
        room->tags = t;
        room->id = id;
        return room;
    }
    else {
        errprintf("ERROR: no malloc space for new Room_t\n");
        return NULLADDR;
    }
}

Error_t room_free(Room_t *room) {
    if (room) {
        free(room);
        return ERROR_NOERROR;
    }
    else {
        errprintf("ERROR: Room_t *room is null, can't free\n");
        return ERROR_ISNULLADDR;
    }
}

Error_t room_draw(Room_t *room, App_t *app) {
    Error_t e1 = room_drawfloor(room, app);
    Error_t e2 = room_drawtile(room, app);
    return e1 + e2;
}

Error_t room_drawfloor(Room_t *room, App_t *app) {
    Error_t e = ERROR_NOERROR;
    Coordinate c = { 0 };
    for (u8 y = 0; y < ROOM_SIZE_Y; y++) {
        for (u8 x = 0; x < ROOM_SIZE_X; x++) {
            e += tile_drawfloor(room->tiles[x][y], c, app);
            c.x += TILE_PX_SIZE_X;
        }
        c.y += TILE_PX_SIZE_Y;
    }
    return e;
}

Error_t room_drawtile(Room_t *room, App_t *app) {
    Error_t e = ERROR_NOERROR;
    Coordinate c = { 0 };
    for (u8 y = 0; y < ROOM_SIZE_Y; y++) {
        for (u8 x = 0; x < ROOM_SIZE_X; x++) {
            e += tile_drawtile(room->tiles[x][y], c, app);
            c.x += TILE_PX_SIZE_X;
        }
        c.y += TILE_PX_SIZE_Y;
    }
    return e;
}