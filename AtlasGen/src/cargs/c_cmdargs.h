#ifndef C_CMDARGS_H
#define C_CMDARGS_H

#include "oocdll.h"

typedef struct {
    u32 aimgsize;
    u32 padding;
    String_t dirpath;
    String_t outputpath;
} Cmdargs_t;

Cmdargs_t cmdargs_get(int argc, char *argv[]);
void cmdargs_free(Cmdargs_t cargs);

#endif