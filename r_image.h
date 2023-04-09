#ifndef R_IMAGE_H
#define R_IMAGE_H

#include <stdint.h>
#include <stdlib.h>

#include "d_string.h"
#include "d_common.h"

    // this is very wip, its honestly more of a placeholder for trying to block out
    // how tiles are going to work...

    typedef uint32_t* Image_t;

    typedef struct {
        String_t *fpath;
        u8 xdim, ydim;
        size_t length;
        size_t alloc;
    } ImageData_t;

#endif