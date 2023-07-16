#ifndef U_LIST_H
#define U_LIST_H

#ifdef OOCDLL_EXPORTS
#define U_LIST_API __declspec(dllexport)
#else
#define U_LIST_API __declspec(dllimport)
#endif

#include "defs/d_common.h"

U_LIST_API typedef struct ListNode ListNode_t;
U_LIST_API typedef struct List List_t;

struct ListNode {
    u32 key;
    void *data;
    DataFree_fnptr datafree;
    DataCmp_fnptr datacmp;

    struct ListNode *next;
};

struct List {
    struct ListNode **headptr;
    Size_t size;
};

// NOTE: u_list.h and u_list.c are adapted from GH user Leyxargon
// from repo https://github.com/Leyxargon/c-linked-list/blob/master/
// thank you for the help


U_LIST_API ListNode_t *listnode_new(u32 key, void *data, DataFree_fnptr datafree, DataCmp_fnptr datacmp);

U_LIST_API ListNode_t *list_addtohead(ListNode_t *head, u32 key, void *data, DataFree_fnptr datafree, DataCmp_fnptr datacmp);

U_LIST_API ListNode_t *list_addtotail(ListNode_t *head, u32 key, void *data, DataFree_fnptr datafree, DataCmp_fnptr datacmp);

U_LIST_API ListNode_t *list_addsortedbykey(ListNode_t *head, u32 key, void *data, DataFree_fnptr datafree, DataCmp_fnptr datacmp);

U_LIST_API ListNode_t *list_addsortedbydata(ListNode_t *head, u32 key, void *data, DataFree_fnptr datafree, DataCmp_fnptr datacmp);

U_LIST_API ListNode_t *list_searchbykey(ListNode_t *head, const u32 tgtkey);

U_LIST_API ListNode_t *list_searchbydata(ListNode_t *head, const void *tgtdata);

U_LIST_API ListNode_t *list_freenodebykey(ListNode_t *head, const u32 tgtkey);

U_LIST_API ListNode_t *list_freenodebydata(ListNode_t *head, const void *tgtdata);

U_LIST_API ListNode_t *list_freelist(ListNode_t *head);

U_LIST_API Error_t list_mergesortbykey(ListNode_t **head);

U_LIST_API Error_t list_mergesortbydata(ListNode_t **head);

U_LIST_API ListNode_t *list_mergebykey(ListNode_t *headA, ListNode_t *headB);

U_LIST_API ListNode_t *list_mergebydata(ListNode_t *headA, ListNode_t *headB);

U_LIST_API Error_t *list_split(ListNode_t *currhead, ListNode_t **newhead, ListNode_t **newtail);

U_LIST_API void list_renumber(ListNode_t *head);

void _list_renumber(ListNode_t *head, u32 newkey);

#endif