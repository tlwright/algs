#include <stdio.h>
int heapSize = 10;

void print(int a[]) {
  int i;
  for (i = 0; i <= 9; i++) { printf("%d %s ", a[i] , "-"); }
  printf("\n");
}

int left(int i) { return (2 * i) + 1;}

int right(int i) { return (2 * i) + 2;}

void swap(int x[], int i, int j) {
  int t = x[i];
  x[i] = x[j];
  x[j] = t;
}

void heapify(int a[], int i) {
  int x;
  int l = left(i), great;
  int r = right(i);
  printf("a[] %p a[0] %d i %d\n", a, a[0], i);
  for (x = 0; x < i; x++) printf("%d ", a[x]);
  if (i) printf("\n");
  if ( (a[l] > a[i]) && (l < heapSize)) { great = l;
  }  else { great = i; }
  if ( (a[r] > a[great]) && (r < heapSize)) { great = r; }
  if (great != i) {
    swap(a, i, great);
    heapify(a, great);
  }
}

void BuildMaxHeap(int a[]) {
  int i;
  for ( i = (heapSize - 1) / 2; i >= 0; i--) {
    heapify(a, i);
    print(a);
  }
}

void HeapSort(int a[]) {
  int i;
  BuildMaxHeap(a);
  for ( i = heapSize; i > 0; i--) {
    swap(a, 0, heapSize - 1);
    heapSize--;
    heapify(a, 0);
  }
}

int main() {
  int arr[] = { 2, 9, 3, 6, 1, 4, 5, 7, 0, 8};
  HeapSort(arr);
  print(arr);
  return 0;
}
