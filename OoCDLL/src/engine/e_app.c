#include <stdio.h>
#include <stdlib.h>

#include "SDL.h"

#include "e_app.h"
#include "defs/d_common.h"
#include "defs/d_constants.h"

App_t *app_new(void) {
    App_t *app = (App_t *) malloc(sizeof(App_t));

    if (app) {
        app->paused = FALSE;
        app->rdr = NULLADDR;
        app->wdw = NULLADDR;
        zeroset(app->keys, (sizeof(u8) * MAX_KEYS));
        return app;
    }
    else {
        errprintf("ERROR: no malloc space for new App_t *app\n");
        return NULLADDR;
    }
}


Error_t app_start(App_t *app, i32 initflags, i32 wdwflags, i32 rdrflags, i32 sizex, i32 sizey) {

    if (!app) {
        errprintf("ERROR: App_t *app is null, can't start app\n");
        return (Error_t) ERROR_ISNULLADDR;
    }

    if (SDL_Init(initflags) < 0) {
        errprintf("SDL failed to initialize: %s\n", SDL_GetError());
        return (Error_t) ERROR_SDL_INIT_FAILURE;
    }

    app->wdw = SDL_CreateWindow(GAME_WINDOW_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, sizex, sizey, wdwflags);

    if (app->wdw == NULLADDR) {
        errprintf("Failed to init app.wdw: %s\n", SDL_GetError());
        return (Error_t) ERROR_SDL_CREATEWINDOW_FAILURE;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    app->rdr = SDL_CreateRenderer(app->wdw, -1, rdrflags);

    if (app->rdr == NULLADDR) {
        errprintf("Failed to init app.rdr: %s\n", SDL_GetError());
        return (Error_t) ERROR_SDL_CREATERENDERER_FAILURE;
    }

    return (Error_t) ERROR_NOERROR;
}

Error_t app_doevents(SDL_Event *evt) {
    SDL_PollEvent(evt);

    switch (evt->type) {
        case SDL_QUIT:
            return ERROR_DOEVENTS_TIMETOQUIT;
        default:
            return ERROR_DOEVENTS_DEFAULTCASE;
    }

    return ERROR_DOEVENTS_SWITCHCASEDIDNTRETURN;
}

Error_t app_stop(App_t *app, i32 initflags) {
    SDL_DestroyRenderer(app->rdr);
    SDL_DestroyWindow(app->wdw);
    SDL_QuitSubSystem(initflags);
    SDL_Quit();
    return (Error_t) ERROR_NOERROR;
}

Error_t app_free(App_t *app) {
    if (app) {
        free(app);
    }
    else {
        errprintf("ERROR: App_t *app is null, can't free\n");
        return ERROR_ISNULLADDR;
    }
}