int i, act;
unsigned int hash, info_curr, info_prior, vec;

act = t_db->act_buf;
/* #define CRC32C(c, d) (c = (c >> 8) ^ crc_c[(c ^ (d)) & 0xFF]) */
for (i = 0, hash = ~0; i < 4; i++) {
  CRC32C(hash, ((ip_adr >> (i << 3)) & 0xFF));
  /* i << 3: 0 << 3 = 0, 1 << 3 = 8, 2 << 3 = 16, 3 << 3 = 24 */
/*hash = (hash >> 8) ^ crc_c[(hash ^ ((ip_adr >> (i << 3)) & 0xFF)) & 0xFF]*/
}
vec = hash % MAX_UNIQUE;

/* is the hash point used */
if ((info_curr = t_db->ip_buf[act].seq[vec]))  {
  while (info_curr) {
    if (t_db->ip_buf[act].ipinfo[info_curr].adr == ip_adr) break;
    info_prior = info_curr;
    info_curr = t_db->ip_buf[act].ipinfo[info_prior].next;
  }
  if (info_curr) { /* found prior entry */ 
    t_db->ip_buf[act].ipinfo[info_curr].spam_cnt += spams;
    
    if (t_db->ip_buf[act].ipinfo[info_curr].spam_cnt & 0xFFFF0000) {
      t_db->ip_buf[act].ipinfo[info_curr].spam_cnt = 0xFFFF;
    }
    t_db->ip_buf[act].ipinfo[info_curr].list_flg |= ip_flag;
  } else { /* add entry to collision train */
    info_curr = t_db->ip_buf[act].nodes++;
    t_db->ip_buf[act].ipinfo[info_curr].next = 0; /* should not be needed */
    t_db->ip_buf[act].ipinfo[info_curr].adr = ip_adr; /* setting the address */
    t_db->ip_buf[act].ipinfo[info_curr].spam_cnt = spams; /* set spam count */
    t_db->ip_buf[act].ipinfo[info_curr].list_flg = ip_flag;
    t_db->ip_buf[act].ipinfo[info_prior].next = info_curr;
  }
} else { /* pull next node */
  t_db->ip_buf[act].seq[vec] = info_curr = t_db->ip_buf[act].nodes++;    
  t_db->ip_buf[act].ipinfo[info_curr].next = 0; /* should not be needed */
  t_db->ip_buf[act].ipinfo[info_curr].adr = ip_adr; /* setting the address */
  t_db->ip_buf[act].ipinfo[info_curr].spam_cnt = spams; /* set spam count */
  t_db->ip_buf[act].ipinfo[info_curr].list_flg = ip_flag;
}

if(t_db->ip_buf[act].nodes >= MAX_UNIQUE) {
  /* char err_muo[] = "ERR: Too many unique IP addresses %d.\n"; */
  (void) fprintf(stderr, err_muo, t_db->ip_buf[act].nodes);
  t_dat->ret_val |= 4;
}
