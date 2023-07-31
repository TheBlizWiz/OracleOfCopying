#ifndef D_MACROS_H
#define D_MACROS_H

#include <stdio.h>
#include <string.h>

#include "defs/d_common.h"

// ------------------------
// |   FUNCTION MACROS    |
// ------------------------

#ifdef _DEBUG
#define errprintf printf
#endif

#ifdef NDEBUG
#define errprintf //
#endif

#define zeroset(ptr, sz) memset(ptr, 0, sz)
#define strncopy(dst, src, szdst) do { strncpy_s(dst, sizeof(dst[0]) * szdst, src, sizeof(dst[0]) * (szdst - 1)); dst[szdst - 1] = '\0'; } while(0)

// -----------------------------
// |  STRUCT PARAMETER MACROS  |
// -----------------------------

#define PLAYER_HITBOX_DIMENSIONS  \
(Point3){.x =  0.0, .y =  0.0, .z =  0.0}, \
(Point3){.x = 32.0, .y =  0.0, .z =  0.0}, \
(Point3){.x =  0.0, .y = 32.0, .z =  0.0}, \
(Point3){.x = 32.0, .y = 32.0, .z =  0.0}, \
(Point3){.x =  0.0, .y =  0.0, .z = 32.0}, \
(Point3){.x = 32.0, .y =  0.0, .z = 32.0}, \
(Point3){.x =  0.0, .y = 32.0, .z = 32.0}, \
(Point3){.x = 32.0, .y = 32.0, .z = 32.0}

#endif