#ifndef U_LINKLIST_H
#define U_LINKLIST_H

#ifdef OOCDLL_EXPORTS
#define U_LINKLIST_API __declspec(dllexport)
#else
#define U_LINKLIST_API __declspec(dllimport)
#endif

#include "defs/d_common.h"

U_LINKLIST_API Error_t list_new(u32 key, void *data, ListNode_t **head);

U_LINKLIST_API Error_t list_addtofront(u32 key, void *data, ListNode_t **head);
U_LINKLIST_API Error_t list_addafter(u32 key, void *data, ListNode_t *prevnode);
U_LINKLIST_API Error_t list_addbefore(u32 key, void *data, ListNode_t *nextnode);
U_LINKLIST_API Error_t list_addtoback(u32 key, void *data, ListNode_t **head);

U_LINKLIST_API Error_t list_reverse(ListNode_t **head);

U_LINKLIST_API Error_t list_freenode(ListNode_t *del, ListNode_t **head);
U_LINKLIST_API Error_t list_freelist(ListNode_t **head, Error_t (*data_free) (void *data)); // spooky scary function pointer
U_LINKLIST_API Error_t data_free(void *data);

//U_LINKLIST_API Error_t list_isort(); TODO: insertion sort a double link list PROBLEM: by key or by the data itself?
//U_LINKLIST_API Error_t list_qsort(); TODO: quick sort a double link list     PROBLEM: by key or by the data itself?

#endif