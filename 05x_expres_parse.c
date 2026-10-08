#include <stdio.h>
#include <ctype.h>   /* isalnum 函数 */
#include <string.h>
#include "math.h"

#define MAX 100

char stack[MAX];
int top = -1;

void push(char c) { stack[++top] = c; }
char pop() { return (top == -1) ? -1 : stack[top--]; }

/* 返回运算符优先级：数字越大优先级越高 */
int precedence(char op) {
    if (op == '+' || op == '-') return 1;  /* 加减优先级最低 */
    if (op == '*' || op == '/') return 2;  /* 乘除优先级较高 */
    if (op == '^') return 3;               /* 幂运算优先级最高 */
    return 0;  /* 不是运算符 */
}

/* 中缀表达式转后缀表达式
   参数：infix 输入的中缀表达式字符串
          postfix 输出的后缀表达式缓冲区 */
void infixToPostfix(char* infix, char* postfix) {
    int i = 0, j = 0;
    char c;

    while ((c = infix[i++]) != '\0') {
        /* 操作数（字母或数字）：直接输出 */
        if (isalnum(c)) {
            postfix[j++] = c;
        }
        /* 左括号：直接压栈 */
        else if (c == '(') {
            push(c);
        }
        /* 右括号：弹出直到遇到左括号 */
        else if (c == ')') {
            while (top != -1 && stack[top] != '(') {
                postfix[j++] = pop();
            }
            pop();  /* 弹出左括号 '('，但不输出 */
        }
        /* 运算符：处理优先级 */
        else {
            while (top != -1 &&
                   precedence(stack[top]) >= precedence(c) &&
                   stack[top] != '(') {
                postfix[j++] = pop();
            }
            push(c);
        }
    }

    /* 将栈中剩余运算符全部弹出 */
    while (top != -1) {
        postfix[j++] = pop();
    }
    postfix[j] = '\0';  /* 字符串结尾 */
}


/* 计算后缀表达式的值
   参数：postfix 后缀表达式（操作数均为单个数字 0-9）
   返回值：表达式的计算结果 */
int evaluatePostfix(char* postfix) {
    int i = 0;
    char c;

    while ((c = postfix[i++]) != '\0') {
        /* 操作数：转换为数字后压栈 */
        if (isdigit(c)) {
            push(c - '0');  /* '3' 转为整数 3 */
        }
        /* 运算符：弹出两个操作数，计算后压回 */
        else {
            int b = pop();  /* 第二个操作数（右操作数） */
            int a = pop();  /* 第一个操作数（左操作数） */
            switch (c) {
                case '+': push(a + b); break;
                case '-': push(a - b); break;
                case '*': push(a * b); break;
                case '/': push(a / b); break;
                case '^': push(pow(a, b)); break;
            }
        }
    }
    return pop();  /* 栈中最后一个元素即为最终结果 */
}

int main() {
    char infix[] = "(5-3)*(6-1)^2";            /* 中缀表达式 */
    char postfix[MAX];
    infixToPostfix(infix, postfix);    /* 步骤 1：转为后缀 */

    printf("中缀: %s\n", infix);       /* 输出: 中缀: 5+3*2 */
    printf("后缀: %s\n", postfix);     /* 输出: 后缀: 532*+ */

    int result = evaluatePostfix(postfix);  /* 步骤 2：求值 */
    printf("结果: %s = %d\n", infix, result);
    /* 输出: 结果: 5+3*2 = 11 */
    return 0;
}
