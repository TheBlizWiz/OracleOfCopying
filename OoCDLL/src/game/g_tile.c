#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "defs/d_constants.h"
#include "defs/d_macros.h"

#include "game/g_tile.h"
#include "render/r_sdl.h"

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

Error_t tile_set(Tile_t *tile, u32 tid, int tty, boolean col, u16 f, SDL_Texture **ftx, SDL_Texture **ttx) {
    if (tile) {
        tile->tileid = tid;
        tile->ttype = tty;
        tile->collision = col;
        tile->flags = f;
        tile->floortex = ftx;
        tile->tiletex = ttx;
        return (Error_t) ERROR_NOERROR;
    }
    else {
        errprintf("ERROR: Tile_t *tile is null, can't set\n");
        return ERROR_ISNULLADDR;
    }
}

Error_t tile_drawfloor(Tile_t *tile, Coordinate c, App_t *app) {
    if (app) {
        if (tile) {
            return (Error_t) SDL_BlitImage(app, tile->floortex, c, 0, TF_NONE);
        }
        else {
            errprintf("ERROR: Tile_t *tile is null, can't draw Tile_t\n");
            return ERROR_ISNULLADDR;
        }
    }
    else {
        errprintf("ERROR: App_t *app is null, can't draw Tile_t\n");
        return ERROR_ISNULLADDR;
    }
}

Error_t tile_drawtile(Tile_t *tile, Coordinate c, App_t *app) {
    if (app) {
        if (tile) {
            return (Error_t) SDL_BlitImage(app, tile->tiletex, c, 0, TF_NONE);
        }
        else {
            errprintf("ERROR: Tile_t *tile is null, can't draw Tile_t\n");
            return ERROR_ISNULLADDR;
        }
    }
    else {
        errprintf("ERROR: App_t *app is null, can't draw Tile_t\n");
        return ERROR_ISNULLADDR;
    }
}