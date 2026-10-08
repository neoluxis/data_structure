#include "stdio.h"
#include "stdlib.h"

typedef struct Node {
  int data;
  struct Node *next;
} Node;

struct Node *createNode(int val) {
  struct Node *node = (struct Node *)malloc(sizeof(struct Node));
  if (node == NULL) {
    puts("Failed to malloc");
    return NULL;
  }

  node->data = val;
  node->next = NULL;
  return node;
}

void traverse(struct Node *head) {
  struct Node *cur = head;
  while (cur != NULL) {
    printf("%d -> ", cur->data);
    cur = cur->next;
  }
  printf("NULL\n");
}

struct Node *createList(int n) {
  if (n <= 0)
    return NULL;

  struct Node *head = (struct Node *)malloc(sizeof(struct Node));
  head->data = 0;
  head->next = NULL;

  struct Node *tail = head; /* tail 始终指向最后一个节点 */
  for (int i = 2; i <= n; i++) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = 0;
    newNode->next = NULL;
    tail->next = newNode; /* 将新节点连接到链表末尾 */
    tail = newNode;       /* 更新 tail 指针 */
  }
  return head;
}

/* 在链表头部插入新节点（头插法）
   时间复杂度：O(1)
   返回值：新的头节点指针 */
struct Node *insertAtHead(struct Node *head, int value) {
  struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
  newNode->data = value;
  newNode->next = head; /* 新节点指向原头节点 */
  return newNode;       /* 新节点成为新的头节点 */
}

/* 在链表尾部插入新节点（尾插法）
   时间复杂度：O(n)，需要遍历到尾部 */
struct Node *insertAtTail(struct Node *head, int value) {
  struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
  newNode->data = value;
  newNode->next = NULL;

  if (head == NULL) {
    return newNode; /* 空链表，新节点即为头节点 */
  }

  struct Node *current = head;
  while (current->next != NULL) {
    current = current->next; /* 遍历到最后一个节点 */
  }
  current->next = newNode; /* 尾部节点指向新节点 */
  return head;
}

/* 在指定位置后插入新节点
   时间复杂度：O(n)，需要先找到 prevNode */
void insertAfter(struct Node *prevNode, int value) {
  if (prevNode == NULL) {
    printf("前驱节点不能为空\n");
    return;
  }
  struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
  newNode->data = value;
  /* 关键：先让新节点指向后继，再让前驱指向新节点 */
  newNode->next = prevNode->next;
  prevNode->next = newNode;
}

/* 删除链表头部节点
   时间复杂度：O(1)
   返回值：新的头节点指针 */
struct Node *deleteHead(struct Node *head) {
  if (head == NULL)
    return NULL;

  struct Node *temp = head; /* 保存旧头节点 */
  head = head->next;        /* 头指针后移 */
  free(temp);               /* 释放旧头节点的内存 */
  return head;
}

/* 删除链表中第一个值为 target 的节点
   时间复杂度：O(n)，需要遍历查找目标节点 */
struct Node* deleteByValue(struct Node* head, int target) {
    if (head == NULL) return NULL;

    /* 特殊情况：目标值在头节点 */
    if (head->data == target) {
        struct Node* temp = head;
        head = head->next;
        free(temp);
        return head;
    }

    /* 遍历查找目标节点的前驱节点 */
    struct Node* current = head;
    while (current->next != NULL && current->next->data != target) {
        current = current->next;
    }

    /* 找到目标节点，进行删除 */
    if (current->next != NULL) {
        struct Node* temp = current->next;
        current->next = current->next->next;  /* 跳过目标节点 */
        free(temp);  /* 释放目标节点内存 */
    }
    return head;
}

int main(int argc, char const *argv[]) {
  struct Node *head = createList(5);
  traverse(head);

  head = insertAtHead(head, 10);
  traverse(head);
  head = insertAtTail(head, 5);
  traverse(head);
  insertAfter(head->next, 15);
  traverse(head);

  head=deleteHead(head);
  traverse(head);
  head = deleteByValue(head, 5);
  traverse(head);
  return 0;
}
