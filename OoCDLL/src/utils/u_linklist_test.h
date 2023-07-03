#ifndef U_LINKLIST_TEST_H
#define U_LINKLIST_TEST_H

#ifdef OOCDLL_EXPORTS
#define U_LLT_API __declspec(dllexport)
#else
#define U_LLT_API __declspec(dllimport)
#endif

#include "defs/d_common.h"

U_LLT_API typedef struct node testnode_t;

struct node {
    u32 key;
    void *data;
    DataFree_fnptr dfree;
    DataCmp_fnptr dcmp;
    struct node *next;
};

U_LLT_API void push(struct node **head, u32 key, void *data, DataFree_fnptr dfree, DataCmp_fnptr dcmp);

U_LLT_API void deletelist(struct node **head);
#endif
