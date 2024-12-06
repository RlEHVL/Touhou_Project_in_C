#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include "CObj.h"

typedef struct ListNode {
    struct CObj* obj;          // CObj 포인터
    struct ListNode* next;     // 다음 노드
} ListNode;

typedef struct {
    ListNode* head;            // 리스트의 첫 번째 노드
    ListNode* tail;            // 리스트의 마지막 노드
} list_CObj;

// 함수 선언
list_CObj* create_list_CObj();
void list_CObj_push_back(list_CObj* list, struct CObj* obj);
struct CObj* list_CObj_get(ListNode* node);
ListNode* list_CObj_begin(list_CObj* list);
bool list_CObj_end(ListNode* node, list_CObj* list);
void list_CObj_next(ListNode** node);

#endif // LIST_H
