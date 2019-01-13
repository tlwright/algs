#include <stdio.h>

int f(char *s) {  return (*s ? f(s + 1) + 1 : 0); }

int main(int argc, char *argv[])
{
  /* f("cisco"); */

  int r;
  if (argc != 2) {
    printf("%s string\n", argv[0]);
    return 0;
  }

  r = f(argv[1]);
  printf("f(%s) = %d\n", argv[1], r);
  return 0;
}
