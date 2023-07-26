#ifndef R_APP_H
#define R_APP_H

#include "SDL.h"
#include "defs/d_common.h"
#include "defs/d_constants.h"

/**
  * Struct that holds SDL_Window and SDL_Renderer.
  * This is the struct that holds the game program window.
  *
  * \param SDL_Window   *wdw  - pointer to a SDL_Window, usually as a local stack address (&wdw)
  * \param SDL_Renderer *rdr  - pointer to a SDL_Renderer, usually as a local stack address (&rdr)
  */
DLLINCLUDE typedef struct App App_t;


struct App {
    SDL_Window *wdw;
    SDL_Renderer *rdr;
    boolean paused;

    u8 keys[MAX_KEYS];
};

DLLINCLUDE App_t *app_new(void);

/**
  * Start Oracle of Copying / DungeonMaster.
  * Remember to memset(&ooc, 0, sizeof(App_t)) before passing.
  *
  * \param  App_t   *app      - App_t for OoC/DgM
  * \param  i32     initflags - Flags for SDL_Init(), usually SDL_INIT_EVERYTHING
  * \param  i32     wdwflags  - Flags for SDL_CreateWindow(), usually SDL_WINDOW_ALLOW_HIGHDPI
  * \param  i32     rdrflags  - Flags for SDL_CreateRenderer(), usually SDL_RENDERER_ACCELERATED
  * \param  i32     sizex     - Horizontal screen size
  * \param  i32     sizey     - Vertical screen size
  * \return Error_t           - Error code, check d_constants.h
  */
DLLINCLUDE Error_t app_start(App_t *app, i32 initflags, i32 wdwflags, i32 rdrflags, i32 sizex, i32 sizey);

/**
  * Handle events for OoC / DgM
  *
  * \param  SDL_Event *evt    - Event sent over from SDL
  * \return Error_t           - Error code, check d_constants.h
  */
DLLINCLUDE Error_t app_doevents(SDL_Event *);

/**
 * Stop Oracle of Copying / DungeonMaster.
 * This safely stops all processes running before closing app.
 *
 * \param  App_t *app      - App_t for OoC / DgM
 * \param  i32   initflags - Flags for SDL_Init(), use the same ones as in app_start()
 * \return Error_t         - Error code, currently broken, only returns ERROR_NOERROR
 */
DLLINCLUDE Error_t app_stop(App_t *app, i32 initflags);

DLLINCLUDE Error_t app_free(App_t *app);

#endif