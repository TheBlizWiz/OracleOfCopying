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

    SDL_Texture *tex_chest_closed = NULLADDR;
    SDL_Texture *tex_chest_open = NULLADDR;
    SDL_Texture *tex_gemstone = NULLADDR;

    tex_chest_closed = IMG_LoadTexture(ooc.rdr, "./textures/oracle_chest_closed.qoi");
    if (!tex_chest_closed) { 
        printf("failed to load the closed chest: %s\n", SDL_GetError()); 
    }

    tex_chest_open = IMG_LoadTexture(ooc.rdr, "./textures/oracle_chest_open.qoi");
    if (!tex_chest_open) { 
        printf("failed to load the open chest: %s\n", SDL_GetError()); 
    }

    tex_gemstone = IMG_LoadTexture(ooc.rdr, "./textures/oracle_gem_diamond.qoi");
    if (!tex_gemstone) { 
        printf("failed to load the diamond: %s\n", SDL_GetError()); 
    }

    SDL_Rect tex_chest_closed_rect, tex_chest_open_rect, tex_gemstone_rect;
    memset(&tex_chest_closed_rect, 0, sizeof(SDL_Rect));
    memset(&tex_chest_open_rect, 0, sizeof(SDL_Rect));
    memset(&tex_gemstone_rect, 0, sizeof(SDL_Rect));


    tex_chest_closed_rect.x = 64;
    tex_chest_closed_rect.y = 64;
    tex_chest_closed_rect.w = 32;
    tex_chest_closed_rect.h = 32;

    tex_chest_open_rect.x = 64;
    tex_chest_open_rect.y = 64;
    tex_chest_open_rect.w = 32;
    tex_chest_open_rect.h = 32;

    tex_gemstone_rect.x = 64;
    tex_gemstone_rect.y = 32;
    tex_gemstone_rect.w = 32;
    tex_gemstone_rect.h = 32;

    while (run) {
        Error_t e = app_doevents(&evt);

        if (e == ERROR_DOEVENTS_TIMETOQUIT) {
            run = 0;
            break;
        }
        SDL_RenderClear(ooc.rdr);
        SDL_RenderCopy(ooc.rdr, tex_chest_closed, NULLADDR, &tex_chest_closed_rect);
        SDL_RenderPresent(ooc.rdr);
        SDL_Delay(1000);
        SDL_RenderClear(ooc.rdr);
        SDL_RenderCopy(ooc.rdr, tex_chest_open, NULLADDR, &tex_chest_open_rect);
        SDL_RenderPresent(ooc.rdr);
        SDL_Delay(1000);
        SDL_RenderClear(ooc.rdr);
        SDL_RenderCopy(ooc.rdr, tex_chest_open, NULLADDR, &tex_chest_open_rect);
        SDL_RenderCopy(ooc.rdr, tex_gemstone, NULLADDR, &tex_gemstone_rect);
        SDL_RenderPresent(ooc.rdr);
        SDL_Delay(1000);
    }

    SDL_DestroyTexture(tex_chest_closed);
    SDL_DestroyTexture(tex_chest_open);
    SDL_DestroyTexture(tex_gemstone);

    app_stop(&ooc, SDL_INIT_EVERYTHING);

    return 0;
}