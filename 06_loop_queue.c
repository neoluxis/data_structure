#include <stdio.h>
#include <stdbool.h>

#define MAX 5  /* 故意设置较小的容量，便于观察循环效果 */

struct CircularQueue {
    int items[MAX];
    int front;  /* 队首索引 */
    int rear;   /* 队尾索引（下一个插入位置）*/
};

void initQueue(struct CircularQueue* q) {
    q->front = 0;
    q->rear = 0;
}

/* 判空：front 和 rear 重合 */
bool isEmpty(struct CircularQueue* q) {
    return q->front == q->rear;
}

/* 判满：(rear + 1) % MAX == front
   注意：循环队列故意空一个位置，用于区分空和满 */
bool isFull(struct CircularQueue* q) {
    return (q->rear + 1) % MAX == q->front;
}

/* 入队：在 rear 处写入，然后 rear 循环后移 */
void enqueue(struct CircularQueue* q, int value) {
    if (isFull(q)) {
        printf("循环队列已满！\n");
        return;
    }
    q->items[q->rear] = value;
    q->rear = (q->rear + 1) % MAX;  /* 取模实现回绕 */
    printf("入队: %d (rear=%d)\n", value, q->rear);
}

/* 出队：返回 front 处元素，然后 front 循环后移 */
int dequeue(struct CircularQueue* q) {
    if (isEmpty(q)) {
        printf("循环队列为空！\n");
        return -1;
    }
    int value = q->items[q->front];
    q->front = (q->front + 1) % MAX;  /* 取模实现回绕 */
    return value;
}

int main() {
    struct CircularQueue q;
    initQueue(&q);

    enqueue(&q, 10);  /* 入队: 10 (rear=1) */
    enqueue(&q, 20);  /* 入队: 20 (rear=2) */
    enqueue(&q, 30);  /* 入队: 30 (rear=3) */
    enqueue(&q, 40);  /* 入队: 40 (rear=4) — 容量 5，最多存 4 个 */

    printf("出队: %d\n", dequeue(&q));  /* 出队: 10 (front=1) */
    printf("出队: %d\n", dequeue(&q));  /* 出队: 20 (front=2) */

    enqueue(&q, 50);  /* 入队: 50 (rear=0 — 回绕到开头！) */
    enqueue(&q, 60);  /* 入队: 60 (rear=1) */

    printf("剩余元素: ");
    while (!isEmpty(&q)) {
        printf("%d ", dequeue(&q));
    }
    printf("\n");  /* 输出: 剩余元素: 30 40 50 60 */
    return 0;
}