#include <stdio.h>
#include <stdlib.h>

unsigned long fib(unsigned int n) {
  printf(" %d", n);
  if (n == 0 || n == 1) {
      return n;
  } else {
    return fib(n - 1) + fib(n - 2);
  }
}

int main (int argc, char *argv[]) {
  int n;
  unsigned long myfib;

  if (argc != 2) {
    printf("%s num\n", argv[0]);
    return 0;
  }

  n = atoi(argv[1]);
  if (n > 45) {
    printf("%s num too big\n", argv[1]);
    return 0;
  }
  printf("fib3 %d: 0", n);
  myfib = fib(n);
  printf("\n");
  printf("fib3 %d = %ld\n", n, myfib);
  return 0;
}
