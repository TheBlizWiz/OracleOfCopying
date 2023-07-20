#ifndef R_IMAGE_H
#define R_IMAGE_H

#include "defs/d_constants.h"
#include "defs/d_common.h"

#include "libs/hashmap/hashmap.h"

#include "SDL.h"
#include "SDL_image.h"

// r_image.h needs to be redone, but since that would be like the 3rd redo, ill do it later

DLLINCLUDE typedef struct Image Image_t;

struct Image {
    char fname[MAX_FNAME_LENGTH];
    u8 isrotated;
    SDL_Texture *tex;
    SDL_Rect rect;
};

DLLINCLUDE Error_t atlas_load(Hashmap_t *atlasmap, char *jsonfpath);

#endif