#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "a_node.h"
#include "oocdll.h"

#include "SDL.h"
#include "SDL_image.h"

AtlasNode_t *atlasnode_new(u32 x, u32 y, u32 w, u32 h) {
    AtlasNode_t *node = (AtlasNode_t *) malloc(sizeof(AtlasNode_t));
    if (node) {
        node->x = x;
        node->y = y;
        node->w = w;
        node->h = h;
        node->used = 0;

        node->left = NULLADDR;
        node->right = NULLADDR;
        return node;
    }
    else {
        return NULLADDR;
    }

}

AtlasNode_t *atlasnode_find(AtlasNode_t *head, u32 w, u32 h, u32 pad) {
    if (head->used) {
        AtlasNode_t *n = NULLADDR;

        if ((n = atlasnode_find(head->left, w, h, pad)) != NULLADDR || (n = atlasnode_find(head->right, w, h, pad)) != NULLADDR) {
            return n;
        }
        else {
            return NULLADDR;
        }
    }
    else if (w <= head->w && h <= head->h) {
        atlasnode_split(head, w, h, pad);
        return head;
    }
    else {
        return NULLADDR;
    }
}

Error_t atlasnode_split(AtlasNode_t *node, u32 w, u32 h, u32 pad) {
    if (node) {
        node->used = 1;

        AtlasNode_t *tmp1 = atlasnode_new(0, 0, 0, 0);
        AtlasNode_t *tmp2 = atlasnode_new(0, 0, 0, 0);
        if (tmp1) {
            if (tmp2) {
                node->left = tmp1;
                node->right = tmp2;

                node->left->x = node->x + w + pad;
                node->left->y = node->y;
                node->left->w = node->w - w - pad;
                node->left->h = h;

                node->right->x = node->x;
                node->right->y = node->y + h + pad;
                node->right->w = node->w;
                node->right->h = node->h - h - pad;
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

void atlasnode_freedeep(AtlasNode_t *head) {
    if (head && head->used) {
        atlasnode_freedeep(head->left);
        atlasnode_freedeep(head->right);
        free(head);
    }
}