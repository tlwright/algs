#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int n1, n2;

  if (argc != 3) {
    printf("%s 2 numbers\n", argv[0]);
    return 0;
  }

  n1 = strtol(argv[1], NULL, 0);
  n2 = strtol(argv[2], NULL, 0);

  printf("%10s %10s\n", argv[1], argv[2]);
  printf("0x%08x 0x%08x\n", n1, n2);
  printf("0x%08x ^= 0x%08x = ", n1, n2);
  n1 ^= n2;
  printf("0x%08x\n", n1);
  printf("0x%08x ^= 0x%08x = ", n2, n1);
  n2 ^= n1;
  printf("0x%08x\n", n2);
  printf("0x%08x ^= 0x%08x = ", n1, n2);
  n1 ^= n2;
  printf("0x%08x\n", n1);
  printf("0x%08x 0x%08x\n", n1, n2);
  return 0;
}
