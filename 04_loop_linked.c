#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

/* 创建新节点 */
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = newNode;  /* 单节点时，next 指向自身，自成环 */
    return newNode;
}

/* 在循环链表头部插入节点
   时间复杂度：O(n) — 需要先找到尾部节点来更新其 next 指针 */
struct Node* insertAtHead(struct Node* head, int value) {
    struct Node* newNode = createNode(value);

    if (head == NULL) {
        return newNode;  /* 空链表，新节点自成环 */
    }

    /* 找到尾部节点（即 next 指向 head 的节点） */
    struct Node* tail = head;
    while (tail->next != head) {
        tail = tail->next;
    }

    newNode->next = head;   /* 新节点的 next 指向原头节点 */
    tail->next = newNode;   /* 尾节点的 next 指向新节点（新头） */
    return newNode;          /* 新节点成为新的头节点 */
}

/* 遍历循环链表（一圈）
   从头节点开始，直到再次回到头节点时停止 */
void traverse(struct Node* head) {
    if (head == NULL) return;

    struct Node* cur = head;
    printf("循环链表: ");
    do {
        printf("%d -> ", cur->data);
        cur = cur->next;
    } while (cur != head);  /* 回到起点时结束 */
    printf("(回到起点)\n");
}

int main() {
    struct Node* head = NULL;
    head = insertAtHead(head, 30);
    head = insertAtHead(head, 20);
    head = insertAtHead(head, 10);

    traverse(head);
    /* 输出: 循环链表: 10 -> 20 -> 30 -> (回到起点) */
    return 0;
}