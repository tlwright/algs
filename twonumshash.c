#include <stdio.h>
#include <stdlib.h>

#define HASHSIZE 11
#define ARRAYSIZE 6

unsigned int kphash(unsigned int n) { return 31 * n % HASHSIZE; }

int main (int argc, char *argv[]) {
  int in, hashidx, diff, i = 0;
  int x[] = {3, 4, 5, 7, 50, 100}; /* sorted list */ 
  int hash[HASHSIZE] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 

  if (argc != 2) {
    printf("%s num\n", argv[0]);
    return 0;
  }
  /* generate hash index from x[i], set hash value to i */ 
  for (in = 0; in < ARRAYSIZE; in++) {
    hashidx = kphash(x[in]);
    printf("value = %d, hashidx = %d, hash = %d\n", x[in], hashidx, in);
    if (!hash[hashidx]) hash[hashidx] = in;
    else printf("collision detected\n");
  }
  in = atoi(argv[1]); /* get the sum */

  /* look for num - 1st value */
  diff = in - x[0];
  hashidx = kphash(diff);
  printf("idx 0: value = %d, hashidx = %d, hash = %d, ", 
	 diff, hashidx, hash[hashidx]);
  while (x[hash[hashidx]] != diff && i < ARRAYSIZE) {
    printf("%d + %d = %d: %d not found\n", x[i], diff, in, diff);
    diff = in - x[++i];
    hashidx = kphash(diff);
    printf("idx %d: value = %d, hashidx = %d, hash = %d, ", 
	   i, diff, hashidx, hash[hashidx]);
  }

  if (x[hash[hashidx]] == diff) 
    printf("%d + %d = %d\n", x[i], diff, in);
  else printf("no 2 numbers found whose sum = %d\n", in);
  return 0;
}
