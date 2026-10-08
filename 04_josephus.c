#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;           /* 人的编号 */
    struct Node* next;
};

/* 约瑟夫环求解
   参数：n 总人数, m 每次数到 m 的人出圈
   使用循环链表模拟整个过程 */
void josephus(int n, int m) {
    if (n <= 0) return;

    /* 步骤 1：创建包含 n 个人的循环链表（编号 1~n） */
    struct Node* head = (struct Node*)malloc(sizeof(struct Node));
    head->data = 1;
    head->next = head;  /* 只有一个人时，自环 */

    struct Node* tail = head;
    for (int i = 2; i <= n; i++) {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = i;
        newNode->next = head;   /* 新节点的 next 始终指向头 */
        tail->next = newNode;   /* 前一个节点的 next 指向新节点 */
        tail = newNode;          /* tail 后移 */
    }

    /* 步骤 2：模拟淘汰过程 */
    struct Node* cur = head;
    struct Node* prev = tail;  /* prev 指向 cur 的前驱，初始为尾节点 */

    printf("约瑟夫环 (n=%d, m=%d) 淘汰顺序: ", n, m);

    while (cur->next != cur) {  /* 只剩一个节点时（自环）结束 */
        /* 报数：数 m-1 次，让 prev 和 cur 同时前进 */
        for (int count = 1; count < m; count++) {
            prev = cur;
            cur = cur->next;
        }
        /* 数到 m，cur 被淘汰 */
        printf("%d ", cur->data);
        prev->next = cur->next; /* 跳过 cur */
        free(cur);               /* 释放被淘汰的节点 */
        cur = prev->next;        /* 从下一个人重新开始报数 */
    }

    printf("=> 最后幸存者: %d\n", cur->data);  /* 输出最后一个人 */
    free(cur);
}

int main() {
    josephus(7, 3);
    /* 输出: 约瑟夫环 (n=7, m=3) 淘汰顺序: 3 6 2 7 5 1 => 最后幸存者: 4 */
    return 0;
}