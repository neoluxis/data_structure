#include "stdio.h"
#include "stdint.h"

void array1d(void) {
  int arr1[] = {0, 1, 2, 3, 4};
  printf("Elements in arr1: \r\n");
  for (int i = 0; i < 5; i++) {
    printf("%d ", arr1[i]);
  }
  printf("\r\n");
}

void arraymd(void) {
  int arr[4][4] = {
      {0, 1, 2, 3},
      {1, 2, 3, 4},
      {2, 3, 4, 5},
      {3, 4, 5, 6},
  };

  // traverse 2d array (matrix)
  printf("Elements in matrix: \r\n");
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      printf("%d ", arr[i][j]);
    }
    printf("\r\n");
  }

  // accessing a specific element in 2d array
  printf("Element at arr[2][3]: %d \r\n", arr[2][3]);
}


/* 遍历并打印数组所有元素
   时间复杂度：O(n)，n 为数组长度 */
void traverse(int arr[], int n) {
    printf("Traverse: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int insert(int arr[], int len, int pos, int value, int cap) {
  if (len >= cap) {
    puts("Array full!");
    return -1;
  }
  if (pos < 0 || pos > len) {
    puts("Invalid pos!");
    return -1;
  }
  for (int i = len; i>pos; i--){
    arr[i] = arr[i-1];
  }
  arr[pos] = value;
  return len+1;
}

int main(int argc, char const *argv[]) {
  array1d();
  arraymd();

  int arr1[] = {1,2,3,4};
  traverse(arr1, 4);


  
  return 0;
}
