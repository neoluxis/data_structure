#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    int priority;       /* 优先级（值越大优先级越高） */
    struct Node* next;
};

/* 入队：按优先级降序插入，O(n) */
struct Node* enqueue(struct Node* head, int data, int priority) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->priority = priority;
    newNode->next = NULL;

    /* 空链表或新节点优先级最高 → 头部插入 */
    if (head == NULL || head->priority < priority) {
        newNode->next = head;
        return newNode;
    }

    /* 遍历找到合适位置（保持降序） */
    struct Node* cur = head;
    while (cur->next != NULL && cur->next->priority >= priority) {
        cur = cur->next;
    }
    newNode->next = cur->next;
    cur->next = newNode;
    return head;
}

/* 出队：移除头节点（优先级最高），O(1) */
struct Node* dequeue(struct Node* head) {
    if (head == NULL) return NULL;
    struct Node* temp = head;
    printf("出队: data=%d, priority=%d\n", temp->data, temp->priority);
    head = head->next;
    free(temp);
    return head;
}

int main() {
    struct Node* pq = NULL;

    pq = enqueue(pq, 10, 1);  /* 数据 10，优先级 1 */
    pq = enqueue(pq, 20, 5);  /* 数据 20，优先级 5 */
    pq = enqueue(pq, 30, 3);  /* 数据 30，优先级 3 */

    pq = dequeue(pq);  /* 出队: data=20, priority=5 (最高优先级) */
    pq = dequeue(pq);  /* 出队: data=30, priority=3 */
    pq = dequeue(pq);  /* 出队: data=10, priority=1 */
    return 0;
}