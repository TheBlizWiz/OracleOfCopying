#include <string.h>

#include "g_room.h"

Room_t *room_new(u64 tags, u8 roomid) {
    Room_t *room = malloc(sizeof(Room_t));
    if (room) {
        room->tags = tags;
        room->id = roomid;

        memset(room->tiles, 0, sizeof(room->tiles));

        return room;
    }
    else {
        errprintf("ERROR: no malloc space for new Room_t\n");
        return NULLADDR;
    }
}

Error_t room_free(Room_t *room) {
    if (room) {
        Error_t e = ERROR_NOERROR;
        for (int i = 0; i < ROOM_SIZE_X; i++) {
            for (int j = 0; j < ROOM_SIZE_Y; j++) {
                e = tile_free(room->tiles[i][j]);
            }
            free(room);
            return e * ERROR_NOERROR;
         }
    }
    else {
        errprintf("ERROR: Room_t is null, can't free\n");
        return ERROR_ISNULLADDR;
    }
}