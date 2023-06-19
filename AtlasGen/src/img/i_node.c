#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "i_node.h"
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

Error_t node_split(AtlasNode_t *node, u32 w, u32 h, u32 pad) {
    if (node) {
        node->used = 1;

        node->next = (AtlasNode_t *) malloc(sizeof(AtlasNode_t) * 2);
        if (node->next) {
            memset(node->next, 0, sizeof(AtlasNode_t) * 2);

            node->next[0].x = node->x + w + pad;
            node->next[0].y = node->y;
            node->next[0].w = node->w - w - pad;
            node->next[0].h = h;

            node->next[1].x = node->x;
            node->next[1].y = node->y + h + pad;
            node->next[1].w = node->w;
            node->next[1].h = node->h - h - pad;
            return ERROR_NOERROR;
        }
        else {
            printf("no malloc space to split *node...\n");
            return ERROR_MALLOC_NOSPACE;
        }
    }
    else {
        printf("node_split: *node is null, can't do anything...\n");
        return ERROR_ISNULLADDR;
    }
}