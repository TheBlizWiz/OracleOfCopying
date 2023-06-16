#ifndef N_NODE_H
#define N_NODE_H

#include "oocdll.h"

typedef struct AtlasNode AtlasNode_t;

struct AtlasNode {
    u32 x;
    u32 y;
    u32 w;
    u32 h;
    u8 used;

    struct AtlasNode *next; // arr of len 2, but is also kind of a linked list
};

AtlasNode_t *node_find(AtlasNode_t *, u32, u32, u32);
void node_split(AtlasNode_t *, u32, u32, u32);

#endif