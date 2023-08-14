#ifndef G_PLAYER_H
#define G_PLAYER_H

#include "defs/d_common.h"

#include "g_entity.h"
#include "g_hitbox.h"

#include "render/r_image.h"

DLLINCLUDE typedef struct Player Player_t;

struct Player {

    // entity used for physics
    Entity_t ent;

    // player hitbox
    // see g_hitbox.h
    Hitbox_t hbox;

    // point on screen that corresponds with the top-left most pixel of the texture to draw
    Coordinate rdrpt;

    // what direction the player is facing
    // determines which sprite needs to draw
    // eg: if direction is up, and sprite is up, draw next animation frame
    //     if direction is up, and sprite is left, change to up player sprite
    // TODO: should this be set by player velocity or directly from the controls?
    u8 direction;

    // pointer to Image_t * in hashmap that corresponds with the player on screen
    Image_t **tex;

    double actiontimers[MAX_ACTIONS];
};

DLLINCLUDE Player_t *player_new(Point3 pos, Hitbox_t hbox, Image_t **tex);
DLLINCLUDE Hitbox_t player_newhbox();

DLLINCLUDE Error_t player_handleinput(App_t *app, Player_t *player, double dt);

DLLINCLUDE Vector3 player_calcforce(Player_t *player);
DLLINCLUDE Error_t player_capvelocity(Player_t *player);

DLLINCLUDE Error_t player_free(Player_t *player);

#endif