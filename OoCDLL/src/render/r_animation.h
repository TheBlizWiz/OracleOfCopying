#ifndef R_ANIMATION_H
#define R_ANIMATION_H

#include "defs/d_common.h"
#include "r_image.h"


DLLINCLUDE typedef struct Animation Animation_t;

struct Animation {
    u8 numframes;
    u16 framerate;
    Image_t *frames[];
};

DLLINCLUDE Animation_t *anim_new(u8 numf, u16 frate);
DLLINCLUDE Error_t anim_free(Animation_t *a);

#endif