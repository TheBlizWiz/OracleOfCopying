#include "g_player.h"
#include "defs/d_constants.h"

Player_t *player_new(Point3 pos, Hitbox_t hbox, Image_t **tex) {
    Player_t *player = (Player_t *) malloc(sizeof(Player_t));
    if (player) {

        player->ent.mass = PLAYER_MASS;
        player->ent.force = (Vector3){ 0.0 };
        player->ent.position = pos;
        player->ent.velocity = (Vector3){ 0.0 };
        player->ent.acceleration = (Vector3){ 0.0 };

        player->direction = NORTH;
        player->rdrpt = (SDL_Point){ 0 };
        player->hbox = hbox;
        player->tex = tex;

        return player;
    }
    else {
        errprintf("ERROR: no malloc space for new player\n");
        return NULLADDR;
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