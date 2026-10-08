#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* 链表节点 */
struct Node {
    int data;
    struct Node* next;
};

/* 入栈 (push)：以链表头作为栈顶，头插法
   时间复杂度：O(1) */
struct Node* push(struct Node* top, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = top;   /* 新节点指向原栈顶 */
    printf("入栈: %d\n", value);
    return newNode;          /* 新节点成为新栈顶 */
}

/* 出栈 (pop)：移除链表头节点
   时间复杂度：O(1) */
struct Node* pop(struct Node* top) {
    if (top == NULL) {
        printf("栈为空！\n");
        return NULL;
    }
    struct Node* temp = top;
    printf("出栈: %d\n", top->data);
    top = top->next;   /* 栈顶后移 */
    free(temp);         /* 释放旧栈顶 */
    return top;
}

/* 判空 */
bool isEmpty(struct Node* top) {
    return top == NULL;
}

int main() {
    struct Node* stackTop = NULL;  /* 初始时栈为空 */

    stackTop = push(stackTop, 100);  /* 入栈: 100 */
    stackTop = push(stackTop, 200);  /* 入栈: 200 */
    stackTop = push(stackTop, 300);  /* 入栈: 300 */

    printf("栈顶: %d\n", stackTop->data);  /* 输出: 栈顶: 300 */

    stackTop = pop(stackTop);  /* 出栈: 300 */
    stackTop = pop(stackTop);  /* 出栈: 200 */
    stackTop = pop(stackTop);  /* 出栈: 100 */

    if (isEmpty(stackTop)) {
        printf("栈已空\n");      /* 输出: 栈已空 */
    }
    return 0;
}