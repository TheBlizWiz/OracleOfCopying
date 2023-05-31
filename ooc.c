#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include <SDL2\SDL.h>

#include <e_app.h>
#include <d_common.h>
#include <d_constants.h>

int rng(int lo, int hi) {
    return (rand() % (hi - lo)) + lo;
}

int main(int argc, char *argv[]) {

    srand(time(0));

    App_t ooc;
    memset(&ooc, 0, sizeof(App_t)); // malloc on stack

    //app_start(ooc, SDL_INIT_EVERYTHING, SDL_WINDOW_ALLOW_HIGHDPI, SDL_RENDERER_ACCELERATED);

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("SDL failed to initialize: %s", SDL_GetError());
        return (int) ERROR_SDL_INIT_FAILURE;
    }

    ooc.wdw = SDL_CreateWindow(GAME_WINDOW_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_SIZE_X, SCREEN_SIZE_Y, SDL_WINDOW_ALLOW_HIGHDPI);

    if (ooc.wdw == NULL) {
        printf("Failed to init ooc.wdw: %s\n", SDL_GetError());
        return (int) ERROR_SDL_CREATEWINDOW_FAILURE;
    }

    if (SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear") == SDL_FALSE) {
        printf("Failed to set SDL Hint, %s\n", SDL_GetError());
    }

    ooc.rdr = SDL_CreateRenderer(ooc.wdw, -1, SDL_RENDERER_ACCELERATED);

    if (ooc.rdr == NULL) {
        printf("Failed to init ooc.rdr: %s\n", SDL_GetError());
        return (int) ERROR_SDL_CREATERENDERER_FAILURE;
    }

    SDL_Event evt;
    int run = 1;
    int i = 0;
    int r = 0;
    int g = 0;
    int b = 0;
    int x = 0;
    int y = 0;

    while (run) {
       Error_t e = app_doevents(evt);

       if (e == ERROR_DOEVENTS_TIMETOQUIT) {
           run = 0;
           break;
       }

       i = rng(1, 10000);

       if (i == 1) {
           if (SDL_SetRenderDrawColor(ooc.rdr, 0, 0, 0, 0) < 0) {
               printf("failed to set render draw color when i == 1: %s\n", SDL_GetError());
           }
          
           if (SDL_RenderClear(ooc.rdr) < 0) {
               printf("failed to clear render when i == 1: %s\n", SDL_GetError());
          }
       }
       else {
           r = rng(128, 255);
           g = rng(128, 255);
           b = rng(128, 255);
           x = rng(0, 800);
           y = rng(0, 600);

           if (SDL_SetRenderDrawColor(ooc.rdr, r, g, b, 255) < 0) {
               printf("failed to set render draw color when i != 1, %s\n", SDL_GetError());
           }

           if (SDL_RenderDrawPoint(ooc.rdr, x, y) < 0) {
               printf("failed to draw point to screen, %s\n", SDL_GetError());
           }
       }

       SDL_RenderPresent(ooc.rdr);

       SDL_Delay(15);
    }

    //app_stop(ooc, SDL_INIT_EVERYTHING);
    SDL_DestroyRenderer(ooc.rdr);
    SDL_DestroyWindow(ooc.wdw);
    SDL_QuitSubSystem(SDL_INIT_EVERYTHING);
    SDL_Quit();

    return 0;
}