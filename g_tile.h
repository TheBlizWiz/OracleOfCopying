#ifndef G_TILE_H
#define G_TILE_H

#include <stdbool.h>

#include "d_common.h"
#include "d_constants.h"
#include "g_enums.h"

    typedef struct {
        TileType_e tiletype;
        void *tileptr;
    } Tile_t;

    typedef struct {
        TileType_e type;

        String_t *name;
        Hitbox_t hitbox;
        i32 elevation;
        bool hasalpha;

        Image_t *basetex;
        Image_t *alptex;
        Image_t *flrtex;
    } StaticTile_t;



    typedef struct {
        TileType_e type;

        String_t *name;
        Hitbox_t hitbox;
        i32 elevation;
        bool hasalpha;

        Image_t *basetex;
        Image_t *alptex;
        Image_t *flrtex;

        bool isalive;
        
    } DynamicTile_t;



#endif