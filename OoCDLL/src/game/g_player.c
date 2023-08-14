#include "g_player.h"
#include "math/m_math.h"
#include "defs/d_constants.h"
#include "defs/d_macros.h"

Player_t *player_new(Point3 pos, Hitbox_t hbox, Image_t **tex) {
    Player_t *player = (Player_t *) malloc(sizeof(Player_t));
    if (player) {

        zeroset(player, sizeof(Player_t));

        player->ent.mass = PLAYER_MASS;
        player->ent.prevstate.position = pos;
        player->ent.currstate.position = pos;
        player->direction = NORTH;
        player->hbox = hbox;
        player->tex = tex;

        return player;
    }
    else {
        errprintf("ERROR: no malloc space for new player\n");
        return NULLADDR;
    }

}

Hitbox_t player_newhbox() {
    Hitbox_t hb = hbox_new(PLAYER_HITBOX_DIMENSIONS);
    return hb;
}

Error_t player_handleinput(App_t *app, Player_t *player, double dt) {
    if (app) {
        if (player) {
            if (app->keys[SDL_SCANCODE_UP] || app->keys[SDL_SCANCODE_W]) {
                player->direction = NORTH;
                player->actiontimers[ACTIONS_PLAYER_MOVE_NORTH] += dt;
            }
            else {
                player->actiontimers[ACTIONS_PLAYER_MOVE_NORTH] = 0.0;
            }

            if (app->keys[SDL_SCANCODE_LEFT] || app->keys[SDL_SCANCODE_A]) {
                player->direction = WEST;
                player->actiontimers[ACTIONS_PLAYER_MOVE_WEST] += dt;
            }
            else {
                player->actiontimers[ACTIONS_PLAYER_MOVE_WEST] = 0.0;
            }

            if (app->keys[SDL_SCANCODE_DOWN] || app->keys[SDL_SCANCODE_S]) {
                player->direction = SOUTH;
                player->actiontimers[ACTIONS_PLAYER_MOVE_SOUTH] += dt;
            }
            else {
                player->actiontimers[ACTIONS_PLAYER_MOVE_SOUTH] = 0.0;
            }

            if (app->keys[SDL_SCANCODE_RIGHT] || app->keys[SDL_SCANCODE_D]) {
                player->direction = EAST;
                player->actiontimers[ACTIONS_PLAYER_MOVE_EAST] += dt;
            }
            else {
                player->actiontimers[ACTIONS_PLAYER_MOVE_EAST] = 0.0;
            }

            if (app->keys[SDL_SCANCODE_SPACE] /* && player has jump item */) {
                player->actiontimers[ACTIONS_PLAYER_MOVE_JUMP] += dt;
            }
            else {
                player->actiontimers[ACTIONS_PLAYER_MOVE_JUMP] = 0.0;
            }

            return ERROR_NOERROR;
        }
        else {
            errprintf("ERROR: Player_t *player is null...\n");
            return ERROR_ISNULLADDR;
        }
    }
    else {
        errprintf("ERROR: App_t *app is null...\n");
        return ERROR_ISNULLADDR;
    }
}

Vector3 player_calcforce(Player_t *player) {

    // function to determine player forces for x and y axes (z is handled elsewhere)
    // t = time from player->actiontimers (amt of time since action started / button pressed)
    // p = player position 
    // v = player velocity
    // a = player acceleration
    // m = player mass
    // F = player force
    // q = y axis magic number
    // w = x axis magic number
    // 
    // f(t) = p(t) = ((-q/2)/(w/2))(ln(wt+1))+(qt) <--- integral v(t)
    // f'(t) = v(t) = (-q/w)/(t + (1/w)) + q <-- base function
    // f''(t) = a(t) = (qw)/(wt+q)^2 dt <-- d/dt v(t) 
    // 
    // but we want to cap v(t) to be at MAX_PLAYER_SPEED
    // if( v(t) > MAX_PLAYER_SPEED) v(t) = MAX_PLAYER_SPEED
    // a(t) = 0
    // 
    // therefore...
    // F = m * a
    // F = PLAYER_MASS * a(t)
    // // F = (PLAYER_MASS * (2t + 1)) / 200
    // return F * PLAYER_MOVE_XY_FORCE

    Vector3 outputF = { 0.0 };

    const double q = PLAYER_MOVE_Y_MAGIC_NUMBER;
    const double w = PLAYER_MOVE_X_MAGIC_NUMBER;
    const double wsq = PLAYER_MOVE_X_MAGIC_NUMBER * PLAYER_MOVE_X_MAGIC_NUMBER;

    const double d = PLAYER_MASS * q * w;

    //if (player->ent.currstate.velocity.x < PLAYER_MOVE_X_MAX_VELOCITY) {
        outputF.x += d * quadratic(wsq, w, 1.0, player->actiontimers[ACTIONS_PLAYER_MOVE_EAST]) * PLAYER_MOVE_X_FORCE;
   //}
   // else {
   //     outputF.x = 0.0;
   // }

   // if (player->ent.currstate.velocity.x > -PLAYER_MOVE_X_MAX_VELOCITY) {
        outputF.x -= d * quadratic(wsq, w, 1.0, player->actiontimers[ACTIONS_PLAYER_MOVE_WEST]) * PLAYER_MOVE_X_FORCE;
   // }
  //  else {
  //      outputF.x = 0.0;
  //  }

  //  if (player->ent.currstate.velocity.y < PLAYER_MOVE_Y_MAX_VELOCITY) {
        outputF.y += d * quadratic(wsq, w, 1.0, player->actiontimers[ACTIONS_PLAYER_MOVE_SOUTH]) * PLAYER_MOVE_Y_FORCE;
   // }
   // else {
   //     outputF.y = 0.0;
   // }

  //  if (player->ent.currstate.velocity.y > -PLAYER_MOVE_Y_MAX_VELOCITY) {
        outputF.y -= d * quadratic(wsq, w, 1.0, player->actiontimers[ACTIONS_PLAYER_MOVE_NORTH]) * PLAYER_MOVE_Y_FORCE;
   // }
  //  else {
  //      outputF.y = 0.0;
  //  }

    return outputF;
}

Error_t player_capvelocity(Player_t *player) {
    if (player) {
        if (player->ent.currstate.velocity.x > PLAYER_MOVE_X_MAX_VELOCITY) {
            player->ent.currstate.velocity.x = PLAYER_MOVE_X_MAX_VELOCITY;
        }
        if (player->ent.currstate.velocity.x < -PLAYER_MOVE_X_MAX_VELOCITY) {
            player->ent.currstate.velocity.x = -PLAYER_MOVE_X_MAX_VELOCITY;
        }
        if (player->ent.currstate.velocity.y > PLAYER_MOVE_Y_MAX_VELOCITY) {
            player->ent.currstate.velocity.y = PLAYER_MOVE_Y_MAX_VELOCITY;
        }
        if (player->ent.currstate.velocity.y < -PLAYER_MOVE_Y_MAX_VELOCITY) {
            player->ent.currstate.velocity.y = -PLAYER_MOVE_Y_MAX_VELOCITY;
        }
        return ERROR_NOERROR;
    }
    else {
        errprintf("ERROR: Player_t *player is null\n");
        return ERROR_ISNULLADDR;
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