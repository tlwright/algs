#include <stdio.h>
#include <stdlib.h>

void swap(int x[], int i, int j) {
  int t = x[i];
  x[i] = x[j];
  x[j] = t;
}

void qwiksort(int x[], int n) {
  int i, p, last;
  if (n <= 1) return;
  p = rand() % n;
  printf("x[] %p x[0] %d p %d n %d\n", x, x[0], p, n);
  for (i = 0; i < n; i++) printf("%d ", x[i]);
  printf("\n");
  swap(x, 0, p);
  last = 0;
  for (i = 1; i < n; i++) if (x[i] < x[0]) swap(x, ++last, i);
  swap(x, 0, last);
  qwiksort(x, last);
  qwiksort(x + last + 1, n - last - 1);
}

int main(int argc, char *argv[]) 
{
#define sz 15
  int a[sz] = { 2, 5, 8, 4, 3,  5, 7, 11, 15, 13,  18, 0, 14, 12, 17};  
  int i;
  for (i = 0; i < sz; i++) printf("%d ", a[i]);
  printf("\n");
  qwiksort(a, sz);
  for (i = 0; i < sz; i++) printf("%d ", a[i]);
  printf("\n");
  return 0;
}
