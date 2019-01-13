#include <stdio.h>

int f(char *s) { int i = 0; for (; *s; s++, i++); return i; } 

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
