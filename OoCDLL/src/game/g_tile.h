#ifndef G_TILE_H
#define G_TILE_H

#include "SDL.h"

#include "defs/d_common.h"
#include "game/g_enums.h"
#include "game/g_hitbox.h"

DLLINCLUDE typedef struct Tile Tile_t;
DLLINCLUDE typedef struct TileArray TileArray_t;

struct Tile {
    u32 tileid;
    TileType_e ttype;
    u8 collision;
    i16 elev;
    i16 flags;
    SDL_Texture *floortex;
    SDL_Texture *tiletex;
};

struct TileArray {
    Size_t len;
    Size_t alloc;
    Tile_t tiles[];
};

#endif