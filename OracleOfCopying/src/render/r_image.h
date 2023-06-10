#ifndef R_IMAGE_H
#define R_IMAGE_H

#include <stdint.h>
#include <stdlib.h>

#include "SDL.h"
#include "SDL_image.h"

#include "engine/e_app.h"
#include "defs/d_string.h"
#include "defs/d_common.h"


// now that im using SDL all of this is probably irrelevant
// esp since SDL surprisingly supports qoi files
// but im keeping it commented if i need it later...

typedef struct {
    SDL_Texture *tex;
    SDL_Rect rect;
} Image_t;

Error_t *img_new(Image_t *, App_t, const char *, u32, u32, u32, u32);
Error_t *img_newdefault(Image_t *, App_t, const char *);

Error_t img_render(Image_t *, App_t, u32, u32);
//Error_t img_renderadv(Image_t *, App_t, u32, u32);


#endif