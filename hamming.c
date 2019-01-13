#include <stdio.h>
#include <stdlib.h>
typedef unsigned long long uint64;
short int tableLookup[256];

int count0(uint64 num) {
  int ctr=0;
  for(; num != 0; num >>= 1) { if(num&1) { ctr++; } }
  return ctr;
}

int popcount_4(uint64 x) {
  uint64 count;
  for (count=0; x; count++) x &= x-1;
  return count;
}

int count(uint64 x) {
  int result = 0;
  while ( x != 0 ) {
    result += tableLookup[ (x & 0xFF) ];
    x >>= 8;
  }
  return result;
}

void inittbl(void) {
  int i;
  for(i = 0; i < 256; i++) tableLookup[i] = popcount_4(i);
}

int main(int argc, char *argv[]) {
  uint64 num;
  int cnt, cnt0, cnt4;
  if (argc < 2) {
    printf("%s num\n", argv[0]);
    return 0;
  }
  inittbl();
  num = strtoul(argv[1], NULL, 0); 
  cnt = count(num); 
  cnt0 = count0(num); 
  cnt4 = popcount_4(num); 
  printf("%d %d %d 1s in %s\n", cnt, cnt0, cnt4, argv[1]);
  return 0;
}
