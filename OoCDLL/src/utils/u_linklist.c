#include <stdio.h>
#include <stdlib.h>

#include "defs/d_common.h"
#include "defs/d_constants.h"

#include "u_linklist.h"

Error_t list_new(u32 key, void *data, ListNode_t **head) {

}

Error_t list_addtofront(u32 key, void *data, ListNode_t **head) {

}

Error_t list_addafter(u32 key, void *data, ListNode_t *prevnode) {

}

Error_t list_addbefore(u32 key, void *data, ListNode_t *nextnode) {

}

Error_t list_addtoback(u32 key, void *data, ListNode_t **head) {

}

Error_t list_reverse(ListNode_t **head) {

}

Error_t list_freenode(ListNode_t *del, ListNode_t **head){

}

Error_t list_freelist(ListNode_t **head, Error_t(*data_free) (void *data)) {

}

Error_t data_free(void *data) {

}

// Error_t list_isort() {
//
// }

// Error_t list_qsort() {
// 
// }