#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "oocdll.h"

void printnode(ListNode_t *node) {
    if (node) {
        printf("\nNode at %p:\n", node);
        printf("\tkey: %d\n", node->key);
        printf("\tdata: %s\n", (String_t) node->data);

        if (node->next) {
            printf("\tnext: %p\n", node->next);
        }
        else {
            printf("\tnext: NULLADDR\n");
        }
    }
    else {
        printf("Node is null.\n");
    }
}

void print(struct node *node) {
    if (node) {
        printf("\nNode at %p:\n", node);
        printf("\tkey: %d\n", node->key);
        printf("\tdata: %s\n", (String_t) node->data);
        if (node->next) {
            printf("\tnext: %p\n", node->next);
        }
        else {
            printf("\tnext: NULLADDR\n");
        }
    }
    else {
        printf("Node is null.\n");
    }
}

int main(int argc, char *argv[]) {

    String_t str0 = str_new("Once upon a midnight dreary, while I pondered, weak and weary,");
    String_t str1 = str_new("Over many a quaint and curious volume of forgotten lore");
    String_t str2 = str_new("While I nodded, nearly napping, suddenly there came a tapping,");
    String_t str3 = str_new("As of some one gently rapping, rapping at my chamber door.");
    String_t str4 = str_new("\"'Tis some visitor,\" I muttered, \"tapping at my chamber door");
    String_t str5 = str_new("Only this and nothing more.\"");

//    String_t strA = str_new("Ah, distinctly I remember it was in the bleak December;");
//    String_t strB = str_new("And each separate dying ember wrought its ghost upon the floor.");
//    String_t strC = str_new("Eagerly I wished the morrow;—vainly I had sought to borrow");
//    String_t strD = str_new("From my books surcease of sorrow—sorrow for the lost Lenore—");
//    String_t strE = str_new("For the rare and radiant maiden whom the angels name Lenore—");
//    String_t strF = str_new("Nameless here for evermore.");

    ListNode_t *node = listnode_new(3, str3, str_free_fnptr, str_cmp_fnptr);
    if (!node) return -1;
    List_t *stanza1 = list_new();
    stanza1->headptr = &node;
    stanza1->size = 1;
    list_add(stanza1, 5, str5, str_free_fnptr, str_cmp_fnptr);
    list_add(stanza1, 2, str2, str_free_fnptr, str_cmp_fnptr);
    list_add(stanza1, 0, str0, str_free_fnptr, str_cmp_fnptr);
    list_add(stanza1, 4, str4, str_free_fnptr, str_cmp_fnptr);
    list_add(stanza1, 1, str1, str_free_fnptr, str_cmp_fnptr);

    ListNode_t *curr = (*stanza1->headptr);
    while (curr) {
        printnode(curr);
        curr = curr->next;
    }

    printf("\n\n\n-----------SORTING----------\n\n\n");

    ListNode_t *head = (*stanza1->headptr);
    list_isortbydata(stanza1, head);

    curr = (*stanza1->headptr);
    while (curr) {
        printnode(curr);
        curr = curr->next;
    }

    printf("\n\n\n-----------RENUMBERING----------\n\n\n");

    head = (*stanza1->headptr);
    printnode(head);
    list_renumberkeys(stanza1);

    curr = (*stanza1->headptr);
    while (curr) {
        printnode(curr);
        curr = curr->next;
    }


    list_freelist(stanza1);


    return 0;
}
