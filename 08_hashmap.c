#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10  /* 哈希表容量 */

/* 哈希表节点 */
struct HashNode {
    int key;
    int value;
    struct HashNode* next;  /* 指向同一槽位的下一个节点 */
};

/* 哈希函数：简单的取模法 */
int hashFunc(int key) {
    return key % TABLE_SIZE;
}

/* 插入键值对（链地址法）
   时间复杂度：O(1) 平均，O(n) 最坏（所有键映射到同一槽） */
void insert(struct HashNode* table[], int key, int value) {
    int index = hashFunc(key);
    struct HashNode* newNode = (struct HashNode*)malloc(sizeof(struct HashNode));
    newNode->key = key;
    newNode->value = value;
    newNode->next = table[index];  /* 头插法 */
    table[index] = newNode;
}

/* 查找：根据键获取值
   先计算哈希值定位槽位，再遍历链表查找匹配的键 */
int search(struct HashNode* table[], int key) {
    int index = hashFunc(key);
    struct HashNode* cur = table[index];
    while (cur != NULL) {
        if (cur->key == key) {
            return cur->value;  /* 找到 */
        }
        cur = cur->next;
    }
    return -1;  /* 未找到 */
}

int main() {
    struct HashNode* table[TABLE_SIZE] = {NULL};  /* 初始化所有槽为空 */

    insert(table, 1, 100);   /* key=1, value=100, index=1 */
    insert(table, 2, 200);   /* key=2, value=200, index=2 */
    insert(table, 11, 300);  /* key=11, value=300, index=1 — 与 key=1 冲突！ */

    printf("key=1 → %d\n", search(table, 1));   /* 输出: 100 */
    printf("key=2 → %d\n", search(table, 2));   /* 输出: 200 */
    printf("key=11 → %d\n", search(table, 11)); /* 输出: 300 (链地址法正确处理了冲突) */
    printf("key=99 → %d\n", search(table, 99)); /* 输出: -1 (未找到) */
    return 0;
}