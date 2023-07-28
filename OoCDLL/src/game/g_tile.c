#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "defs/d_constants.h"

#include "game/g_tile.h"

TileArray_t *tilearr_new(Size_t len) {
    Size_t tmp1 = len * sizeof(Tile_t);
    Size_t tmp2 = sizeof(TileArray_t) + tmp1;

    TileArray_t *tarr = (TileArray_t *) malloc(tmp2);

    if (tarr) {
        zeroset(tarr, tmp1);
        tarr->alloc = tmp2;
        tarr->len = len;
        return tarr;
    }
    else {
        errprintf("ERROR: No malloc space for new TileArray_t\n");
        return NULLADDR;
    }
}

Error_t tilearr_free(TileArray_t *tarr) {
    if (tarr) {
        free(tarr);
        return (Error_t) ERROR_NOERROR;
    }
    else {
        errprintf("ERROR: TileArray_t * is null, can't free\n");
        return (Error_t) ERROR_ISNULLADDR;
    }
}

Error_t tile_set(Tile_t tile, u32 tid, TileType_e tty, u8 col, i16 e, i16 f, SDL_Texture *ftex, SDL_Texture *ttex) {
    tile.tileid = tid;
    tile.ttype = tty;
    tile.collision = col;
    tile.elev = e;
    tile.flags = f;
    tile.floortex = ftex;
    tile.tiletex = ttex;
    return (Error_t) ERROR_NOERROR;
}