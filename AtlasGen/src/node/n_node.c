#include <stdlib.h>
#include <string.h>

#include "n_node.h"
#include "oocdll.h"

#include "SDL.h"
#include "SDL_image.h"

AtlasNode_t *node_find(AtlasNode_t *head, u32 w, u32 h, u32 pad) {
    if (head->used) {
        AtlasNode_t *n = NULLADDR;

        if ((n = node_find(&head->next[0], w, h, pad)) != NULLADDR || (n = node_find(&head->next[1], w, h, pad)) != NULLADDR) {
            return n;
        }
    }
    else if (w <= head->w && h <= head->h) {
        node_split(head, w, h, pad);
        return head;
    }
    else {
        return NULLADDR;
    }
}

void node_split(AtlasNode_t *node, u32 w, u32 h, u32 pad) {
    node->used = 1;

    node->next = (AtlasNode_t *) malloc(sizeof(AtlasNode_t) * 2);
    memset(node->next, 0, sizeof(AtlasNode_t) * 2); // yeah this isnt safe but ill fix it if errors happen

    node->next[0].x = node->x + w + pad;
    node->next[0].y = node->y;
    node->next[0].w = node->w - w - pad;
    node->next[0].h = h;

    node->next[1].x = node->x;
    node->next[1].y = node->y + h + pad;
    node->next[1].w = node->w;
    node->next[1].h = node->h - h - pad;
}