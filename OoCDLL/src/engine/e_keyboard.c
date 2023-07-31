#include "e_keyboard.h"
#include "defs/d_constants.h"
#include "defs/d_macros.h"

Error_t kboard_keyup(App_t *app, SDL_KeyboardEvent *kevt) {
    if (app) {
        if (kevt) {
            if (kevt->keysym.scancode < 0 || kevt->keysym.scancode > MAX_KEYS) {
                errprintf("ERROR: key pressed out of bounds of app->keys, scancode OOB\n");
                return ERROR_INDEX_OOB;
            }

            if (!kevt->repeat) {
                app->keys[kevt->keysym.scancode] = 0;
            }

            return ERROR_NOERROR;
        }
        else {
            errprintf("ERROR: SDL_KeyboardEvent is null\n");
            return ERROR_ISNULLADDR;
        }
    }
    else {
        errprintf("ERROR: App_t *app is null\n");
        return ERROR_ISNULLADDR;
    }
}

Error_t kboard_keydown(App_t *app, SDL_KeyboardEvent *kevt) {
    if (app) {
        if (kevt) {
            if (kevt->keysym.scancode < 0 || kevt->keysym.scancode > MAX_KEYS) {
                errprintf("ERROR: key pressed out of bounds of app->keys, scancode OOB\n");
                return ERROR_INDEX_OOB;
            }

            if (!kevt->repeat) {
                app->keys[kevt->keysym.scancode] = 1;
            }

            return ERROR_NOERROR;
        }
        else {
            errprintf("ERROR: SDL_KeyboardEvent is null\n");
            return ERROR_ISNULLADDR;
        }
    }
    else {
        errprintf("ERROR: App_t *app is null\n");
        return ERROR_ISNULLADDR;
    }
}