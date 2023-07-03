#include <stdio.h>
#include <stdlib.h>

#include "u_linklist_test.h"

void push(struct node **head, u32 key, void *data, DataFree_fnptr dfree, DataCmp_fnptr dcmp) {
    struct node *newnode = malloc(sizeof(struct node));
    if (newnode) {
        newnode->key = key;
        newnode->data = data;
        newnode->dfree = dfree;
        newnode->dcmp = dcmp;

        if (head) {
            newnode->next = (*head);
            (*head) = newnode;
        }
        else {
            newnode->next = NULL;
            head = &newnode;
        }
    }
}

void deletelist(struct node **head) {
    struct node *curr = *head;
    struct node *next;

    while (curr != NULL) {
        next = curr->next;
        curr->dfree(curr->data);
        free(curr);
        curr = next;
    }

    *head = NULL;
}