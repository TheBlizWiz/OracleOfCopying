#ifndef E_KEYBOARD_H
#define E_KEYBOARD_H

#include "e_app.h"

#include "SDL.h"

Error_t kboard_keyup(App_t *app, SDL_KeyboardEvent *evt);
Error_t kboard_keydown(App_t *app, SDL_KeyboardEvent *evt);

#endif