#ifndef U_TREE_H
#define U_TREE_H

#include "defs/d_common.h"

DLLINCLUDE typedef struct TreeNode TreeNode_t;
DLLINCLUDE typedef struct Tree Tree_t;

struct TreeNode {
    u32 key;
    void *data;
    free_fnptr datafree;
    cmp_fnptr datacmp;

    struct TreeNode *left;
    struct TreeNode *right;
};

struct Tree {
    struct TreeNode_t **root;
    Size_t size;
};

DLLINCLUDE TreeNode_t *tree_new(u32 key, void *data);
DLLINCLUDE TreeNode_t *tree_add(u32 key, void *data, TreeNode_t **leaf);
DLLINCLUDE TreeNode_t *tree_find(u32 key, TreeNode_t *leaf);
DLLINCLUDE Error_t tree_freetree(TreeNode_t *leaf, Error_t(*data_free)(void *));

#endif