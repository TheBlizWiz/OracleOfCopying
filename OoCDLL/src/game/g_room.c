#include <string.h>

#include "defs/d_common.h"
#include "defs/d_utils.h"
#include "defs/d_macros.h"
#include "engine/e_app.h"
#include "libs/csv/csv.h"
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

Error_t room_load(Room_t *room, TileArray_t *tileset, const wchar_t *fpath) {
    if (room) {
        char *row;
        const char *col;
        int tid, rownum = 0, colnum = 0;
        Tile_t tgt = { 0 };
        CsvHandle hdl = CsvOpen(fpath);
        if (hdl) {
            while (row = CsvReadNextRow(hdl)) {
                while (col = CsvReadNextCol(row, hdl)) {
                    tid = atoi(col);
                    tgt.tileid = tid;

                    Size_t idx;
                    vec_search(tileset, idx, &tgt, tile_compare);

                    if (idx != -1) {
                        room->tiles[rownum][colnum] = (Tile_t **) &tileset;
                    }
                    else {
                        errprintf("ERROR: couldn't find Tile_t with id %d\n", tid);
                        room->tiles[rownum][colnum] = NULLADDR;
                    }

                    colnum++;
                }
                rownum++;
            }

            CsvClose(hdl);
            return ERROR_NOERROR;
        }
        else {
            errprintf("ERROR: Couldn't open .dg file\n");
            return ERROR_FILE_NOTFOUND;
        }
    }
    else {
        errprintf("ERROR: Room_t *room is null");
        return ERROR_ISNULLADDR;
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

Error_t room_draw(Room_t *room, Hashmap_t **atlasmap, App_t *app) {
    Error_t e1 = room_drawfloor(room, atlasmap, app);
    Error_t e2 = room_drawtile(room, atlasmap, app);
    return e1 + e2;
}

Error_t room_drawfloor(Room_t *room, Hashmap_t **atlasmap, App_t *app) {
    Error_t e = ERROR_NOERROR, tmp = ERROR_NOERROR;
    Coordinate c = { 0 };
    for (u8 y = 0; y < ROOM_SIZE_Y; y++) {
        for (u8 x = 0; x < ROOM_SIZE_X; x++) {
            tmp = tile_drawfloor(*(room->tiles[x][y]), atlasmap, c, app);

            if (tmp) {
                errprintf("ERROR: room_drawfloor threw an error, code %lld\n", e);
            }

            e += tmp;
            tmp = ERROR_NOERROR;
            c.x += TILE_PX_SIZE_X;
        }
        c.y += TILE_PX_SIZE_Y;
    }
    return e;
}

Error_t room_drawtile(Room_t *room, Hashmap_t **atlasmap, App_t *app) {
    Error_t e = ERROR_NOERROR, tmp = ERROR_NOERROR;
    Coordinate c = { 0 };
    for (u8 y = 0; y < ROOM_SIZE_Y; y++) {
        for (u8 x = 0; x < ROOM_SIZE_X; x++) {
            tmp = tile_drawtile(*(room->tiles[x][y]), atlasmap, c, app);

            if (!tmp) {
                errprintf("ERROR: room_drawtile threw an error, code %lld\n", e);
            }

            e += tmp;
            tmp = ERROR_NOERROR;
            c.x += TILE_PX_SIZE_X;
        }
        c.y += TILE_PX_SIZE_Y;
    }
    return e;
}