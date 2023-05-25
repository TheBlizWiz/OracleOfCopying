#include <stdlib.h>

#include "g_tile.h"

Tile_t *tile_new(TileClass_e tclass, i8 roomid, i16 gposx, i16 gposy, i16 elev, i16 flags, i16 hbox, Image_t **flrtex, Image_t **tiletex) {
    Tile_t *tile;
    tile = (Tile_t *) malloc(sizeof(Tile_t));

    tile->tclass  = tclass;
    tile->roomid  = roomid;
    tile->gposx   = gposx;
    tile->gposy   = gposy;
    tile->elev    = elev;
    tile->flags   = flags;
    tile->hbox    = hbox;
    tile->flrtex  = flrtex;
    tile->tiletex = tiletex;

    return tile;
}

// warning: this will not free fltex or tiletex
void tile_free(Tile_t *tile) {
    free(tile);
}