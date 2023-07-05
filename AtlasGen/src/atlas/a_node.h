#ifndef A_NODE_H
#define A_NODE_H

#include "oocdll.h"

typedef struct AtlasNode AtlasNode_t;

struct AtlasNode {
    u32 x;
    u32 y;
    u32 w;
    u32 h;
    u8 used;

    struct AtlasNode *left;
    struct AtlasNode *right;
};

AtlasNode_t *atlasnode_new(u32 x, u32 y, u32 w, u32 h);
AtlasNode_t *atlasnode_find(AtlasNode_t **head, u32 w, u32 h, u32 pad);
Error_t atlasnode_split(AtlasNode_t **node, u32 w, u32 h, u32 pad);
void atlasnode_freedeep(AtlasNode_t **head);

#endif