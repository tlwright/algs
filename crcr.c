#include <stdio.h>
#include <string.h>
#include "crctable.h"

#define INIT 0xffffffffL
#define INIT_REFLECTED 0xffffffffL
#define XOROT 0xffffffffL

unsigned long crc_normal ();
unsigned long crc_normal (blk_adr,blk_len)
     unsigned char *blk_adr;
     unsigned long  blk_len;
{
  unsigned long crc = INIT;
  while (blk_len--)
    crc = crctable[((crc>>24) ^ *blk_adr++) & 0xFFL] ^ (crc << 8);
  return crc ^ XOROT;
}

unsigned long crc_reflected ();
unsigned long crc_reflected (blk_adr,blk_len)
     unsigned char *blk_adr;
     unsigned long  blk_len;
{
  unsigned long crc = INIT_REFLECTED;
  while (blk_len--)
    crc = crctable[(crc ^ *blk_adr++) & 0xFFL] ^ (crc >> 8);
  return crc ^ XOROT;
}

/* try 123456789: should get crc of 0xcbf43926 */
int main(int argc, char * argv[]) {
  char *in = "123456789";
  unsigned long crc;

  crc = crc_reflected(in, strlen(in));
  printf("crc for %s is %x, expected cbf43926\n", in, crc); 
  return 0;
}
