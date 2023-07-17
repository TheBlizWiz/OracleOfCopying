#ifndef G_MAP_H
#define G_MAP_H

#include "SDL.h"
#include "g_room.h"
#include "defs/d_common.h"

DLLINCLUDE typedef struct Map Map_t;

struct Map {
    u64 tags;
    Room_t rooms[MAP_SIZE_X][MAP_SIZE_Y];
};

#endif