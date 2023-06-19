#ifndef C_CMDARGS_H
#define C_CMDARGS_H

#include "oocdll.h"

typedef struct {
    u32 aimgsize;
    u32 padding;
    String_t dirpath;
} Cmdargs_t;

Cmdargs_t cmdargs_get(int, char *[]);

#endif