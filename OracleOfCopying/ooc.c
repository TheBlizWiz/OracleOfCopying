#include "ooc.h"

#include <string.h>
#include <stdlib.h>
#include <time.h>

Error_t _app_start(App_t *ooc, int initflags, int wdwflags, int rdrflags) {

    if (SDL_Init(initflags) < 0) {
        printf("SDL failed to initialize: %s\n", SDL_GetError());
        return (Error_t) ERROR_SDL_INIT_FAILURE;
    }

    ooc->wdw = SDL_CreateWindow(GAME_WINDOW_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_SIZE_X, SCREEN_SIZE_Y, wdwflags);

    if (ooc->wdw == NULLADDR) {
        printf("Failed to init ooc.wdw: %s\n", SDL_GetError());
        return (Error_t) ERROR_SDL_CREATEWINDOW_FAILURE;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    ooc->rdr = SDL_CreateRenderer(ooc->wdw, -1, rdrflags);

    if (ooc->rdr == NULLADDR) {
        printf("Failed to init ooc.rdr: %s\n", SDL_GetError());
        return (Error_t) ERROR_SDL_CREATERENDERER_FAILURE;
    }

    return (Error_t) ERROR_NOERROR;
}

Error_t _app_stop(App_t *ooc, int initflags) {
    SDL_DestroyRenderer(ooc->rdr);
    SDL_DestroyWindow(ooc->wdw);
    SDL_QuitSubSystem(initflags);
    SDL_Quit();
    return (Error_t) ERROR_NOERROR;
}

Error_t _app_doevents(SDL_Event *evt) {
    SDL_PollEvent(evt);

    switch (evt->type) {
        case SDL_QUIT:
            return ERROR_DOEVENTS_TIMETOQUIT;
        default:
            return ERROR_NOERROR;
    }

    return ERROR_DOEVENTS_SWITCHCASEDIDNTRETURN;
}




int main(int argc, char *argv[]) {
    App_t ooc;
    SDL_Event evt;

    Hashmap_t *atlasmap;
    SDL_Texture *atlas;


    Error_t e = ERROR_NOERROR;
    u8 run = 1;

    // PRE-LOAD

    zeroset(&ooc, sizeof(App_t));
    zeroset(&evt, sizeof(SDL_Event));

    e = _app_start(&ooc, SDL_INIT_EVERYTHING, SDL_WINDOW_ALLOW_HIGHDPI, SDL_RENDERER_ACCELERATED);
    if (e != ERROR_NOERROR) {
        errprintf("ERROR: something wrong with app_start\n");
        return 1;
    }

    // LOAD

    // backup missing texture, if we look up an image on the atlas and it isnt there, render this instead
    u8 *px = CreateMissingTextureArray(32, 32);

    nulltex = img_newfromsurface(ooc, "nulltex", SDL_CreateMissingTexture(ooc, 32, 32, px), 0);
    if (!nulltex) {
        errprintf("ERROR: no malloc space for backup missing texture... what is this, a potato?\n");
        return 2;
    }

    atlas = IMG_LoadTexture(ooc.rdr, "E:\\MSVC\\source\\repos\\OracleOfCopying\\OracleOfCopying\\textures\\atlases\\dancingdragondungeon\\atlasimg.qoi");
    if (!atlas) {
        errprintf("ERROR: atlas is null... uhhh\n");
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



    Image_t *floor = atlas_getimage(atlasmap, "E:\\MSVC\\source\\repos\\OracleOfCopying\\oracle_of_seasons_texture_rips\\floors\\oos_ddd_floor_patterned_purple.qoi");
    
    Image_t *wall_corner_se = atlas_getimage(atlasmap, "E:\\MSVC\\source\\repos\\OracleOfCopying\\oracle_of_seasons_texture_rips\\walls\\oos_ddd_walls_innercorner_sw.qoi");

    Image_t *eyestatue = atlas_getimage(atlasmap, "E:\\MSVC\\source\\repos\\OracleOfCopying\\oracle_of_seasons_texture_rips\\animated\\objects\\oos_ddd_objects_eyestatue_center.qoi");

    Image_t *water_f2 = atlas_getimage(atlasmap, "E:\\MSVC\\source\\repos\\OracleOfCopying\\oracle_of_seasons_texture_rips\\animated\\floors\\floors_water_f2.qoi");

    //Image_t *not_a_texture = atlas_getimage(atlasmap, "asdf");

    run = 1;
    while (run) {
        e = _app_doevents(&evt);

        if (e == ERROR_DOEVENTS_TIMETOQUIT) {
            run = 0;
            break;
        }

        SDL_RenderClear(ooc.rdr);

        SDL_BlitImage(ooc, floor, rng_gnext(), rng_gnext(), 1);
        SDL_BlitImage(ooc, wall_corner_se, rng_gnext(), rng_gnext(), 1);
        SDL_BlitImage(ooc, eyestatue, rng_gnext(), rng_gnext(), 1);
        SDL_BlitImage(ooc, water_f2, rng_gnext(), rng_gnext(), 1);
        //SDL_BlitImage(ooc, not_a_texture, rand() % SCREEN_SIZE_X, rand() % SCREEN_SIZE_Y, 1);

        SDL_RenderPresent(ooc.rdr);
        SDL_Delay(300);
    }


    hashmap_free(atlasmap);
    SDL_DestroyTexture(atlas);

    _app_stop(&ooc, SDL_INIT_EVERYTHING);

    return 0;
}