#include <stdio.h>
#include <stdlib.h>

int fact(int num) {
  printf("%d ", num); 
  return num > 1 ? num * fact(num - 1) : 1;
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
  printf("fact %d = %d\n", in, out);
 
  return 0;
}
