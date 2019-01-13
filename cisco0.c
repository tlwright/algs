#include <stdio.h>

int f(char *s)
{
  printf("*s = %c\n", *s);
  printf("*(s + 1) = %c\n", *(s + 1));
  printf("*(s + 1) + 1 = %c\n", *(s + 1 ) + 1);
  return (*s ? f(s + 1) + 1 : 0);
}

int main(int argc, char *argv[])
{
  int n = f("cisco");
  return 0;
}

/*
*s = c
*(s + 1) = i
*(s + 1) + 1 = j
*s = i
*(s + 1) = s
*(s + 1) + 1 = t
*s = s
*(s + 1) = c
*(s + 1) + 1 = d
*s = c
*(s + 1) = o
*(s + 1) + 1 = p
*s = o
*(s + 1) =
*(s + 1) + 1 = ?
*s =
*(s + 1) =
*(s + 1) + 1 = ?
*/

