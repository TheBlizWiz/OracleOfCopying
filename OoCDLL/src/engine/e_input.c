#include "e_input.h"

Vector3 player_handleinput(App_t *app /*, Player_t *player */) {
    Vector3 v = { 0.0 };
    if (app) {
        if (app->keys[SDL_SCANCODE_UP] || app->keys[SDL_SCANCODE_W]) {
            v.y = PLAYER_MOVE_Y_FORCE;
        }
        if (app->keys[SDL_SCANCODE_LEFT] || app->keys[SDL_SCANCODE_A]) {
            v.x = -PLAYER_MOVE_X_FORCE;
        }
        if (app->keys[SDL_SCANCODE_DOWN] || app->keys[SDL_SCANCODE_S]) {
            v.y = -PLAYER_MOVE_Y_FORCE;
        }
        if (app->keys[SDL_SCANCODE_RIGHT] || app->keys[SDL_SCANCODE_D]) {
            v.x = PLAYER_MOVE_X_FORCE;
        }
        if (app->keys[SDL_SCANCODE_SPACE] /* && player has jump item */) {
            v.z = PLAYER_MOVE_Z_FORCE;
        }

        return v;
    }
    else {
        errprintf("ERROR: App_t *app is null...\n");
        return v;
    }
}