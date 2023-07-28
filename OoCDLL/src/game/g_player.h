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
    SDL_Point rdrpt;

    // what direction the player is facing
    // determines which sprite needs to draw
    // eg: if direction is up, and sprite is up, draw next animation frame
    //     if direction is up, and sprite is left, change to up player sprite
    // TODO: should this be set by player velocity or directly from the controls?
    u8 direction;

    // needed to get keyboard inputs for physics
    // maybe theres a better way to do this but after mulling it over
    // for an hour this is the only way i can think to do it
    App_t **app;

    Vector3(*forcehandler)(App_t *app, Entity_t *ent);

    // pointer to Image_t * in hashmap that corresponds with the player on screen
    Image_t **tex;
};

DLLINCLUDE Player_t *player_new();

#endif