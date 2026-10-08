#include <stdio.h>
#include <stdbool.h>

#define MAX 100

struct Queue {
    int items[MAX];
    int front;   /* 队首指针：指向第一个元素 */
    int rear;    /* 队尾指针：指向下一个待插入位置 */
};

void initQueue(struct Queue* q) {
    q->front = 0;
    q->rear = 0;
}

bool isEmpty(struct Queue* q) {
    return q->front == q->rear;
}

bool isFull(struct Queue* q) {
    return q->rear == MAX;
}

/* 入队：在队尾添加元素 */
void enqueue(struct Queue* q, int value) {
    if (isFull(q)) {
        printf("队列已满！\n");
        return;
    }
    q->items[q->rear++] = value;  /* 在 rear 处写入，然后 rear 后移 */
    printf("入队: %d\n", value);
}

/* 出队：从队首移除元素 */
int dequeue(struct Queue* q) {
    if (isEmpty(q)) {
        printf("队列为空！\n");
        return -1;
    }
    return q->items[q->front++];  /* 返回 front 处元素，然后 front 后移 */
}

int main() {
    struct Queue q;
    initQueue(&q);

    enqueue(&q, 10);  /* 入队: 10 */
    enqueue(&q, 20);  /* 入队: 20 */
    enqueue(&q, 30);  /* 入队: 30 */

    printf("出队: %d\n", dequeue(&q));  /* 输出: 出队: 10 (先进先出) */
    printf("出队: %d\n", dequeue(&q));  /* 输出: 出队: 20 */
    printf("出队: %d\n", dequeue(&q));  /* 输出: 出队: 30 */
    return 0;
}