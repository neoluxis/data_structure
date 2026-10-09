#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode TreeNode;
struct TreeNode {
  int data;
  struct TreeNode *left;
  struct TreeNode *right;
};

struct TreeNode *createNode(int value) {
  struct TreeNode *node = (struct TreeNode *)malloc(sizeof(struct TreeNode));
  node->data = value;
  node->left = NULL;
  node->right = NULL;
  return node;
}

/* 前序遍历：根 → 左 → 右 */
void preOrder(struct TreeNode *root) {
  if (root == NULL)
    return;
  printf("%d ", root->data); /* 先访问根 */
  preOrder(root->left);      /* 再遍历左子树 */
  preOrder(root->right);     /* 最后遍历右子树 */
}

/* 中序遍历：左 → 根 → 右 */
void inOrder(struct TreeNode *root) {
  if (root == NULL)
    return;
  inOrder(root->left);       /* 先遍历左子树 */
  printf("%d ", root->data); /* 再访问根 */
  inOrder(root->right);      /* 最后遍历右子树 */
}

/* 后序遍历：左 → 右 → 根 */
void postOrder(struct TreeNode *root) {
  if (root == NULL)
    return;
  postOrder(root->left);     /* 先遍历左子树 */
  postOrder(root->right);    /* 再遍历右子树 */
  printf("%d ", root->data); /* 最后访问根 */
}

int main() {
    /* 构建如下二叉树:
           1
          / \
         2   3
        / \
       4   5   */
    struct TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);

    printf("前序: "); preOrder(root);  printf("\n");  /* 1 2 4 5 3 */
    printf("中序: "); inOrder(root);   printf("\n");  /* 4 2 5 1 3 */
    printf("后序: "); postOrder(root); printf("\n");  /* 4 5 2 3 1 */
    return 0;
}
