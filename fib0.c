#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
  int n, i, previousFib = 0, currentFib = 1, newFib;

  if (argc != 2) {
    printf("%s num\n", argv[0]);
    return 0;
  }

  n = atoi(argv[1]);
  if (n > 45) {
    printf("%s num too big\n", argv[1]);
    return 0;
  }

  printf("fib %d: 0 1", n);
  for (i = 0; i < n;  i++) {
    newFib = previousFib + currentFib;
    previousFib = currentFib;
    currentFib = newFib;
    printf(" %d", newFib);
  } 

  printf("\n");
  return 0;
}
