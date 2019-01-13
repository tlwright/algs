#include <stdio.h>
#include <stdlib.h>
#include "crc.h"

#define TB_FILE   "crct.h"
#define TB_WIDTH  4
/* #define TB_POLY   0x04C11DB7L */
#define TB_POLY   0x1EDC6F41
#define TB_REVER  TRUE

/*****************************************************************************/

/* Miscellaneous definitions. */

#define LOCAL static
FILE *outfile;
#define WR(X) fprintf(outfile,(X))
#define WP(X,Y) fprintf(outfile,(X),(Y))

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

ulong cm_tab (p_cm,index)
     p_cm_t p_cm;
     int    index;
{
  int   i;
  ulong r;
  ulong topbit = BITMASK(p_cm->cm_width-1);
  ulong inbyte = (ulong) index;

  if (p_cm->cm_refin) inbyte = reflect(inbyte,8);
  r = inbyte << (p_cm->cm_width-8);
  for (i=0; i<8; i++)
    if (r & topbit)
      r = (r << 1) ^ p_cm->cm_poly;
  else
    r<<=1;
  if (p_cm->cm_refin) r = reflect(r,p_cm->cm_width);
  return r & widmask(p_cm);
}

/* If mess is non-empty, write it out and abort. Otherwise, check the error  */
/* status of outfile and abort if an error has occurred.                     */
LOCAL void chk_err P_((char *));
LOCAL void chk_err (mess)
     char *mess;
{
  if (mess[0] != 0   ) {printf("%s\n",mess); exit(EXIT_FAILURE);}
  if (ferror(outfile)) {perror("chk_err");   exit(EXIT_FAILURE);}
}

/*****************************************************************************/

LOCAL void chkparam P_((void));
LOCAL void chkparam ()
{
  if ((TB_WIDTH != 2) && (TB_WIDTH != 4))
    chk_err("chkparam: Width parameter is illegal.");
  if ((TB_WIDTH == 2) && (TB_POLY & 0xFFFF0000L))
    chk_err("chkparam: Poly parameter is too wide.");
  if ((TB_REVER != FALSE) && (TB_REVER != TRUE))
    chk_err("chkparam: Reverse parameter is not boolean.");
}
LOCAL void gentable P_((void));
LOCAL void gentable ()
{
  WR("/*****************************************************************/\n");
  WR("/*                                                               */\n");
  WR("/* CRC LOOKUP TABLE                                              */\n");
  WR("/* ================                                              */\n");
  WR("/*                                                               */\n");
  WP("/*    Width   : %1lu bytes.                                         */\n",
     (ulong) TB_WIDTH);
  if (TB_WIDTH == 2)
    WP("/*    Poly    : 0x%04lX                                           */\n",
       (ulong) TB_POLY);
  else
    WP("/*    Poly    : 0x%08lXL                                      */\n",
       (ulong) TB_POLY);
  if (TB_REVER)
    WR("/*    Reverse : TRUE.                                            */\n");
  else
    WR("/*    Reverse : FALSE.                                           */\n");
  WR("/*                                                               */\n");
  WR("/* For more information on the Rocksoft^tm Model CRC Algorithm,  */\n");
  WR("/* see the document titled \"A Painless Guide to CRC Error        */\n");
  WR("/* Detection Algorithms\" by Ross Williams                        */\n");
  WR("/* (ross@guest.adelaide.edu.au.). This document is likely to be  */\n");
  WR("/* in the FTP archive \"ftp.adelaide.edu.au/pub/rocksoft\".        */\n");
  WR("/*                                                               */\n");
  WR("/*****************************************************************/\n");
  WR("\n");
  switch (TB_WIDTH)
    {
    case 2: WR("unsigned short crctable[256] =\n{\n"); break;
    case 4: WR("unsigned long  crctable[256] =\n{\n"); break;
    default: chk_err("gentable: TB_WIDTH is invalid.");
    }
  chk_err("");

  {
    int i;
    cm_t cm;
    char *form    = (TB_WIDTH==2) ? "0x%04lX" : "0x%08lXL";
    int   perline = (TB_WIDTH==2) ? 8 : 4;

    cm.cm_width = TB_WIDTH*8;
    cm.cm_poly  = TB_POLY;
    cm.cm_refin = TB_REVER;

    for (i=0; i<256; i++)
      {
	WR(" ");
	WP(form,(ulong) cm_tab(&cm,i));
	if (i != 255) WR(",");
	if (((i+1) % perline) == 0) WR("\n");
	chk_err("");
      }
    WR("};\n");
    WR("\n");
    WR("/*****************************************************************/\n");
    WR("/*                   End of CRC Lookup Table                     */\n");
    WR("/*****************************************************************/\n");
    WR("");
    chk_err("");
  }
}

/******************************************************************************/

int main ()
{
  printf("\n");
  printf("Output file is \"%s\".\n",TB_FILE);
  chkparam();
  outfile = fopen(TB_FILE,"w"); chk_err("");
  gentable();
  if (fclose(outfile) != 0)
    chk_err("main: Couldn't close output file.");
  printf("\nSUCCESS: The table has been successfully written.\n");
  return 0;
}

