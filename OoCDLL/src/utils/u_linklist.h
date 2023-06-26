#ifndef U_LINKLIST_H
#define U_LINKLIST_H

#ifdef OOCDLL_EXPORTS
#define U_LINKLIST_API __declspec(dllexport)
#else
#define U_LINKLIST_API __declspec(dllimport)
#endif

#include "defs/d_common.h"

U_LINKLIST_API List_t *list_new(u32 key, void *data, DataFree_fnptr datafree, DataCmp_fnptr datacmp);

U_LINKLIST_API ListNode_t *listnode_new(u32 key, void *data, DataFree_fnptr datafree, DataCmp_fnptr datacmp);

U_LINKLIST_API Error_t list_add(List_t *list, u32 key, void *data, DataFree_fnptr datafree, DataCmp_fnptr datacmp);

//U_LINKLIST_API ListNode_t *list_add(ListNode_t *head, u32 key, void *data, DataFree_fnptr datafree, DataCmp_fnptr datacmp);

U_LINKLIST_API Error_t list_addtotail(List_t *list, u32 key, void *data, DataFree_fnptr datafree, DataCmp_fnptr datacmp);

//U_LINKLIST_API Error_t list_addbeforebykey(List_t *list, u32 key, void *data, DataFree_fnptr datafree, DataCmp_fnptr datacmp, u32 tgtkey);

//U_LINKLIST_API Error_t list_addafterbykey(List_t *list, u32 key, void *data, DataFree_fnptr datafree, DataCmp_fnptr datacmp, u32 tgtkey);

//U_LINKLIST_API Error_t list_addbeforebydata(List_t *list, u32 key, void *data, DataFree_fnptr datafree, DataCmp_fnptr datacmp, const void *tgtdata);

//U_LINKLIST_API Error_t list_addafterbydata(List_t *list, u32 key, void *data, DataFree_fnptr datafree, DataCmp_fnptr datacmp, const void *tgtdata);

U_LINKLIST_API ListNode_t *list_gettail(List_t *list);

U_LINKLIST_API ListNode_t *list_searchbykey(List_t *list, u32 tgtkey);

U_LINKLIST_API Error_t list_sortbykey(List_t *list);

U_LINKLIST_API Error_t list_addsortedbykey(List_t *list, ListNode_t *newnode);

U_LINKLIST_API ListNode_t *list_searchbydata(List_t *list, const void *tgtdata);

U_LINKLIST_API Error_t list_sortbydata(List_t *list);

U_LINKLIST_API Error_t list_addsortedbydata(List_t *list, ListNode_t *node);

U_LINKLIST_API Error_t list_renumberkeys(List_t *list);

U_LINKLIST_API Error_t list_reverse(List_t *list);

U_LINKLIST_API Error_t listnode_free(ListNode_t *node);

U_LINKLIST_API Error_t list_freenodebykey(List_t *list, u32 tgtkey);

U_LINKLIST_API Error_t list_freenodebydata(List_t *list, const void *tgtdata);

U_LINKLIST_API Error_t list_freelist(List_t *list);







#endif