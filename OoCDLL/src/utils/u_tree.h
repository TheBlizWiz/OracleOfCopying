#ifndef U_TREE_H
#define U_TREE_H

#ifdef OOCDLL_EXPORTS
#define U_TREE_API __declspec(dllexport)
#else
#define U_TREE_API __declspec(dllimport)
#endif

#include "defs/d_common.h"

U_TREE_API TreeNode_t *tree_new(u32 key, void *data);
U_TREE_API TreeNode_t *tree_add(u32 key, void *data, TreeNode_t **leaf);
U_TREE_API TreeNode_t *tree_find(u32 key, TreeNode_t *leaf);
U_TREE_API Error_t tree_freetree(TreeNode_t *leaf, Error_t(*data_free)(void *));

#endif