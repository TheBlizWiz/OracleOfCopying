#ifndef G_TILE_H
#define G_TILE_H

#include <defs/d_common.h>
#include "g_enums.h"
#include "g_hitbox.h"
#include <render/r_image.h>

/**
    Struct for Tiles, which are the building blocks of maps
    They are non interactable and not dynamic
    Every space should have a tile in the map

    You can make a "blank" tile by making a tile with a black
    or transparent ftex and setting it to be non solid
    If it's out of bounds, also set roomid to zero

    You can place Objects on top of Tiles
    To do this make a non-solid Tile with ttex set to
    NULLADDR and ftex to whatever the floor texture should be
    Then place your Object in the same grid position

    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    Fields:

    TileClass_e tclass: Refer to g_entity.h
                        Enum to store what class this tile is
                        Compared to Objects and Entities, this field is not as important
                        but still useful to quickly check if something is out of bounds, for instance

    i8 roomid: i8 value to store what Room this Tile is in, which is needed to make Rooms work. Very important!
               Fill with zero if this tile is out of bounds

    i16 gposx: X Grid position of this tile, see g_map.h for more info on grid position vs absolute position

    i16 gposy: Y Grid position of this tile

    i16 elev: Elevation of this tile, see g_map.h for more information on tile elevation

    i16 flags: Currently unused but is here if and when it might be needed, set to zero for now

    Hitbox_t hbox: Hitbox of this tile, see g_hitbox.h for more information on how Hitboxes work

    Image_t **ftex: Pointer to an already-allocated texture in memory
                    Make this point to the MegaTexture array so we can keep track of how many times Tiles reuse this texture
                    Refer to r_image.h and r_megaimage.h for more information

                    This is for the floor of the tile
                    If a Tile has a ttex that is non-transparent and is fully drawn over this won't be visible
                    But you should probably still fill in the floor texture anyway

    Image_t **ttex: Pointer to an already-allocated texture in memory
                    Make this point to the MegaTexture array so we can keep track of how many times Tiles reuse this texture
                    Refer to r_image.h and r_megaimage.h for more information

                    This is for the "tile" part of the Tile, like the texture for a wall or the decorative statue on a decoration tile
                    This field might not always be used, such as when you want an empty tile with just the floor
                    Other times, like with walls, this texture will cover up ftex

    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    Create new Tiles with tile_new(TileClass_e, i8, i16, i16, i16, i16, i16, Image_t **, Image_t **)
    Free Tiles with tile_free(Tile_t *)

*/
typedef struct {

    TileClass_e tclass;
    i8          roomid;
    i16         gposx;
    i16         gposy;
    i16         elev;
    i16         flags;
    Hitbox_t    hbox;
    Image_t   **ftex;
    Image_t   **ttex;

} Tile_t;

Tile_t *tile_new(TileClass_e, i8, i16, i16, i16, i16, i16, Image_t **, Image_t **);
void tile_free(Tile_t *);

#endif