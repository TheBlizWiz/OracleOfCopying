#ifndef U_LIST_H
#define U_LIST_H

#include "defs/d_common.h"

DLLINCLUDE typedef struct ListNode ListNode_t;
DLLINCLUDE typedef struct List List_t;

struct ListNode {
    u32 key;
    void *data;
    free_fnptr datafree;
    cmp_fnptr datacmp;

    struct ListNode *next;
};

struct List {
    struct ListNode **headptr;
    Size_t size;
};

// NOTE: u_list.h and u_list.c are adapted from GH user Leyxargon
// from repo https://github.com/Leyxargon/c-linked-list/blob/master/
// thank you for the help


DLLINCLUDE ListNode_t *listnode_new(u32 key, void *data, free_fnptr datafree, cmp_fnptr datacmp);

DLLINCLUDE ListNode_t *list_addtohead(ListNode_t *head, u32 key, void *data, free_fnptr datafree, cmp_fnptr datacmp);

DLLINCLUDE ListNode_t *list_addtotail(ListNode_t *head, u32 key, void *data, free_fnptr datafree, cmp_fnptr datacmp);

DLLINCLUDE ListNode_t *list_addsortedbykey(ListNode_t *head, u32 key, void *data, free_fnptr datafree, cmp_fnptr datacmp);

DLLINCLUDE ListNode_t *list_addsortedbydata(ListNode_t *head, u32 key, void *data, free_fnptr datafree, cmp_fnptr datacmp);

DLLINCLUDE ListNode_t *list_searchbykey(ListNode_t *head, const u32 tgtkey);

DLLINCLUDE ListNode_t *list_searchbydata(ListNode_t *head, const void *tgtdata);

DLLINCLUDE ListNode_t *list_freenodebykey(ListNode_t *head, const u32 tgtkey);

DLLINCLUDE ListNode_t *list_freenodebydata(ListNode_t *head, const void *tgtdata);

DLLINCLUDE ListNode_t *list_freelist(ListNode_t *head);

DLLINCLUDE Error_t list_mergesortbykey(ListNode_t **head);

DLLINCLUDE Error_t list_mergesortbydata(ListNode_t **head);

DLLINCLUDE ListNode_t *list_mergebykey(ListNode_t *headA, ListNode_t *headB);

DLLINCLUDE ListNode_t *list_mergebydata(ListNode_t *headA, ListNode_t *headB);

DLLINCLUDE Error_t *list_split(ListNode_t *currhead, ListNode_t **newhead, ListNode_t **newtail);

DLLINCLUDE void list_renumber(ListNode_t *head);

void _list_renumber(ListNode_t *head, u32 newkey);

#endif