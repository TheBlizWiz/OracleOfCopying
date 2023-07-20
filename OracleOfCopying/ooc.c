#include "ooc.h"

#include <string.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {

    App_t ooc;
    SDL_Event evt;

    Hashmap_t *atlasmap;
    SDL_Texture *atlas;

    Error_t e = ERROR_NOERROR;
    u8 run = 1;

    // PRE-LOAD

    srand(time(NULL));

    zeroset(&ooc, sizeof(App_t));
    zeroset(&evt, sizeof(SDL_Event));
    zeroset(&atlas, sizeof(Image_t));

    e = app_start(&ooc, SDL_INIT_EVERYTHING, SDL_WINDOW_ALLOW_HIGHDPI, SDL_RENDERER_ACCELERATED);
    if (e != ERROR_NOERROR) {
        errprintf("ERROR: something wrong with app_start\n");
        return 1;
    }

    // LOAD

    atlas = IMG_LoadTexture(ooc.rdr, "E:\\MSVC\\source\\repos\\OracleOfCopying\\OracleOfCopying\\textures\\atlases\dancingdragondungeon\\atlasimg.qoi");

    // TODO: DO I need hash_imgfree?

   // atlas = hashmap_new(sizeof(Image_t), 0, 0, 0, hash_imghash, hash_imgcmp, hash_imgfree, NULL); 
    atlasmap = hashmap_new(sizeof(Image_t), 0, 0, 0, hash_imghash, hash_imgcmp, NULL, NULL);








    while (run) {
        e = app_doevents(&evt);

        if (e == ERROR_DOEVENTS_TIMETOQUIT) {
            run = 0;
            break;
        }

        SDL_RenderClear(ooc.rdr);

        SDL_RenderPresent(ooc.rdr);
        SDL_Delay(15);
    }


    hashmap_free(atlasmap);
    SDL_DestroyTexture(atlas);

    app_stop(&ooc, SDL_INIT_EVERYTHING);

    return 0;
}