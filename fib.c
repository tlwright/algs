#include <stdio.h>
#include <stdlib.h>

int fib(int n) {
  int prev = 0, cur = 1, new = 1;

  printf("0 ");
  for ( ; n;  n--) {
    printf("%d ", new);
    new = prev + cur;
    prev = cur;
    cur = new;
  } 
  return prev;
}

int main (int argc, char *argv[]) {
  int n, myfib;

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
  printf("fib %d = %d\n", n, myfib);
  return 0;
}
