#include "g_player.h"
#include "defs/d_constants.h"
#include "defs/d_macros.h"

Player_t *player_new(Point3 pos, Hitbox_t hbox, Image_t **tex) {
    Player_t *player = (Player_t *) malloc(sizeof(Player_t));
    if (player) {

        player->ent.mass = PLAYER_MASS;
        player->ent.force = (Vector3){ 0.0 };

        player->ent.prevstate.position = pos;
        player->ent.prevstate.velocity = (Vector3){ 0.0 };
        player->ent.prevstate.acceleration = (Vector3){ 0.0 };

        player->ent.currstate.position = pos;
        player->ent.currstate.velocity = (Vector3){ 0.0 };
        player->ent.currstate.acceleration = (Vector3){ 0.0 };

        player->direction = NORTH;
        player->rdrpt = (Coordinate){ 0 };
        player->hbox = hbox;
        player->tex = tex;

        return player;
    }
    else {
        errprintf("ERROR: no malloc space for new player\n");
        return NULLADDR;
    }

}

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

Error_t player_free(Player_t *player) {
    if (player) {
        free(player);
        return ERROR_NOERROR;
    }
    else {
        errprintf("ERROR: can't free player, player is null\n");
        return ERROR_ISNULLADDR;
    }
}