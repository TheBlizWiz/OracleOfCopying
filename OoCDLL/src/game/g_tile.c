#include <stdlib.h>

#include "defs/d_constants.h"

#include "game/g_tile.h"

Tile_t *tile_new(u32 tid, TileClass_e tc, u8 coll, i16 e, i16 f, SDL_Texture *ft, SDL_Texture *tt) {
    Tile_t *tile = malloc(sizeof(Tile_t));
    if (tile) {
        tile->tileid = tid;
        tile->tclass = tc;
        tile->collision = coll;
        tile->elev = e;
        tile->flags = f;
        tile->ftex = ft;
        tile->ttex = tt;
        return tile;
    }
    else {
        errprintf("ERROR: no malloc space for new Tile_t\n");
        return NULLADDR;
    }
}

i32 tile_cmp(const Tile_t *a, const Tile_t *b) {
    return a->tileid - b->tileid;
}

Error_t tile_free(Tile_t *tile) {
    if (tile) {
        free(tile);
        return ERROR_NOERROR;
    }
    else {
        errprintf("ERROR: tile is null, can't free\n");
        return ERROR_ISNULLADDR;
    }
}

TileArray_t *tilearr_new(Size_t len) {
    TileArray_t *tarr = (TileArray_t *) malloc(sizeof(TileArray_t));
}

Error_t *tilearr_add(Tile_t *tile) {

}

Error_t *tilearr_sort(TileArray_t **tarr) {

}

Error_t *tilearr_free(TileArray_t *tarr) {

}
