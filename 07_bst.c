#include "stdio.h"
#include "stdlib.h"

typedef struct TreeNode TreeNode;
struct TreeNode {
    int data;
    TreeNode *left;
    TreeNode *right;
};

/* BST 插入：根据值的大小递归定位到合适位置
   时间复杂度：O(h)，h 为树高，平衡时为 O(log n) */
struct TreeNode* insert(struct TreeNode* root, int value) {
    if (root == NULL) {
        struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        node->data = value;
        node->left = node->right = NULL;
        return node;
    }
    if (value < root->data) {
        root->left = insert(root->left, value);   /* 小于根，插入左子树 */
    } else if (value > root->data) {
        root->right = insert(root->right, value); /* 大于根，插入右子树 */
    }
    return root;  /* 相等则忽略（BST 通常不存重复值） */
}

/* BST 查找：与当前节点比较，决定向左或向右搜索 */
struct TreeNode* search(struct TreeNode* root, int target) {
    if (root == NULL || root->data == target) {
        return root;  /* 找到目标或到达叶节点 */
    }
    if (target < root->data) {
        return search(root->left, target);   /* 目标更小，去左子树找 */
    }
    return search(root->right, target);       /* 目标更大，去右子树找 */
}

/* 中序遍历（验证 BST 的有序性） */
void inOrder(struct TreeNode* root) {
    if (root == NULL) return;
    inOrder(root->left);
    printf("%d ", root->data);
    inOrder(root->right);
}

int main() {
    struct TreeNode* root = NULL;
    int values[] = {50, 30, 70, 20, 40, 60, 80};

    /* 依次插入构建 BST */
    for (int i = 0; i < 7; i++) {
        root = insert(root, values[i]);
    }

    printf("BST 中序遍历（升序）: ");
    inOrder(root);  /* 输出: 20 30 40 50 60 70 80 */
    printf("\n");

    /* 查找测试 */
    int target = 40;
    struct TreeNode* found = search(root, target);
    printf("%d %s\n", target, found ? "找到了！" : "未找到");
    /* 输出: 40 找到了！ */
    return 0;
}
