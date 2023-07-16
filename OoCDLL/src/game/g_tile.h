#ifndef G_TILE_H
#define G_TILE_H

#include "SDL.h"

#include "defs/d_common.h"
#include "game/g_enums.h"
#include "game/g_hitbox.h"


typedef struct {
    TileClass_e tclass;
    u8 collision;
    i16 elev;
    i16 flags;
    SDL_Texture *ftex;
    SDL_Texture *ttex;
} Tile_t;

Tile_t *tile_new(TileClass_e tclass, u8 collision, i16 elevation, i16 flags, SDL_Texture *floortex, SDL_Texture *tiletex);
Error_t tile_free(Tile_t *tile);

#endif