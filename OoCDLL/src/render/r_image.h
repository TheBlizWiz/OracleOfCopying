#ifndef R_IMAGE_H
#define R_IMAGE_H

#ifdef OOCDLL_EXPORTS
#define R_IMAGE_API __declspec(dllexport)
#else
#define R_IMAGE_API __declspec(dllimport)
#endif


#include <stdint.h>
#include <stdlib.h>

#include "SDL.h"
#include "SDL_image.h"
#include "engine/e_app.h"
#include "defs/d_string.h"
#include "defs/d_common.h"

R_IMAGE_API typedef struct {
    u8 wdt, hgt;
    const char *fpath;
    Size_t fpathlen;
    SDL_Surface *tex;
    SDL_Rect *rect;
} Image_t;



/*
R_IMAGE_API typedef struct {
    const char *fpath;
    Size_t fpathlen;
    SDL_Texture *tex;
    SDL_Rect rect;
} Image_t;
*/

/*

R_IMAGE_API Error_t img_new(Image_t *, App_t, const char *, u32, u32, u32, u32);
R_IMAGE_API Error_t img_newdefault(Image_t *, App_t, const char *);



Error_t img_render(Image_t *, App_t, u32, u32);
//Error_t img_renderadv(Image_t *, App_t, u32, u32);
*/

#endif