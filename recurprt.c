#include <stdio.h>

void prt(char * s) {
  if (*s) {
    putchar(*s);
    prt(s+1);
  }
}

void revprt(char * s) {
  if (*s) {
    revprt(s+1);
    putchar(*s);
  }
}

int main (int argc, char * argv[]) {
  if (argc < 2) return 0;
  prt(argv[1]);
  putchar('\n');
  revprt(argv[1]);
  putchar('\n');
  return 0;
}
