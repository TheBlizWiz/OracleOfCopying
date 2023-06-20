#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "a_node.h"
#include "oocdll.h"

#include "SDL.h"
#include "SDL_image.h"

AtlasNode_t *node_new(u32 x, u32 y, u32 w, u32 h) {
    AtlasNode_t *node = (AtlasNode_t *) malloc(sizeof(AtlasNode_t));
    if (node) {
        node->x = x;
        node->y = y;
        node->w = w;
        node->h = h;
        node->used = 0;

        node->nextleft = NULLADDR;
        node->nextright = NULLADDR;
        return node;
    }
    else {
        return NULLADDR;
    }

}

AtlasNode_t *node_find(AtlasNode_t *head, u32 w, u32 h, u32 pad) {
    if (head->used) {
        AtlasNode_t *n = NULLADDR;

        if ((n = node_find(&head->nextleft, w, h, pad)) != NULLADDR || (n = node_find(&head->nextright, w, h, pad)) != NULLADDR) {
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

        AtlasNode_t *tmp1 = node_new(0, 0, 0, 0);
        AtlasNode_t *tmp2 = node_new(0, 0, 0, 0);
        if (tmp1) {
            if (tmp2) {
                node->nextleft = tmp1;
                node->nextright = tmp2;

                node->nextleft->x = node->x + w + pad;
                node->nextleft->y = node->y;
                node->nextleft->w = node->w - w - pad;
                node->nextleft->h = h;

                node->nextright->x = node->x;
                node->nextright->y = node->y + h + pad;
                node->nextright->w = node->w;
                node->nextright->h = node->h - h - pad;
                return ERROR_NOERROR;
            }
            else {
                printf("no malloc space to split *node...\n");
                free(tmp1);
                return ERROR_MALLOC_NOSPACE;
            }
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