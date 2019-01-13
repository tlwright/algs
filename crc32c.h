struct IPINFO            /* collision train of nodes terminated with a NULL */
{
  unsigned int next;     /* if hash collision, pointer to next node */
  unsigned int adr;      /* IP address */
  unsigned int spam_cnt; /* number of spams detected */
  unsigned int list_flg; /* rbl or qil list flags */
};

struct R_DB
{
  int act_buf;          /* flag to indicate which buffer is active on input */
  int buf_alloc;        /* sort buffer allocated */
    struct
    {
      unsigned int nodes;    /* count of nodes */
      unsigned int *seq;     /* pointer to sequence array */
      struct IPINFO *ipinfo; /* pointer to node array holding IP info */
    } ip_buf[2];
};

#define MAX_UNIQUE      0x180000
#define CRC32C_POLY 0x1EDC6F41
#define CRC32C(c,d) (c=(c>>8)^crc_c[(c^(d))&0xFF])

unsigned long  crc_c[256] =
  {
    0x00000000L, 0xF26B8303L, 0xE13B70F7L, 0x1350F3F4L,
    0xC79A971FL, 0x35F1141CL, 0x26A1E7E8L, 0xD4CA64EBL,
...
    0x34F4F86AL, 0xC69F7B69L, 0xD5CF889DL, 0x27A40B9EL,
    0x79B737BAL, 0x8BDCB4B9L, 0x988C474DL, 0x6AE7C44EL,
    0xBE2DA0A5L, 0x4C4623A6L, 0x5F16D052L, 0xAD7D5351L,
  };
