#ifndef A_ATLAS_H
#define A_ATLAS_H

#include "oocdll.h"
#include "img/i_surface.h"
#include "a_node.h"

typedef struct {
    SDL_Surface *surf;
    u32 w;
    u32 h;
    String_t fpath;
} Atlas_t;

Atlas_t *atlas_new(u32 w, u32 h, String_t dirpath, const char *fname);
void atlas_add(Atlas_t *atlas, AtlasNode_t *head, SurfaceImage_t *img, u32 pad);

#endif