#include <stdio.h>
#include <string.h>
#include "crc.h"

/*****************************************************************************/

/* The following definitions make the code more readable. */

#define BITMASK(X) (1L << (X))
#define MASK32 0xFFFFFFFFL
#define LOCAL static

/*****************************************************************************/

LOCAL ulong reflect P_((ulong v,int b));
LOCAL ulong reflect (v,b)
     /* Returns the value v with the bottom b [0,32] bits reflected. */
     /* Example: reflect(0x3e23L,3) == 0x3e26                        */
     ulong v;
     int   b;
{
  ulong t = v;
  int i;
  for (i=0; i<b; i++)
    {
      if (t & 1L)
	v|=  BITMASK((b-1)-i);
      else
	v&= ~BITMASK((b-1)-i);
      t>>=1;
    }
  return v;
}

/*****************************************************************************/

LOCAL ulong widmask P_((p_cm_t));
LOCAL ulong widmask (p_cm)
     /* Returns a longword whose value is (2^p_cm->cm_width)-1.     */
     /* The trick is to do this portably (e.g. without doing <<32). */
     p_cm_t p_cm;
{
  return (((1L<<(p_cm->cm_width-1))-1L)<<1)|1L;
}

/*****************************************************************************/

void cm_ini (p_cm)
     p_cm_t p_cm;
{
  p_cm->cm_reg = p_cm->cm_init;
}
void cm_nxt (p_cm,ch)
     p_cm_t p_cm;
     int    ch;
{
  int   i;
  ulong uch  = (ulong) ch;
  ulong topbit = BITMASK(p_cm->cm_width-1);

  if (p_cm->cm_refin) uch = reflect(uch,8);
  p_cm->cm_reg ^= (uch << (p_cm->cm_width-8));
  for (i=0; i<8; i++)
    {
      if (p_cm->cm_reg & topbit)
	p_cm->cm_reg = (p_cm->cm_reg << 1) ^ p_cm->cm_poly;
      else
	p_cm->cm_reg <<= 1;
      p_cm->cm_reg &= widmask(p_cm);
    }
}

/*****************************************************************************/

void cm_blk (p_cm,blk_adr,blk_len)
     p_cm_t   p_cm;
     p_ubyte_ blk_adr;
     ulong    blk_len;
{
  while (blk_len--) cm_nxt(p_cm,*blk_adr++);
}

/*****************************************************************************/

ulong cm_crc (p_cm)
     p_cm_t p_cm;
{
  if (p_cm->cm_refot)
    return p_cm->cm_xorot ^ reflect(p_cm->cm_reg,p_cm->cm_width);
  else
    return p_cm->cm_xorot ^ p_cm->cm_reg;
}
/*****************************************************************************/

/* try 123456789: should get crc of 0xcbf43926 */
int main(int argc, char * argv[]) {
  char *in = "123456789";
  ulong crc;

  cm_t cm;
  p_cm_t p_cm = &cm;
  p_cm->cm_width = 32;     
  p_cm->cm_poly  = 0x04c11db7L;
  p_cm->cm_init  = 0xffffffffL;     
  p_cm->cm_refin = TRUE;   
  p_cm->cm_refot = TRUE;   
  p_cm->cm_xorot = 0xffffffffL;     
  
  cm_ini(p_cm);
  cm_blk(p_cm, in, strlen(in));
  crc = cm_crc(p_cm);
  printf("crc for %s is %x, expected cbf43926\n", in, crc); 
  return 0;
}
