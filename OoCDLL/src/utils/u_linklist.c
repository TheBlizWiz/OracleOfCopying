#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs/d_common.h"
#include "defs/d_constants.h"

#include "utils/u_linklist.h"

List_t *list_new(u32 key, void *data, DataFree_fnptr datafree, DataCmp_fnptr datacmp) {
    if (data) {
        List_t *list = (List_t *) malloc(sizeof(List_t));
        if (list) {
            memset(list, 0, sizeof(List_t));

            ListNode_t *node = listnode_new(key, data, datafree, datacmp);
            if (node) {
                list->headptr = &node;
                list->size = 1;
                return list;
            }
            else {
                errprintf("ERROR: malloc for first ListNode_t failed, can't make new list. Returning list with size zero...\n");
                list->headptr = NULLADDR;
                list->size = 0;
                return list;
            }
        }
        else {
            errprintf("ERROR: no malloc space for new List_t *.\n");
            return NULLADDR;
        }
    }
    else {
        errprintf("ERROR: *data is null, can't make new ListNode_t *.\n");
        return NULLADDR;
    }
}

ListNode_t *listnode_new(u32 key, void *data, DataFree_fnptr datafree, DataCmp_fnptr datacmp) {
    if (data) {
        ListNode_t *node = (ListNode_t *) malloc(sizeof(ListNode_t));
        if (node) {
            memset(node, 0, sizeof(ListNode_t));
            node->key = key;
            node->data = data;
            node->datafree = datafree;
            node->datacmp = datacmp;
            node->next = NULLADDR;
            return node;
        }
        else {
            errprintf("ERROR: no malloc space for new ListNode_t *.\n");
            return NULLADDR;
        }
    }
    else {
        errprintf("ERROR: *data is null, can't make new ListNode_t *.\n");
        return NULLADDR;
    }
}


Error_t list_add(List_t *list, u32 key, void *data, DataFree_fnptr datafree, DataCmp_fnptr datacmp) {
    if (data) {
        if (list) {
            if (list->size > 0) {
                if (list->headptr) {
                    if ((*list->headptr)) {
                        ListNode_t *node = listnode_new(key, data, datafree, datacmp);
                        if (node) {
                            node->next = (*list->headptr);
                            list->headptr = &node;
                            list->size++;
                            return (Error_t) ERROR_NOERROR;
                        }
                        else {
                            errprintf("ERROR: malloc for ListNode_t failed, can't add to list.\n");
                            return (Error_t) ERROR_MALLOC_NOSPACE;
                        }
                    }
                    else {
                        errprintf("ERROR: *list has size greater than zero but the node at **headptr is null! Can't add node to list...\n");
                        return (Error_t) ERROR_ISNULLADDR;
                    }
                }
                else {
                    errprintf("ERROR: *list has size greater than zero but headptr is null. Can't add node to list.\n");
                    return (Error_t) ERROR_ISNULLADDR;
                }
            }
            else if (list->size == 0) {
                ListNode_t *node = listnode_new(key, data, datafree, datacmp);
                if (node) {
                    list->headptr = &node;
                    list->size = 1;
                    return (Error_t) ERROR_NOERROR;
                }
                else {
                    errprintf("WARNING: malloc for ListNode_t failed, can't add to list.\n");
                    list->headptr = NULLADDR;
                    list->size = 0;
                    return (Error_t) ERROR_MALLOC_NOSPACE;
                }
            }
            else {
                errprintf("URGENT ERROR: List_t *list has a size less than zero? How did this happen? Can't add to list...\n");
                return (Error_t) ERROR_LENGTH_INVALIDVALUE;
            }
        }
        else {
            errprintf("ERROR: List_t *list is null, can't add to list.\n");
            return (Error_t) ERROR_ISNULLADDR;
        }
    }
    else {
        errprintf("ERROR: *data is null, can't make new ListNode_t *.\n");
        return (Error_t) ERROR_ISNULLADDR;

    }
}


/*
ListNode_t *list_add(ListNode_t *head, u32 key, void *data, DataFree_fnptr datafree, DataCmp_fnptr datacmp) {
    if (data) {
        if (head) {
            ListNode_t *newhead = listnode_new(key, data, datafree, datacmp);
            if (newhead) {
                newhead->next = head;
                return newhead;
            }
            else {
                errprintf("ERROR: no malloc space for new node\n");
                return NULLADDR;
            }
        }
        else {
            errprintf("ERROR: head is null\n");
            return NULLADDR;
        }
    }
    else {
        errprintf("ERROR: data is null\n");
        return NULLADDR;
    }
}
*/

Error_t list_addtotail(List_t *list, u32 key, void *data, DataFree_fnptr datafree, DataCmp_fnptr datacmp) {
    ListNode_t *tail = list_gettail(list);
    if (tail) {
        ListNode_t *node = listnode_new(key, data, datafree, datacmp);
        if (node) {
            tail->next = node;
            list->size++;
            return (Error_t) ERROR_NOERROR;
        }
        else {
            errprintf("ERROR: malloc for ListNode_t failed, can't add to list.\n");
            return (Error_t) ERROR_MALLOC_NOSPACE;
        }
    }
    else {
        errprintf("ERROR: Can't add to tail, *tail is null\n");
        return (Error_t) ERROR_ISNULLADDR;
    }
}

ListNode_t *list_gettail(List_t *list) {
    if (list) {
        if (list->size > 0) {
            if (list->headptr) {
                if ((*list->headptr)) {
                    ListNode_t *node = (*list->headptr);
                    while (node && node->next) {
                        node = node->next;
                    }
                    return node;
                }
                else {
                    errprintf("ERROR: *list has size greater than zero but the node at headptr is null! Can't get tail...\n");
                    return NULLADDR;
                }
            }
            else {
                errprintf("ERROR: list->headptr is null, can't find head of list\n");
                return NULLADDR;
            }
        }
        else if (list->size == 0) {
            errprintf("ERROR: *list is empty, can't get tail\n");
            return NULLADDR;
        }
        else {
            errprintf("URGENT ERROR: *list has size less than zero! Can't search list...\n");
            return NULLADDR;
        }
    }
    else {
        errprintf("ERROR: List_t *list is null, can't get tail.\n");
        return NULLADDR;
    }
}

ListNode_t *list_searchbykey(List_t *list, u32 tgtkey) {
    if (list) {
        if (list->size > 0) {
            if (list->headptr) {
                if ((*list->headptr)) {
                    ListNode_t *node = (*list->headptr);
                    while (node && node->key != tgtkey) {
                        node = node->next;
                    }
                    if (!node) {
                        errprintf("NOTE: couldn't find key %d in *list, returning null ListNode_t\n", tgtkey);
                    }
                    return node;
                }
                else {
                    errprintf("ERROR: *list has size greater than zero but the node at headptr is null! Can't search list...\n");
                    return NULLADDR;
                }
            }
            else {
                errprintf("ERROR: list->headptr is null, can't find head of list\n");
                return NULLADDR;
            }
        }
        else if (list->size == 0) {
            errprintf("ERROR: *list is empty, can't search list\n");
            return NULLADDR;
        }
        else {
            errprintf("URGENT ERROR: *list has size less than zero! Can't search list...\n");
            return NULLADDR;
        }
    }
    else {
        errprintf("ERROR: List_t *list is null, can't search list.\n");
        return NULLADDR;
    }
}

Error_t list_sortbykey(List_t *list) {
    if (list) {
        if (list->size > 1) {
            if (list->headptr) {
                if ((*list->headptr)) {
                    ListNode_t *curr = (*list->headptr);
                    Error_t e = ERROR_NOERROR;
                    while (curr) {
                        ListNode_t *next = curr->next;
                        e = list_addsortedbykey(list, curr);
                        curr = next;
                    }
                    return (Error_t) ERROR_NOERROR + e;
                }
                else {
                    errprintf("ERROR: *list has size greater than zero but the node at headptr is null! Can't sort list...\n");
                    return (Error_t) ERROR_ISNULLADDR;
                }
            }
            else {
                errprintf("ERROR: list->headptr is null, can't find head of list\n");
                return (Error_t) ERROR_ISNULLADDR;
            }
        }
        else if (list->size == 1) {
            errprintf("NOTE: list only has 1 node, already sorted");
            return (Error_t) ERROR_NOERROR;
        }
        else if (list->size == 0) {
            errprintf("NOTE: List is empty, nothing to sort\n");
            return (Error_t) ERROR_NOERROR;
        }
        else {
            errprintf("ERROR: *list has size less than zero! Can't sort list...\n");
            return (Error_t) ERROR_LENGTH_INVALIDVALUE;
        }
    }
    else {
        errprintf("ERROR: List_t *list is null, can't sort list.\n");
        return (Error_t) ERROR_ISNULLADDR;
    }
}

Error_t list_addsortedbykey(List_t *list, ListNode_t *newnode) {
    if (list) {
        if (list->headptr) {
            if ((*list->headptr)) {
                ListNode_t *curr = (*list->headptr);

                if (curr->key >= newnode->key) { // if newnode needs to be the new head
                    newnode->next = curr;
                    list->headptr = &newnode;
                    return (Error_t) ERROR_NOERROR;
                }
                else {
                    while (curr->next && curr->next->key < newnode->key) {
                        curr = curr->next;
                    }
                    newnode->next = curr->next;
                    curr->next = newnode;
                    return (Error_t) ERROR_NOERROR;
                }
            }
            else {
                errprintf("ERROR: node at list->headptr is null, can't find list\n");
                return (Error_t) ERROR_ISNULLADDR;
            }
        }
        else {
            errprintf("ERROR: list->headptr is null, can't find list\n");
            return (Error_t) ERROR_ISNULLADDR;
        }
    }
    else {
        errprintf("ERROR: list is null, can't find list\n");
        return (Error_t) ERROR_ISNULLADDR;
    }
}

ListNode_t *list_searchbydata(List_t *list, const void *tgtdata) {
    if (tgtdata) {
        if (list) {
            if (list->size > 0) {
                if (list->headptr) {
                    if ((*list->headptr)) {
                        ListNode_t *node = (*list->headptr);
                        while (node && (node->datacmp(node->data, tgtdata) != 0)) {
                            node = node->next;
                        }
                        return node;
                    }
                    else {
                        errprintf("ERROR: *list has size greater than zero but the node at **headptr is null! Can't search list...\n");
                        return NULLADDR;
                    }
                }
                else {
                    errprintf("ERROR: list->headptr is null, can't find list\n");
                    return NULLADDR;
                }
            }
            else if (list->size == 0) {
                errprintf("ERROR: *list is empty, can't search list\n");
                return NULLADDR;
            }
            else {
                errprintf("ERROR: *list has size less than zero! Can't search list...\n");
                return NULLADDR;
            }
        }
        else {
            errprintf("ERROR: List_t *list is null, can't search list.\n");
            return NULLADDR;
        }
    }
    else {
        errprintf("ERRROR: *tgtdata is null, can't compare data\n");
        return NULLADDR;
    }
}

Error_t list_sortbydata(List_t *list) {
    if (list) {
        if (list->size > 1) {
            if (list->headptr) {
                if ((*list->headptr)) {
                    ListNode_t *curr = (*list->headptr);
                    Error_t e = ERROR_NOERROR;
                    while (curr) {
                        ListNode_t *next = curr->next;
                        e = list_addsortedbydata(list, curr);
                        curr = next;
                    }
                    return (Error_t) ERROR_NOERROR + e;
                }
                else {
                    errprintf("ERROR: *list has size greater than zero but the node at headptr is null! Can't sort list...\n");
                    return (Error_t) ERROR_ISNULLADDR;
                }
            }
            else {
                errprintf("ERROR: list->headptr is null, can't find head of list\n");
                return (Error_t) ERROR_ISNULLADDR;
            }
        }
        else if (list->size == 1) {
            errprintf("NOTE: list only has 1 node, already sorted");
            return (Error_t) ERROR_NOERROR;
        }
        else if (list->size == 0) {
            errprintf("NOTE: List is empty, nothing to sort\n");
            return (Error_t) ERROR_NOERROR;
        }
        else {
            errprintf("ERROR: *list has size less than zero! Can't sort list...\n");
            return (Error_t) ERROR_LENGTH_INVALIDVALUE;
        }
    }
    else {
        errprintf("ERROR: List_t *list is null, can't sort list.\n");
        return (Error_t) ERROR_ISNULLADDR;
    }
}

Error_t list_addsortedbydata(List_t *list, ListNode_t *newnode) {
    if (list) {
        if (list->headptr) {
            if ((*list->headptr)) {
                ListNode_t *curr = (*list->headptr);

                if ((newnode->datacmp((const void *) newnode->data, (const void *) curr->data)) <= 0) { // if newnode needs to be the new head
                    newnode->next = curr;
                    list->headptr = &newnode;
                    return (Error_t) ERROR_NOERROR;
                }
                else {
                    while (curr->next && (newnode->datacmp((const void *) newnode->data, (const void *) curr->data)) > 0) {
                        curr = curr->next;
                    }
                    newnode->next = curr->next;
                    curr->next = newnode;
                    return (Error_t) ERROR_NOERROR;
                }
            }
            else {
                errprintf("ERROR: node at list->headptr is null, can't find list\n");
                return (Error_t) ERROR_ISNULLADDR;
            }
        }
        else {
            errprintf("ERROR: list->headptr is null, can't find list\n");
            return (Error_t) ERROR_ISNULLADDR;
        }
    }
    else {
        errprintf("ERROR: list is null, can't find list\n");
        return (Error_t) ERROR_ISNULLADDR;
    }
}

Error_t list_renumberkeys(List_t *list) {
    if (list) {
        if (list->headptr) {
            if ((*list->headptr)) {
                u32 k = 0;
                ListNode_t *node = (*list->headptr);
                while (node) {
                    node->key = k;
                    node = node->next;
                }
                return (Error_t) ERROR_NOERROR;
            }
            else {
                errprintf("ERROR: node at list->headptr is null, can't renumber keys.\n");
                return (Error_t) ERROR_ISNULLADDR;
            }
        }
        else {
            errprintf("ERROR: list->headptr is null, can't find list\n");
            return (Error_t) ERROR_ISNULLADDR;
        }
    }
    else {
        errprintf("ERROR: list is null, can't find list\n");
        return (Error_t) ERROR_ISNULLADDR;
    }
}

Error_t list_reverse(List_t *list) {
    if (list) {
        if (list->size > 1) {
            if (list->headptr) {
                if ((*list->headptr)) {
                    ListNode_t *prev = NULLADDR;
                    ListNode_t *curr = (*list->headptr);
                    ListNode_t *next = NULLADDR;
                    while (curr) {
                        next = curr->next;
                        curr->next = prev;
                        prev = curr;
                        curr = next;
                    }
                    list->headptr = &prev;
                    return (Error_t) ERROR_NOERROR;
                }
                else {
                    errprintf("ERROR: node at list->headptr is null, can't find list\n");
                    return (Error_t) ERROR_ISNULLADDR;
                }
            }
            else {
                errprintf("ERROR: list->headptr is null, can't find list\n");
                return (Error_t) ERROR_ISNULLADDR;
            }
        }
        else if (list->size == 1) {
            errprintf("NOTE: list only has 1 node, already reversed");
            return (Error_t) ERROR_NOERROR;
        }
        else if (list->size == 0) {
            errprintf("NOTE: List is empty, nothing to reverse\n");
            return (Error_t) ERROR_NOERROR;
        }
        else {
            errprintf("ERROR: *list has size less than zero! Can't reverse list...\n");
            return (Error_t) ERROR_LENGTH_INVALIDVALUE;
        }
    }
    else {
        errprintf("ERROR: list is null, can't find list\n");
        return (Error_t) ERROR_ISNULLADDR;
    }
}

Error_t listnode_free(ListNode_t *node) {
    if (node) {
        Error_t e = node->datafree(node->data);
        if (e == ERROR_NOERROR) {
            free(node);
            return e;
        }
        else {
            errprintf("ERROR: something went wrong with *node->datafree\n");
            return e;
        }
    }
    else {
        errprintf("ERROR: *node is null, can't free *node.\n");
        return (Error_t) ERROR_ISNULLADDR;
    }
}

Error_t list_freenodebykey(List_t *list, u32 tgtkey) {
    ListNode_t *node = list_searchbykey(list, tgtkey);
    return listnode_free(node);
}

Error_t list_freenodebydata(List_t *list, const void *tgtdata) {
    ListNode_t *node = list_searchbydata(list, tgtdata);
    return listnode_free(node);
}

Error_t list_freelist(List_t *list) {
    if (list) {
        // we can't trust list->size here since we don't want to leak
        if (list->headptr) {
            ListNode_t *node = (*list->headptr);
            Error_t e = ERROR_NOERROR;
            while (node) {
                list->headptr = &node->next;
                e += listnode_free(node);
                node = (*list->headptr);
            }
            free(list);
            return (Error_t) ERROR_NOERROR + e;
        }
        else {
            errprintf("ERROR: list->headptr is null, can't find list\n");
            return (Error_t) ERROR_ISNULLADDR;
        }
    }
    else {
        errprintf("ERROR: Can't free list, *list is null\n");
        return (Error_t) ERROR_ISNULLADDR;
    }
}

