#include <stdio.h>
#include <stdlib.h>

unsigned long fib2(unsigned int n, unsigned long prev, unsigned long cur) {
  printf("%ld ", cur);
  return n == 1 ? cur : fib2(n - 1, cur, prev + cur);
}

unsigned long fib(unsigned int n) {
  printf("0 ");
  return n == 0 ? 0 : fib2(n, 0, 1);
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
  myfib = fib(n);
  printf("fib2 %d = %ld\n", n, myfib);
  return 0;
}
