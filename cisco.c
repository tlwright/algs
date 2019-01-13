#include <stdio.h>

int f(char *s)
{
  /* return (*s ? f(s + 1) + 1 : 0); */

  char *s1;
  int t, r; 
  if (*s) {
    s1 = s + 1;
    t = f(s1);
    r = t + 1;
    printf("*s = %c, *(s + 1) = %c, f(s + 1 ) = %d, f(s + 1) + 1 = %d\n", 
	   *s, *s1, t, r);
  } else {
    r =  0;
    printf("*s = 0\n");
  }
  return r;
}

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

/*
tlwright@bolt:/home/t/tlwright/public_html/src/algs>./cisco cis 
*s = 0
*s = s, *(s + 1) = , f(s + 1 ) = 0, f(s + 1) + 1 = 1
*s = i, *(s + 1) = s, f(s + 1 ) = 1, f(s + 1) + 1 = 2
*s = c, *(s + 1) = i, f(s + 1 ) = 2, f(s + 1) + 1 = 3
f(cis) = 3
tlwright@bolt:/home/t/tlwright/public_html/src/algs>
*/
