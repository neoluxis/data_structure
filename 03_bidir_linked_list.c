#include "stdio.h"
#include "stdlib.h"

typedef struct Node {
  int data;          /* 数据域 */
  struct Node *prev; /* 前驱指针：指向前一个节点 */
  struct Node *next; /* 后继指针：指向后一个节点 */
} Node;

/* 创建新节点 */
struct Node *createNode(int value) {
  struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
  newNode->data = value;
  newNode->prev = NULL;
  newNode->next = NULL;
  return newNode;
}

/* 在头部插入节点
   步骤：新节点的 next 指向原头节点，原头节点的 prev 指向新节点 */
struct Node *insertAtHead(struct Node *head, int value) {
  struct Node *newNode = createNode(value);
  if (head != NULL) {
    newNode->next = head;
    head->prev = newNode;
  }
  return newNode; /* 新节点成为新头节点 */
}

/* 在指定节点之后插入新节点
   需要操作 4 个指针：
   1-2: 新节点的 prev 和 next
   3:   后继节点的 prev（如果存在）
   4:   前驱节点的 next */
void insertAfter(struct Node *prevNode, int value) {
  if (prevNode == NULL)
    return;

  struct Node *newNode = createNode(value);
  newNode->next = prevNode->next; /* 新节点的 next 指向原后继 */
  newNode->prev = prevNode;       /* 新节点的 prev 指向前驱 */

  if (prevNode->next != NULL) {
    prevNode->next->prev = newNode; /* 原后继的 prev 指向新节点 */
  }
  prevNode->next = newNode; /* 前驱的 next 指向新节点 */
}

/* 删除指定节点（不需要知道前驱节点，这是双向链表最大的优势）
   步骤：让前后节点互连，跳过当前节点，然后释放当前节点 */
void deleteNode(struct Node **headRef, struct Node *del) {
  if (*headRef == NULL || del == NULL)
    return;

  /* 如果删除的是头节点，更新头指针 */
  if (*headRef == del) {
    *headRef = del->next;
  }

  /* 让前驱节点的 next 指向后继节点 */
  if (del->prev != NULL) {
    del->prev->next = del->next;
  }

  /* 让后继节点的 prev 指向前驱节点 */
  if (del->next != NULL) {
    del->next->prev = del->prev;
  }

  free(del); /* 释放被删除的节点 */
}

#include <stdio.h>

/* 正向遍历：从 head 开始，沿 next 方向 */
void traverseForward(struct Node *head) {
  printf("正向遍历: ");
  struct Node *cur = head;
  while (cur != NULL) {
    printf("%d ", cur->data);
    cur = cur->next;
  }
  printf("\n");
}

/* 反向遍历：从 tail 开始，沿 prev 方向
   需要先找到尾部节点 */
void traverseBackward(struct Node *head) {
  if (head == NULL)
    return;

  /* 先走到最后一个节点（即尾部） */
  struct Node *cur = head;
  while (cur->next != NULL) {
    cur = cur->next;
  }

  /* 从尾部沿 prev 方向返回头部 */
  printf("反向遍历: ");
  while (cur != NULL) {
    printf("%d ", cur->data);
    cur = cur->prev;
  }
  printf("\n");
}

int main() {
  struct Node *head = NULL;
  /* 构建链表: 10 <-> 20 <-> 30 */
  head = insertAtHead(head, 30);
  head = insertAtHead(head, 20);
  head = insertAtHead(head, 10);

  traverseForward(head);  /* 输出: 正向遍历: 10 20 30 */
  traverseBackward(head); /* 输出: 反向遍历: 30 20 10 */
  return 0;
}
