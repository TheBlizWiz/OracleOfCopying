#ifndef G_ROOM_H
#define G_ROOM_H

#include "d_common.h"
#include "g_tile.h"

typedef struct {
    u8 sizex;
    u8 sizey;
    u64 tags;
    Tilearray_t *tarr;
} Room_t;



#endif