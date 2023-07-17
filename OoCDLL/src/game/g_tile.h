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
    TileClass_e tclass;
    u8 collision;
    i16 elev;
    i16 flags;
    SDL_Texture *ftex;
    SDL_Texture *ttex;
};

struct TileArray {
    Size_t len;
    Size_t alloc;
    Tile_t tiles[];
};


DLLINCLUDE Tile_t *tile_new(u32 tileid, TileClass_e tclass, u8 collision, i16 elevation, i16 flags, SDL_Texture *floortex, SDL_Texture *tiletex);
DLLINCLUDE i32 tile_cmp(const Tile_t *a, const Tile_t *b);
DLLINCLUDE Error_t tile_free(Tile_t *tile);

DLLINCLUDE TileArray_t *tilearr_new(Size_t len);
DLLINCLUDE Error_t *tilearr_add(Tile_t *tile);
DLLINCLUDE Error_t *tilearr_free(TileArray_t *tarr);
DLLINCLUDE Error_t *tilearr_sort(TileArray_t **tarr);


#endif