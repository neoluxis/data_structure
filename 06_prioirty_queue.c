#include <stdio.h>

#define MAX 100

/* 基于无序数组的优先队列（最大优先队列：值越大优先级越高） */
struct PriorityQueue {
    int items[MAX];
    int size;  /* 当前元素个数 */
};

void initPQ(struct PriorityQueue* pq) { pq->size = 0; }

/* 入队：直接添加到末尾，O(1) */
void enqueue(struct PriorityQueue* pq, int value) {
    if (pq->size >= MAX) return;
    pq->items[pq->size++] = value;
}

/* 出队：遍历查找最大值，O(n)
   找到后将最后一个元素移到删除位置，size 减 1 */
int dequeue(struct PriorityQueue* pq) {
    if (pq->size == 0) return -1;

    /* 查找最大值的索引 */
    int maxIdx = 0;
    for (int i = 1; i < pq->size; i++) {
        if (pq->items[i] > pq->items[maxIdx]) {
            maxIdx = i;
        }
    }
    int maxVal = pq->items[maxIdx];
    /* 将最后一个元素移到被删除位置（避免大量移动） */
    pq->items[maxIdx] = pq->items[--pq->size];
    return maxVal;
}

int main() {
    struct PriorityQueue pq;
    initPQ(&pq);

    enqueue(&pq, 5);
    enqueue(&pq, 9);
    enqueue(&pq, 3);
    enqueue(&pq, 7);

    printf("出队（优先级最高）: %d\n", dequeue(&pq));  /* 输出: 9 */
    printf("出队（优先级最高）: %d\n", dequeue(&pq));  /* 输出: 7 */
    printf("出队（优先级最高）: %d\n", dequeue(&pq));  /* 输出: 5 */
    printf("出队: %d\n", dequeue(&pq));                /* 输出: 3 */
    return 0;
}