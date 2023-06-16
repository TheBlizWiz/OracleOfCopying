#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "SDL.h"
#include "SDL_image.h"

#include "oocdll.h"

int main(int argc, char *argv[]) {

    App_t ooc;
    memset(&ooc, 0, sizeof(App_t)); // malloc on stack

    app_start(&ooc, SDL_INIT_EVERYTHING, SDL_WINDOW_ALLOW_HIGHDPI, SDL_RENDERER_ACCELERATED);

    SDL_Event evt;
    int run = 1;
    
    /*

    struct hashmap *hmap = hashmap_new(sizeof(Image_t), 64, 0, 0, hash_imghash, hash_imgcmp, NULL, NULL);
    

    for (int i = 0; i < NUM_IMAGES_TO_LOAD; i++) {
        hashmap_set(hmap, &(Image_t) {
            .fpath = file_readline(
    }

    */

    while (run) {
        Error_t e = app_doevents(&evt);

        if (e == ERROR_DOEVENTS_TIMETOQUIT) {
            run = 0;
            break;
        }


        SDL_Delay(15);
    }

    app_stop(&ooc, SDL_INIT_EVERYTHING);

    return 0;
}