#include <stdio.h>
#include <stdlib.h>

int fact(int n) {
  int val = 1;

  /* n = 0 or 1 falls through */ 
  for( ; n > 0; n-- ) {
    printf("%d ", n); 
    val *= n;
  }
  return val;
}

int main (int argc, char *argv[]) {
  int in, out;

  if (argc != 2) {
    printf("%s num\n", argv[0]);
    return 0;
  }

  in = atoi(argv[1]);

  if (in > 10) {
    printf("%s num too big\n", argv[1]);
    return 0;
  }

  out = fact(in);
  printf("fact2 %d = %d\n", in, out);
 
  return 0;
}
