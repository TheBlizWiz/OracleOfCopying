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
    TileArray_t *tileset;
    TileType_e ttype = 0;

    State_t tmpstate;
    Coordinate c;

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

    atlas = IMG_LoadTexture(ooc->rdr, "E:\\MSVC\\source\\repos\\OracleOfCopying\\OracleOfCopying\\textures\\atlases\\dancingdragondungeon\\atlasimg.qoi");
    if (!atlas) {
        errprintf("ERROR: atlas is null... uhhh\n");
        return 2;
    }

    atlasmap = hashmap_new(sizeof(Image_t), 0, 0, 0, hash_imghash, hash_imgcmp, hash_imgfree, NULL);
    if (!atlasmap) {
        errprintf("ERROR: something went wrong with hashmap_new\n");
        return 3;
    }

    e = atlas_load(atlasmap, "E:\\MSVC\\source\\repos\\OracleOfCopying\\OracleOfCopying\\textures\\atlases\\dancingdragondungeon\\atlasdata.json", atlas);
    if (e != ERROR_NOERROR) {
        errprintf("ERROR: something wrong with atlas_load\n");
    }

    Image_t *whiteball = atlas_getimage(atlasmap, "whiteball.qoi");
    Image_t *redball = atlas_getimage(atlasmap, "redball.qoi");

    Image_t *northwall = atlas_getimage(atlasmap, "ddd_walls_north.qoi");
    Image_t *southwall = atlas_getimage(atlasmap, "ddd_walls_south.qoi");
    Image_t *eastwall = atlas_getimage(atlasmap, "ddd_walls_east.qoi");
    Image_t *westwall = atlas_getimage(atlasmap, "ddd_walls_west.qoi");
    Image_t *nwwallcorner = atlas_getimage(atlasmap, "ddd_walls_innercorner_nw.qoi");
    Image_t *swwallcorner = atlas_getimage(atlasmap, "ddd_walls_innercorner_sw.qoi");
    Image_t *newallcorner = atlas_getimage(atlasmap, "ddd_walls_innercorner_ne.qoi");
    Image_t *sewallcorner = atlas_getimage(atlasmap, "ddd_walls_innercorner_se.qoi");
    Image_t *blank = atlas_getimage(atlasmap, "blank.qoi");

    Image_t *pitfloor = atlas_getimage(atlasmap, "ddd_floors_pit.qoi");
    Image_t *greenfloor = atlas_getimage(atlasmap, "ddd_floors_patterned_green.qoi");
    
    Image_t *block = atlas_getimage(atlasmap, "ddd_objects_block.qoi");


    player = player_new((Point3) {
        .x = 32.0, .y = 32.0, .z = 0.0
    }, player_newhbox(), &whiteball);

    tileset = tilearr_new(10);
    if (!tileset) return 7;

    tile_set(&tileset->tiles[0], 0, (int) ttype = WALL, 1, 0, &northwall, &pitfloor);
    tile_set(&tileset->tiles[1], 1, (int) ttype, 1, 0, &southwall, &pitfloor);
    tile_set(&tileset->tiles[2], 2, (int) ttype, 1, 0, &eastwall, &pitfloor);
    tile_set(&tileset->tiles[3], 3, (int) ttype, 1, 0, &westwall, &pitfloor);
    tile_set(&tileset->tiles[4], 4, (int) ttype, 1, 0, &nwwallcorner, &pitfloor);
    tile_set(&tileset->tiles[5], 5, (int) ttype, 1, 0, &swwallcorner, &pitfloor);
    tile_set(&tileset->tiles[6], 6, (int) ttype, 1, 0, &newallcorner, &pitfloor);
    tile_set(&tileset->tiles[7], 7, (int) ttype, 1, 0, &sewallcorner, &pitfloor);
    tile_set(&tileset->tiles[8], 8, (int) ttype = EMPTY, 0, 0, &blank, &greenfloor);
    tile_set(&tileset->tiles[9], 9, (int) ttype = BLOCK_STATIC, 1, 0, &block, &greenfloor);

    room = room_new(0, 0);
    if (!room) return 8;

    int x = 0;
    int y = 0;

    for (; x < ROOM_SIZE_X; x++) {
        for (; y < ROOM_SIZE_Y; y++) {
            room->tiles[x][y] = &tileset->tiles[8];
        }
    }

    x = y = 0;

    for (; x < ROOM_SIZE_X; x++) {
        room->tiles[x][0] = &tileset->tiles[0];
    }

    x = y = 0;

    for (; x < ROOM_SIZE_X; x++) {
        room->tiles[x][ROOM_SIZE_Y - 1] = &tileset->tiles[1];
    }

    x = y = 0;

    for (; y < ROOM_SIZE_Y; y++) {
        room->tiles[0][y] = &tileset->tiles[2];
    }

    x = y = 0;

    for (; y < ROOM_SIZE_Y; y++) {
        room->tiles[ROOM_SIZE_X - 1][y] = &tileset->tiles[3];
    }

    room->tiles[0][0] = &tileset->tiles[4];
    room->tiles[ROOM_SIZE_X - 1][0] = &tileset->tiles[6];
    room->tiles[0][ROOM_SIZE_Y - 1] = &tileset->tiles[5];
    room->tiles[ROOM_SIZE_X - 1][ROOM_SIZE_Y - 1] = &tileset->tiles[7];

    room->tiles[4][6] = &tileset->tiles[9];

    while (run) {
        SDL_RenderClear(ooc->rdr);

        room_draw(room, ooc);

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
            player_capvelocity(player);

            errprintf("%f, %f, %f, %f\n", currenttime, player->ent.currstate.position.x, player->ent.currstate.position.y, player->ent.currstate.position.z);
            accumulator -= dt;
        }

        interp = accumulator / dt;

        // foreach (Entity ent) {
        //     tmpstate = phys_interpolate(&player->ent, interp);
        //     c = SDL_WorldPosToScreenPos(tmpstate.position);
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

    hashmap_free(atlasmap);
    SDL_DestroyTexture(atlas);

    app_stop(ooc, SDL_INIT_EVERYTHING);
    app_free(ooc);

    return 0;
}