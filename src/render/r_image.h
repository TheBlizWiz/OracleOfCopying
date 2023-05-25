#ifndef R_IMAGE_H
#define R_IMAGE_H

#include <stdint.h>
#include <stdlib.h>

#include <defs/d_string.h>
#include <defs/d_common.h>

#ifndef QOI_IMPLEMENTATION
#define QOI_IMPLEMENTATION
#include "..\qoi\qoi.h"
#endif

typedef u32 Color_t;

typedef struct {
    u32 wdt;
    u32 hgt;
    u8  coldepth;
    u8  colspace;
    Size_t pxarrlen;
    Color_t pxarr[];
} Image_t;

Image_t *img_open(String_t);

Image_t *img_copy(Image_t *);

Image_t img_resize(Image_t, u8, u8);

Image_t img_rotate(Image_t, double);

#endif