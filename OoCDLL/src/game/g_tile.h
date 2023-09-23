#ifndef G_TILE_H
#define G_TILE_H

#include "SDL.h"

#include "defs/d_common.h"
#include "game/g_enums.h"
#include "game/g_hitbox.h"
#include "libs/hashmap/hashmap.h"
#include "render/r_image.h"
#include "utils/u_array.h"

DLLINCLUDE typedef struct Tile Tile_t;


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
    u16 flags;

    // Image_t in Hashmap where the floor texture of the tile is
    Image_t **floortex;

    // Image_t in Hashmap where the main tile block/wall/etc texture is
    Image_t **tiletex;
};

DLLINCLUDE Tile_t *tile_new(u32, TileType_e, boolean, Hitbox_t, u16, Image_t *, Image_t *);
DLLINCLUDE Error_t tile_set(Tile_t *tile, u32 tid, int tty, boolean col, u16 f, Image_t *ftx, Image_t *ttx);

DLLINCLUDE Error_t tile_free(Tile_t *t);

DLLINCLUDE Error_t tile_drawfloor(Tile_t *tile, Coordinate c, App_t *app);
DLLINCLUDE Error_t tile_drawtile(Tile_t *tile, Coordinate c, App_t *app);
DLLINCLUDE int tile_compare(const void *Tile_t_a, const void *Tile_t_b);
DLLINCLUDE Error_t tile_load(const char *fpath, Array_t(Tile_t) tileset, Hashmap_t *atlasmap);

#endif