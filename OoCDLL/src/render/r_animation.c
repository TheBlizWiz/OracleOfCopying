#include "r_animation.h"

Animation_t *anim_new(u8 numf, u16 frate) {
    Animation_t *anim = (Animation_t *) malloc(sizeof(Animation_t) + (sizeof(Image_t *) * numf));
    if (anim) {
        anim->numframes = numf;
        anim->framerate = frate;
        for (u8 i = 0; i < numf; i++) {
            anim->frames[i] = NULLADDR;
        }
        return anim;
    }
    else {
        errprintf("ERROR: no malloc space for new Animation_t\n");
        return NULLADDR;
    }

}

Error_t anim_free(Animation_t *a) {
    if (a) {
        free(a);
        return ERROR_NOERROR;
    }
    else {
        errprintf("ERROR: Animation_t is not null, can't free\n");
        return ERROR_ISNOTNULLADDR;
    }
}