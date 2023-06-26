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

    ListNode_t *node0 = listnode_new(0, str0, str_free, str_cmp_fptr);
    ListNode_t *node1 = listnode_new(1, str1, str_free, str_cmp_fptr);
    ListNode_t *node2 = listnode_new(2, str2, str_free, str_cmp_fptr);
    ListNode_t *node3 = listnode_new(3, str3, str_free, str_cmp_fptr);
    ListNode_t *node4 = listnode_new(4, str4, str_free, str_cmp_fptr);
    ListNode_t *node5 = listnode_new(5, str5, str_free, str_cmp_fptr);

    node0->next = node4;
    node4->next = node5;
    node5->next = node2;
    node2->next = node3;
    node3->next = node1;
    node1->next = NULLADDR;

    List_t *stanza1 = malloc(sizeof(List_t));
    stanza1->size = 6;
    stanza1->headptr = &node0;

    ListNode_t *curr = (*stanza1->headptr);
    while (curr) {
        printnode(curr);
        curr = curr->next;
    }

    list_sortbykey(stanza1);

    curr = (*stanza1->headptr);
    while (curr) {
        printnode(curr);
        curr = curr->next;
    }

    list_freelist(stanza1);

    return 0;
}
