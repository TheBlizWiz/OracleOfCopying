#include <stdlib.h>

#include "game/g_tile.h"

Tile_t *tile_new(TileClass_e tclass, i8 roomid, i16 gposx, i16 gposy, i16 elev, i16 flags, Hitbox_t hbox, Image_t **flrtex, Image_t **tiletex) {
    Tile_t *tile;
    tile = (Tile_t *) malloc(sizeof(Tile_t));

    tile->tclass = tclass;
    tile->roomid = roomid;
    tile->gposx = gposx;
    tile->gposy = gposy;
    tile->elev = elev;
    tile->flags = flags;
    tile->hbox = hbox;
    tile->ftex = flrtex;
    tile->ttex = tiletex;

    return tile;
}

// warning: this will not free fltex or tiletex
void tile_free(Tile_t *tile) {
    free(tile);
}