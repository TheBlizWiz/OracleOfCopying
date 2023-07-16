#ifndef G_MAP_H
#define G_MAP_H

#ifdef OOCDLL_EXPORTS
#define G_MAP_API __declspec(dllexport)
#else
#define G_MAP_API __declspec(dllimport)
#endif

#include "SDL.h"
#include "g_room.h"
#include "defs/d_common.h"

G_MAP_API typedef struct MapNode MapNode_t;

struct MapNode {
    u32 key;
    Room_t *room;
    struct MapNode *north, *south, *east, *west;
};

G_MAP_API MapNode_t *mapnode_new(u32 key, Room_t *room);
G_MAP_API MapNode_t *map_new(MapNode_t *root, u32 key, Room_t *room);

G_MAP_API MapNode_t *map_addnorth(MapNode_t *root, u32 key, Room_t *room);
G_MAP_API MapNode_t *map_addsouth(MapNode_t *root, u32 key, Room_t *room);
G_MAP_API MapNode_t *map_addeast(MapNode_t *root, u32 key, Room_t *room);
G_MAP_API MapNode_t *map_addwest(MapNode_t *root, u32 key, Room_t *room);

G_MAP_API MapNode_t *map_addnorthbykey(MapNode_t *root, u32 key, Room_t *room, const u32 tgtkey);
G_MAP_API MapNode_t *map_addsouthbykey(MapNode_t *root, u32 key, Room_t *room, const u32 tgtkey);
G_MAP_API MapNode_t *map_addeastbykey(MapNode_t *root, u32 key, Room_t *room, const u32 tgtkey);
G_MAP_API MapNode_t *map_addwestbykey(MapNode_t *root, u32 key, Room_t *room, const u32 tgtkey);

G_MAP_API MapNode_t *map_searchbykey(MapNode_t *root, const u32 tgtkey);

G_MAP_API Error_t mapnode_free(MapNode_t *leaf);
G_MAP_API Error_t map_free(MapNode_t *root);

#endif