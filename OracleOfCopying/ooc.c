#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "SDL.h"
#include "SDL_image.h"

#include "oocdll.h"

struct rgba {
    u8 r, g, b, a;
};

struct rgba randcolor(u8 usealp) {
    u8 r, g, b, a;
    if (usealp) {
        r = rand() % 255;
        g = rand() % 255;
        b = rand() % 255;
        a = rand() % 255;
    }
    else {
        r = rand() % 255;
        g = rand() % 255;
        b = rand() % 255;
        a = 255;
    }
    struct rgba col = { .r = r, .g = g, .b = b, .a = a };
    return col;
}

int main(int argc, char *argv[]) {

    srand(time(NULL));

    App_t ooc;
    memset(&ooc, 0, sizeof(App_t));

    Error_t e1 = app_start(&ooc, SDL_INIT_EVERYTHING, SDL_WINDOW_ALLOW_HIGHDPI, SDL_RENDERER_ACCELERATED);
    if (e1 != ERROR_NOERROR) {
        printf("ERROR: something wrong with app_start\n");
        return 1;
    }

    SDL_Surface *tmp = IMG_Load("E:\\MSVC\\source\\repos\\OracleOfCopying\\OracleOfCopying\\textures\\atlases\\dancingdragondungeon\\atlasimg.png");

    SDL_Texture *atlas = SDL_CreateTextureFromSurface(ooc.rdr, tmp);
    if (!atlas) {
        printf("%s\n", SDL_GetError());
    }

    SDL_Event evt;
    int run = 1;
    struct rgba col;

    while (run) {
        Error_t e = app_doevents(&evt);

        if (e == ERROR_DOEVENTS_TIMETOQUIT) {
            run = 0;
            break;
        }

        SDL_RenderClear(ooc.rdr);

        col = randcolor(0);
        SDL_SetRenderDrawColor(ooc.rdr, col.r, col.g, col.b, col.a);
        SDL_RenderDrawRect(ooc.rdr, NULL);
        SDL_RenderCopy(ooc.rdr, atlas, NULL, &(SDL_Rect){.w = 256, .h = 256, .x = 0, .y = 0});

        SDL_RenderPresent(ooc.rdr);
        SDL_Delay(15);
    }

    SDL_DestroyTexture(atlas);
    SDL_FreeSurface(tmp);
    app_stop(&ooc, SDL_INIT_EVERYTHING);

    return 0;
}