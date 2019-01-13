#ifndef CM_DONE
#define CM_DONE
/*
http://www.ross.net/crc/download/crc_v3.txt

Here is the specification for the CRC-32 algorithm which is reportedly
used in PKZip, AUTODIN II, Ethernet, and FDDI.

  Name   : "CRC-32"
  Width  : 32
  Poly   : 04C11DB7
  Init   : FFFFFFFF
  RefIn  : True
  RefOut : True
  XorOut : FFFFFFFF
  Check  : CBF43926
*/

/* Step 1: Declare a variable of type cm_t. Declare another variable         */
/*         (p_cm say) of type p_cm_t and initialize it to point to the first */
/*         variable (e.g. p_cm_t p_cm = &cm_t).                              */
/*                                                                           */
/* Step 2: Assign values to the parameter fields of the structure.           */
/*         If you don't know what to assign, see the document cited earlier. */
/*         For example:                                                      */
/*            p_cm->cm_width = 16;                                           */
/*            p_cm->cm_poly  = 0x8005L;                                      */
/*            p_cm->cm_init  = 0L;                                           */
/*            p_cm->cm_refin = TRUE;                                         */
/*            p_cm->cm_refot = TRUE;                                         */
/*            p_cm->cm_xorot = 0L;                                           */
/*         Note: Poly is specified without its top bit (18005 becomes 8005). */
/*         Note: Width is one bit less than the raw poly width.              */
/*                                                                           */
/* Step 3: Initialize the instance with a call cm_ini(p_cm);                 */
/*                                                                           */
/* Step 4: Process zero or more message bytes by placing zero or more        */
/*         successive calls to cm_nxt. Example: cm_nxt(p_cm,ch);             */
/*                                                                           */
/* Step 5: Extract the CRC value at any time by calling crc = cm_crc(p_cm);  */
/*         If the CRC is a 16-bit value, it will be in the bottom 16 bits.   */


typedef unsigned long   ulong;
typedef unsigned        bool;
typedef unsigned char * p_ubyte_;

#ifndef TRUE
#define FALSE 0
#define TRUE  1
#endif

/* Change to the second definition if you don't have prototypes. */
#define P_(A) A
/* #define P_(A) () */

/* Uncomment this definition if you don't have void. */
/* typedef int void; */


typedef struct
{
  int   cm_width;   /* Parameter: Width in bits [8,32].       */
  ulong cm_poly;    /* Parameter: The algorithm's polynomial. */
  ulong cm_init;    /* Parameter: Initial register value.     */
  bool  cm_refin;   /* Parameter: Reflect input bytes?        */
  bool  cm_refot;   /* Parameter: Reflect output CRC?         */
  ulong cm_xorot;   /* Parameter: XOR this to output CRC.     */

  ulong cm_reg;     /* Context: Context during execution.     */
} cm_t;
typedef cm_t *p_cm_t;

/*****************************************************************************/

/* Functions That Implement The Model */
/* ---------------------------------- */
/* The following functions animate the cm_t abstraction. */

void cm_ini P_((p_cm_t p_cm));
/* Initializes the argument CRC model instance.          */
/* All parameter fields must be set before calling this. */

void cm_nxt P_((p_cm_t p_cm,int ch));
/* Processes a single message byte [0,255]. */

void cm_blk P_((p_cm_t p_cm,p_ubyte_ blk_adr,ulong blk_len));
/* Processes a block of message bytes. */

ulong cm_crc P_((p_cm_t p_cm));
/* Returns the CRC value for the message bytes processed so far. */

/*****************************************************************************/

/* Functions For Table Calculation */
/* ------------------------------- */
/* The following function can be used to calculate a CRC lookup table.       */
/* It can also be used at run-time to create or check static tables.         */

ulong cm_tab P_((p_cm_t p_cm,int index));
/* Returns the i'th entry for the lookup table for the specified algorithm.  */
/* The function examines the fields cm_width, cm_poly, cm_refin, and the     */
/* argument table index in the range [0,255] and returns the table entry in  */
/* the bottom cm_width bytes of the return value.                            */

/*****************************************************************************/

/* End of the header file idempotence #ifndef */
#endif
