#ifndef R_APP_H
#define R_APP_H

#include <SDL2\SDL.h>
#include <d_common.h>

/**
  * Struct that holds SDL_Window and SDL_Renderer.
  * This is the struct that holds the game program window.
  * 
  * \param SDL_Window   *wdw  - pointer to a SDL_Window, usually as a local stack address (&wdw)
  * \param SDL_Renderer *rdr  - pointer to a SDL_Renderer, usually as a local stack address (&rdr)
  */
typedef struct {
    SDL_Window   *wdw;
    SDL_Renderer *rdr;
} App_t;

/** 
  * Start Oracle of Copying.
  * Remember to memset(&ooc, 0, sizeof(App_t)) before passing.
  * 
  * \param  App_t   ooc       - App_t for OoC
  * \param  int     initflags - Flags for SDL_Init(), usually SDL_INIT_EVERYTHING
  * \param  int     wdwflags  - Flags for SDL_CreateWindow(), usually SDL_WINDOW_ALLOW_HIGHDPI
  * \param  int     rdrflags  - Flags for SDL_CreateRenderer(), usually SDL_RENDERER_ACCELERATED
  * \return Error_t           - Error code, check d_constants.h
  */
Error_t app_start(App_t, int, int, int);

/**
 * Stop Oracle of Copying.
 * This safely stops all processes running before closing app.
 * 
 * \param  App_t ooc       - App_t for OoC
 * \param  int   initflags - Flags for SDL_Init(), use the same ones as in app_start()
 * \return Error_t         - Error code, currently broken, only returns ERROR_NOERROR
 */
Error_t app_stop(App_t, int);

Error_t app_doevents(SDL_Event);



#endif