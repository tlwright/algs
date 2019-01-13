#include <stdio.h>
#include <stdlib.h>

void swap(int x[], int i) {
  int t = x[i];
  printf("swapping x[%d] = %d with x[%d] = %d\n", i, x[i], i + 1, x[i + 1]);
  x[i] = x[i + 1];
  x[i + 1] = t;
}

void insort(int x[], int n) {
  int i, j;
  for (i = 0; i < n; i++) {
    for (j = i - 1; j >= 0; j--) {
      printf("testing x[%d] = %d with x[%d] = %d\n", j, x[j], j + 1, x[j + 1]);
      if (x[j] < x[j + 1]) break;
      swap(x, j);
    }
  }
}

int main(int argc, char *argv[]) 
{
#define sz 15
  int a[sz] = { 2, 5, 8, 4, 3,  5, 7, 11, 15, 13,  18, 0, 14, 12, 17};  
  int i;
  for (i = 0; i < sz; i++) printf("%d ", a[i]);
  printf("\n");
  insort(a, sz);
  for (i = 0; i < sz; i++) printf("%d ", a[i]);
  printf("\n");
  return 0;
}
