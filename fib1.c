#include <stdio.h>
#include <stdlib.h>

int fib(int n) {
  int i, previousFib = 0, currentFib = 1, newFib;

  printf("fib1 %d: 0 1", n);
  for (i = 1; i < n;  i++) {
    newFib = previousFib + currentFib;
    previousFib = currentFib;
    currentFib = newFib;
    printf(" %d", newFib);
  } 

  printf("\n");
  return newFib;
}

int main (int argc, char *argv[]) {
  int n, r;

  if (argc != 2) {
    printf("%s num\n", argv[0]);
    return 0;
  }

  n = atoi(argv[1]);
  if (n > 45) {
    printf("%s num too big\n", argv[1]);
    return 0;
  }

  r = fib(n);
  printf("fib1 %d = %d\n", n, r);

  return 0;
}
