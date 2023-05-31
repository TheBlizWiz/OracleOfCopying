#include <stdio.h>
#include <e_app.h>
#include <d_common.h>
#include <d_constants.h>
#include <SDL2\SDL.h>

Error_t app_start(App_t ooc, int initflags, int wdwflags, int rdrflags) {

    if (SDL_Init(initflags) < 0) {
        printf("SDL failed to initialize: %s\n", SDL_GetError());
        return (Error_t) ERROR_SDL_INIT_FAILURE;
    }

    ooc.wdw = SDL_CreateWindow(GAME_WINDOW_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_SIZE_X, SCREEN_SIZE_Y, wdwflags);

    if (ooc.wdw == NULLADDR) {
        printf("Failed to init ooc.wdw: %s\n", SDL_GetError());
        return (Error_t) ERROR_SDL_CREATEWINDOW_FAILURE;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    ooc.rdr = SDL_CreateRenderer(ooc.wdw, -1, rdrflags);

    if (ooc.rdr == NULLADDR) {
        printf("Failed to init ooc.rdr: %s\n", SDL_GetError());
        return (Error_t) ERROR_SDL_CREATERENDERER_FAILURE;
    }

    return (Error_t) ERROR_NOERROR;
}

Error_t app_stop(App_t ooc, int initflags) {
    SDL_DestroyRenderer(ooc.rdr);
    SDL_DestroyWindow(ooc.wdw);
    SDL_QuitSubSystem(initflags);
    SDL_Quit();
    return (Error_t) ERROR_NOERROR;
}

Error_t app_doevents(SDL_Event evt) {
    SDL_PollEvent(&evt);
    
    switch (evt.type) {
        case SDL_QUIT:
            return ERROR_DOEVENTS_TIMETOQUIT;
        default:
            return ERROR_DOEVENTS_DEFAULTCASE;
    }

    return ERROR_DOEVENTS_SWITCHCASEDIDNTRETURN;
}