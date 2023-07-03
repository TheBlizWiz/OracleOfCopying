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

void printlist(ListNode_t *head) {
    if (head) {
        printnode(head);
        printlist(head->next);
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

    ListNode_t *list = NULLADDR;

    list = list_addtotail(list, 4, str4, str_free_fnptr, str_cmp_fnptr);
    list = list_addtohead(list, 1, str1, str_free_fnptr, str_cmp_fnptr);
    list = list_addtohead(list, 5, str5, str_free_fnptr, str_cmp_fnptr);
    list = list_addtotail(list, 3, str3, str_free_fnptr, str_cmp_fnptr);
    list = list_addtohead(list, 2, str2, str_free_fnptr, str_cmp_fnptr);
    list = list_addtotail(list, 0, str0, str_free_fnptr, str_cmp_fnptr);

    printf("\n\n\n-------------LIST--------------\n\n\n");

    printlist(list);

    printf("\n\n\n---------SORTED LIST-----------\n\n\n");

    list_mergesortbykey(&list);

    printlist(list);

    if (!(list = list_freelist(list))) {
        printf("\nfreed list\n");
    }
    else {
        printf("\noh fuck a memory leak\n");
    }

    return 0;
}
