#include "ooc.h"

#include <string.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {

    App_t *ooc;
    Time_t t;
    boolean run = 1;
    SDL_Event evt;
    SDL_Texture *atlas;
    Hashmap_t *atlasmap;
    Error_t e;
    Player_t *player;

    double accumulator = 0.0;

    ooc = app_new();
    e = app_start(ooc, SDL_INIT_EVERYTHING, SDL_WINDOW_ALLOW_HIGHDPI, SDL_RENDERER_ACCELERATED, SCREEN_SIZE_X, SCREEN_SIZE_Y);

    t = time_start();

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

    player = player_new((Point3) {.x = 256.0, .y = 256.0, .z = 0.0}, hbox_new(PLAYER_HITBOX_DIMENSIONS), &whiteball);

    while (run) {
        app_doevents(ooc, &evt);

        time_calc(t);


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