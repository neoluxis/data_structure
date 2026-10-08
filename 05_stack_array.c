#include <stdio.h>
#include <stdbool.h>  /* bool 类型 */

#define MAX_SIZE 100   /* 栈的最大容量 */

/* 栈结构体：包含数据数组和栈顶指针 */
struct Stack {
    int items[MAX_SIZE];  /* 存储栈元素的数组 */
    int top;              /* 栈顶指针，-1 表示栈空 */
};

/* 初始化栈：将 top 置为 -1 */
void initStack(struct Stack* s) {
    s->top = -1;
}

/* 判空：top 为 -1 时栈为空 */
bool isEmpty(struct Stack* s) {
    return s->top == -1;
}

/* 判满：top 到达容量上限 -1 时栈满 */
bool isFull(struct Stack* s) {
    return s->top == MAX_SIZE - 1;
}

/* 入栈 (push)：将元素放入栈顶
   先移动 top，再写入数据 */
void push(struct Stack* s, int value) {
    if (isFull(s)) {
        printf("栈已满，无法入栈！\n");
        return;
    }
    s->items[++s->top] = value;  /* top 先加 1，再赋值 */
    printf("入栈: %d\n", value);
}

/* 出栈 (pop)：移除并返回栈顶元素
   先取出数据，再移动 top */
int pop(struct Stack* s) {
    if (isEmpty(s)) {
        printf("栈为空，无法出栈！\n");
        return -1;  /* 返回特殊值表示错误 */
    }
    return s->items[s->top--];  /* 先返回值，top 再减 1 */
}

/* 查看栈顶 (peek)：不弹出，只查看 */
int peek(struct Stack* s) {
    if (isEmpty(s)) {
        printf("栈为空！\n");
        return -1;
    }
    return s->items[s->top];
}

int main() {
    struct Stack s;
    initStack(&s);

    push(&s, 10);  /* 入栈: 10 */
    push(&s, 20);  /* 入栈: 20 */
    push(&s, 30);  /* 入栈: 30 */

    printf("栈顶元素: %d\n", peek(&s));  /* 输出: 栈顶元素: 30 */

    printf("出栈: %d\n", pop(&s));        /* 输出: 出栈: 30 (后进先出) */
    printf("出栈: %d\n", pop(&s));        /* 输出: 出栈: 20 */
    printf("出栈: %d\n", pop(&s));        /* 输出: 出栈: 10 */

    if (isEmpty(&s)) {
        printf("栈已空\n");                /* 输出: 栈已空 */
    }
    return 0;
}