#ifndef U_TREE_H
#define U_TREE_H

#include "defs/d_common.h"

DLLINCLUDE TreeNode_t *tree_new(u32 key, void *data);
DLLINCLUDE TreeNode_t *tree_add(u32 key, void *data, TreeNode_t **leaf);
DLLINCLUDE TreeNode_t *tree_find(u32 key, TreeNode_t *leaf);
DLLINCLUDE Error_t tree_freetree(TreeNode_t *leaf, Error_t(*data_free)(void *));

#endif