#include "List.h"
#include <stdlib.h>

list_CObj* create_list_CObj() {
    list_CObj* list = (list_CObj*)malloc(sizeof(list_CObj));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void list_CObj_push_back(list_CObj* list, struct CObj* obj) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->obj = obj;
    newNode->next = NULL;
    if (list->tail) {
        list->tail->next = newNode;
    } else {
        list->head = newNode;
    }
    list->tail = newNode;
}

struct CObj* list_CObj_get(ListNode* node) {
    return node->obj;
}

ListNode* list_CObj_begin(list_CObj* list) {
    return list->head;
}

bool list_CObj_end(ListNode* node, list_CObj* list) {
    return node == NULL;
}

void list_CObj_next(ListNode** node) {
    if (*node) {
        *node = (*node)->next;
    }
}
