#ifndef G_TILE_H
#define G_TILE_H

#include "SDL.h"

#include "defs/d_common.h"
#include "game/g_enums.h"
#include "game/g_hitbox.h"

DLLINCLUDE typedef struct Tile Tile_t;
DLLINCLUDE typedef struct TileArray TileArray_t;

// Static, non-interactive building blocks of dungeons
// Has two parts - the floor and the tile
// The floor is the texture on the ground and is rendered first
// Then the tile is drawn on top of it
// If the tile texture is the same size / nontransparent none of the floor is visible
// but thats ok
struct Tile {
    // numerical id of this tile
    // not entirely sure what i can use this for yet
    // but perhaps as a fast way to look up tile information?
    u32 tileid;

    // type of this tile, refer to g_enums.h
    TileType_e ttype;

    // is this tile solid
    // if not, no need to do actual hitbox math
    boolean collision;

    // hitbox of the tile
    Hitbox_t hbox;

    // flags for this tile
    // usused but maybe useful later?
    u16 flags;

    // pointer to place in Hashmap where the floor texture of the tile is
    SDL_Texture **floortex;

    // pointer to place in Hashmap where the main tile block/wall/etc texture is
    SDL_Texture **tiletex;
};

// Array of Tile_t
// This is not the tiles in your Room_t
// Instead these are a sort of "master pallete" of all tiles needed in the dungeon
// Rooms are then made of a 2-d array of pointers to these tiles 
// That way if a tile gets repeated a lot (say like a block, wall, or an empty tile) we don't
// have like 250 copies of it in memory
// 
// Load these from the dungeon file before building rooms
// and only free them when the dungeon is exited
struct TileArray {
    Size_t len;
    Size_t alloc;
    Tile_t tiles[];
};

TileArray_t *tilearr_new(Size_t len);
Error_t tile_set(Tile_t *tile, u32 tid, int tty, boolean col, u16 f, SDL_Texture **ftx, SDL_Texture **ttx);
Error_t *tilearr_free(TileArray_t *tarr);

Error_t tile_drawfloor(Tile_t *tile, Coordinate c, App_t *app);
Error_t tile_drawtile(Tile_t *tile, Coordinate c, App_t *app);

#endif