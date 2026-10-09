#include <stdio.h>

#define MAX 100

/* 最大堆结构 */
struct MaxHeap {
    int arr[MAX];
    int size;  /* 当前元素个数 */
};

void initHeap(struct MaxHeap* h) { h->size = 0; }

void swap(int* a, int* b) { int t = *a; *a = *b; *b = t; }

/* 上浮 (Sift Up)：新插入元素从底部向上调整
   与父节点比较，若大于父节点则交换，直到满足堆序 */
void siftUp(struct MaxHeap* h, int idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (h->arr[idx] <= h->arr[parent]) break;
        swap(&h->arr[idx], &h->arr[parent]);
        idx = parent;
    }
}

/* 插入：先将元素放在末尾，再上浮调整 O(log n) */
void insert(struct MaxHeap* h, int value) {
    if (h->size >= MAX) return;
    h->arr[h->size] = value;
    siftUp(h, h->size);
    h->size++;
}

/* 下沉 (Sift Down)：从根向下调整
   与较大的子节点比较，若小于则交换，直到满足堆序 */
void siftDown(struct MaxHeap* h, int idx) {
    while (1) {
        int largest = idx;
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;

        if (left < h->size && h->arr[left] > h->arr[largest])
            largest = left;
        if (right < h->size && h->arr[right] > h->arr[largest])
            largest = right;

        if (largest == idx) break;
        swap(&h->arr[idx], &h->arr[largest]);
        idx = largest;
    }
}

/* 删除堆顶（最大值）：将末尾元素移到顶部，再下沉调整 O(log n) */
int extractMax(struct MaxHeap* h) {
    if (h->size == 0) return -1;
    int maxVal = h->arr[0];
    h->arr[0] = h->arr[--h->size];  /* 末尾元素移到顶部 */
    siftDown(h, 0);                 /* 下沉调整 */
    return maxVal;
}

int main() {
    struct MaxHeap h;
    initHeap(&h);

    int vals[] = {3, 10, 5, 8, 2, 15};
    for (int i = 0; i < 6; i++) insert(&h, vals[i]);

    printf("依次取出最大值: ");
    while (h.size > 0) {
        printf("%d ", extractMax(&h));
    }
    printf("\n");  /* 输出: 15 10 8 5 3 2 (降序) */
    return 0;
}