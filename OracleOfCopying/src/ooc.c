#include "ooc.h"

#include <string.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {

    App_t *ooc;

    boolean run = 1;
    SDL_Event evt;
    SDL_Texture *atlas;
    Hashmap_t *atlasmap;
    Error_t e;
    Player_t *player;

    Room_t *room;
    TileType_e ttype = 0;

    State_t tmpstate;
    Coordinate c;

    TileArray_t tileset;

    double currenttime = 0.0;
    double newtime = 0.0;
    double dt = 0.01;
    double accumulator = 0.0;
    double frametime = 0.0;
    double interp = 0.0;

    ooc = app_new();
    e = app_start(ooc, SDL_INIT_EVERYTHING, SDL_WINDOW_ALLOW_HIGHDPI, SDL_RENDERER_ACCELERATED, SCREEN_SIZE_X, SCREEN_SIZE_Y);

    currenttime = (double) SDL_GetTicks64() / 1000.0;


    if (e != ERROR_NOERROR) {
        errprintf("ERROR: something wrong with app_start\n");
        return 1;
    }

    atlas = IMG_LoadTexture(ooc->rdr, "C:\\Users\\thebl\\source\\repos\\OracleOfCopying\\OracleOfCopying\\textures\\atlases\\dancingdragondungeon\\atlasimg.qoi");
    if (!atlas) {
        errprintf("ERROR: atlas is null... uhhh\n");
        return 2;
    }

    atlasmap = hashmap_new(sizeof(Image_t), 0, 0, 0, hash_imghash, hash_imgcmp, hash_imgfree, NULL);
    if (!atlasmap) {
        errprintf("ERROR: something went wrong with hashmap_new\n");
        return 3;
    }

    e = atlas_load(atlasmap, "C:\\Users\\thebl\\source\\repos\\OracleOfCopying\\OracleOfCopying\\textures\\atlases\\dancingdragondungeon\\atlasdata.json", atlas);
    if (e != ERROR_NOERROR) {
        errprintf("ERROR: something wrong with atlas_load\n");
    }

    memset(&tileset, 0, sizeof(tileset));

    e = tile_load("C:\\Users\\thebl\\source\\repos\\OracleOfCopying\\tiles.json", &tileset, &atlasmap);
    if (e != ERROR_NOERROR) {
        errprintf("ERROR: something wrong with tile_load\n");
        return 98;
    }

    room = room_new(0, 0);
    if (!room) {
        errprintf("ERROR: no malloc space for new room_t");
        return 97;
    }

    // dont remove that L in front, this is a widechar string for the csv reader
    e = room_load(room, &tileset, L"C:\\Users\\thebl\\source\\repos\\OracleOfCopying\\dungeon.dg");
    if (e != ERROR_NOERROR) {
        errprintf("ERROR: something went wrong with room_load, code %lld\n", e);
        return 99;
    }

    Image_t *whiteball = atlas_getimage(&atlasmap, "whiteball.qoi");
    if (!whiteball) {
        errprintf("ERROR: whiteball.qoi is null\n");
        return 10;
    }

    player = player_new((Point3) {
        .x = 32.0, .y = 32.0, .z = 0.0
    }, player_newhbox(), whiteball);

    while (run) {
        SDL_RenderClear(ooc->rdr);

        room_draw(room, &atlasmap, ooc);

        e = app_doevents(ooc, &evt);

        if (e == ERROR_DOEVENTS_TIMETOQUIT) {
            run = 0;
            break;
        }

        newtime = (double) SDL_GetTicks64() / 1000.0;
        frametime = newtime - currenttime;

        if (frametime > 0.5) {
            frametime = 0.5;
        }

        currenttime = newtime;

        accumulator += frametime;

        while (accumulator >= dt) {

            player_handleinput(ooc, player, dt);

            //foreach (Entity ent) {
            //     state_update(&ent);
            //     phys_resetforces(&ent);
            //     phys_calcobjectforces(&ent, ent->calcforces(&ent)); <-- TODO: how to do with function pointers?
            //     phys_calcenvironmentforces(&ent);
            //     phys_integrate(&ent);
            //     do_collision(&ent);
            // }

            state_update(&player->ent);
            phys_resetforces(&player->ent);
            phys_calcobjectforces(&player->ent, player_calcforce(player));
            phys_calcenvironmentforces(&player->ent);
            phys_integrate(&player->ent, dt);

            if (player->ent.currstate.position.x > SCREEN_SIZE_X - 32) {
                player->ent.currstate.position.x = SCREEN_SIZE_X - 32;
            }
            if (player->ent.currstate.position.x < 0.0) {
                player->ent.currstate.position.x = 0.0;
            }
            if (player->ent.currstate.position.y > SCREEN_SIZE_Y - 32) {
                player->ent.currstate.position.y = SCREEN_SIZE_Y - 32;
            }
            if (player->ent.currstate.position.y < 0.0) {
                player->ent.currstate.position.y = 0.0;
            }

            player_capvelocity(player);

            errprintf("%f, %f, %f, %f\n", currenttime, player->ent.currstate.position.x, player->ent.currstate.position.y, player->ent.currstate.position.z);
            accumulator -= dt;
        }

        interp = accumulator / dt;

        // foreach (Entity ent) {
        //     tmpstate = phys_interpolate(ent, interp);
        //     c = SDL_WorldPosToScreenPos(tmpstate.position);
        //     SDL_BlitImage(ooc, texture, c, 0, TF);
        // }

        tmpstate = phys_interpolate(&player->ent, interp);
        c = SDL_WorldPosToScreenPos(tmpstate.position);

        switch (player->direction) {
            case NORTH:
                SDL_BlitImage(ooc, whiteball, c, 0, TF_NONE);
                break;
            case SOUTH:
                SDL_BlitImage(ooc, whiteball, c, 0, TF_ROT, 180.00);
                break;
            case EAST:
                SDL_BlitImage(ooc, whiteball, c, 0, TF_ROT, 90.00);
                break;
            case WEST:
                SDL_BlitImage(ooc, whiteball, c, 0, TF_ROT, 270.00);
                break;
        }

        SDL_RenderPresent(ooc->rdr);
        SDL_Delay(15);
    }

    player_free(player);

    vec_deinit(&tileset);

    hashmap_free(atlasmap);
    SDL_DestroyTexture(atlas);
    room_free(room);

    app_stop(ooc, SDL_INIT_EVERYTHING);
    app_free(ooc);

    return 0;
}