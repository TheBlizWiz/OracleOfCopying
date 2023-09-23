#include <stdio.h>
#include <stdlib.h>

#include "defs/d_common.h"
#include "defs/d_constants.h"
#include "defs/d_macros.h"

#include "u_list.h"

ListNode_t *listnode_new(u32 key, void *data, free_fnptr datafree, cmp_fnptr datacmp) {
    if (data) {
        ListNode_t *node = (ListNode_t *) malloc(sizeof(ListNode_t));
        if (node) {
            node->key = key;
            node->data = data;
            node->datafree = datafree;
            node->datacmp = datacmp;
            node->next = NULLADDR;
            return node;
        }
        else {
            errprintf("ERROR: no malloc space for new node\n");
            return NULLADDR;
        }
    }
    else {
        errprintf("ERROR: *data is null, can't make new node\n");
        return NULLADDR;
    }
}

ListNode_t *list_addtohead(ListNode_t *head, u32 key, void *data, free_fnptr datafree, cmp_fnptr datacmp) {
    ListNode_t *node = listnode_new(key, data, datafree, datacmp);
    if (node) {
        node->next = head;
        return node;
    }
    else {
        return NULLADDR;
    }
}

ListNode_t *list_addtotail(ListNode_t *head, u32 key, void *data, free_fnptr datafree, cmp_fnptr datacmp) {
    if (!head) {
        return listnode_new(key, data, datafree, datacmp);
    }
    else {
        head->next = list_addtotail(head->next, key, data, datafree, datacmp);
        return head;
    }
}

ListNode_t *list_addsortedbykey(ListNode_t *head, u32 key, void *data, free_fnptr datafree, cmp_fnptr datacmp) {
    if (!head || head->key > key) {
        ListNode_t *node = listnode_new(key, data, datafree, datacmp);
        node->next = head;
        head = node;
        return head;
    }
    else {
        head->next = list_addsortedbykey(head->next, key, data, datafree, datacmp);
        return head;
    }
}

ListNode_t *list_addsortedbydata(ListNode_t *head, u32 key, void *data, free_fnptr datafree, cmp_fnptr datacmp) {
    if (!head || (head->datacmp(head->data, data) > 0)) {
        ListNode_t *node = listnode_new(key, data, datafree, datacmp);
        node->next = head;
        head = node;
        return head;
    }
    else {
        head->next = list_addsortedbydata(head->next, key, data, datafree, datacmp);
        return head;
    }
}

ListNode_t *list_searchbykey(ListNode_t *head, const u32 tgtkey) {
    if (!head || head->key == tgtkey) {
        return head;
    }
    else {
        return list_searchbykey(head->next, tgtkey);
    }
}

ListNode_t *list_searchbydata(ListNode_t *head, const void *tgtdata) {
    if (!head || (head->datacmp(head->data, tgtdata) == 0)) {
        return head;
    }
    else {
        return list_searchbydata(head->next, tgtdata);
    }
}

ListNode_t *list_freenodebykey(ListNode_t *head, const u32 tgtkey) {
    ListNode_t *node = NULLADDR;
    if (head) {
        if (head->key == tgtkey) {
            node = head->next;
            head->datafree(head->data);
            free(head);
            head = node;
        }
        else {
            head->next = list_freenodebykey(head->next, tgtkey);
        }
    }
    return head;
}

ListNode_t *list_freenodebydata(ListNode_t *head, const void *tgtdata) {
    ListNode_t *node = NULLADDR;
    if (head) {
        if (head->datacmp(head->data, tgtdata) == 0) {
            node = head->next;
            head->datafree(head->data);
            free(head);
            head = node;
        }
        else {
            head->next = list_freenodebydata(head->next, tgtdata);
        }
    }
    return head;
}

ListNode_t *list_freelist(ListNode_t *head) {
    if (head) {
        list_freelist(head->next);
        head->datafree(head->data);
        free(head);
        return NULLADDR;
    }
    else {
    //    errprintf("ERROR: list is null\n");
        return NULLADDR;
    }
}

Size_t *list_getsize(ListNode_t *head) {
    if (head == NULLADDR) {
        return 0;
    }
    else {
        return 1 + list_getsize(head->next);
    }
}

//todo: proper use of Error_t
// also how tf does merge sort work
Error_t list_mergesortbykey(ListNode_t **head) {
    ListNode_t *node = *head;
    ListNode_t *headA = NULLADDR;
    ListNode_t *headB = NULLADDR;

    if (node && node->next) {
        list_split(node, &headA, &headB);

        list_mergesortbykey(&headA);
        list_mergesortbykey(&headB);

        *head = list_mergebykey(headA, headB);

        return ERROR_NOERROR;
    }
    else {
      //  errprintf("ERRROR: list is null or only has 1 node\n");
      //  return ERROR_INVALID_PARAMS;
        return 0;
    }
}

//todo: proper use of Error_t
// also how tf does merge sort work
Error_t list_mergesortbydata(ListNode_t **head) {
    ListNode_t *node = *head;
    ListNode_t *headA = NULLADDR;
    ListNode_t *headB = NULLADDR;

    if (node && node->next) {
        list_split(node, &headA, &headB);

        list_mergesortbydata(&headA);
        list_mergesortbydata(&headB);

        *head = list_mergebydata(headA, headB);

        return ERROR_NOERROR;
    }
    else {
    //    errprintf("ERORR: list is null or only has 1 node\n");
    //    return ERROR_INVALID_PARAMS;
        return 0;
    }
}

ListNode_t *list_mergebykey(ListNode_t *headA, ListNode_t *headB) {
    if (!headA) {
        return headB;
    }
    else {
        if (!headB) {
            return headA;
        }

        ListNode_t *node = NULLADDR;
        if (headA->key > headB->key) {
            node = headA;
            node->next = list_mergebykey(headA->next, headB);
        }
        else {
            node = headB;
            node->next = list_mergebykey(headA, headB->next);
        }
        return node;
    }
}

ListNode_t *list_mergebydata(ListNode_t *headA, ListNode_t *headB) {
    if (!headA) {
        return headB;
    }
    else {
        if (!headB) {
            return headA;
        }

        ListNode_t *node = NULLADDR;
        if (headA->datacmp(headA->data, headB->data) > 0) {
            node = headA;
            node->next = list_mergebydata(headA->next, headB);
        }
        else {
            node = headB;
            node->next = list_mergebydata(headA, headB->next);
        }
        return node;
    }
}

// todo: proper use of error_t
Error_t *list_split(ListNode_t *currhead, ListNode_t **newhead, ListNode_t **newtail) {
    ListNode_t *fast = currhead->next;
    ListNode_t *slow = currhead;

    while (fast) {
        fast = fast->next;
        if (fast) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *newhead = currhead;
    *newtail = slow->next;
    slow->next = NULLADDR;

    return ERROR_NOERROR;
}

void list_renumber(ListNode_t *head) {
    _list_renumber(head, 0);
}

void _list_renumber(ListNode_t *head, u32 newkey) {
    if (!head) {
        return;
    }
    else {
        head->key = newkey;
        _list_renumber(head->next, newkey + 1);
    }
}