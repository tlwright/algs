#include <stdio.h>
#include <stdlib.h>

typedef enum {false, true} bool;

bool isLittleEndian(){
  union {
    int theInteger;
    char singleByte;
  } endianTest;

  endianTest.theInteger = 1;
  return endianTest.singleByte;
}

int main (int argc, char *argv[]) {
  int rc;

  rc = isLittleEndian();
  printf("endian is %s\n", rc ? "little" : "big");
 
  return 0;
}
