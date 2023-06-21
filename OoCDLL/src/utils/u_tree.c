#include <stdio.h>
#include <stdlib.h>

#include "defs/d_common.h"
#include "defs/d_constants.h"
#include "u_tree.h"

TreeNode_t *tree_new(u32 key, void *data) {
    TreeNode_t *root = NULLADDR;
    return tree_add(key, data, &root);
}

TreeNode_t *tree_add(u32 key, void *data, TreeNode_t **leaf) {
    if (*leaf == NULLADDR) {
        *leaf = (TreeNode_t *) malloc(sizeof(TreeNode_t));
        if (*leaf) {
            (*leaf)->key = key;
            (*leaf)->data = data;
            (*leaf)->left = NULLADDR;
            (*leaf)->right = NULLADDR;
        }
        else {
            printf("cant add new leaf to tree, no malloc space\n");
            return NULLADDR;
        }
    }
    else if (key < (*leaf)->key) {
        tree_add(key, data, &(*leaf)->left);
    }
    else if (key > (*leaf)->key) {
        tree_add(key, data, &(*leaf)->right);
    }
}

TreeNode_t *tree_find(u32 key, TreeNode_t *leaf) {
    if (leaf) {
        if (key == leaf->key) {
            return leaf;
        }
        else if (key < leaf->key) {
            return tree_find(key, leaf->left);
        }
        else {
            return tree_find(key, leaf->right);
        }
    }
    else {
        return NULLADDR;
    }
}

Error_t tree_freetree(TreeNode_t *leaf) {
    if (leaf) {
        tree_freetree(leaf->left);
        tree_freetree(leaf->right);
        free(leaf->data);
        free(leaf);
    }
}