#include <stdio.h>
#define __USE_GNU /* NOT _GNU_SOURCE! */
#include <search.h>
#include <stdlib.h> /* exit */
#include <string.h> /* memset */

char *data[] = { "alpha", "bravo", "charlie", "delta", /* 4 */
		 "echo", "foxtrot", "golf", "hotel", "india", "juliet", /* 6 */
		 "kilo", "lima", "mike", "november", "oscar", "papa", /* 6 */
		 "quebec", "romeo", "sierra", "tango", "uniform", /* 5 */
		 "victor", "whisky", "x-ray", "yankee", "zulu" /* 5 */
};

int main() {
  ENTRY e, *ep;
  int i, ret; /* hsearch_r return is int, not *int */
  struct hsearch_data tab;

  /* starting with small table, and letting it grow does not work */
  memset(&tab, 0, sizeof(tab));
  hcreate_r(30, &tab);
  for (i = 0; i < 24; i++) {
    e.key = data[i];
    /* data is just an integer, instead of a
       pointer to something */
    e.data = (char *)i;
    ret = hsearch_r(e, ENTER, &ep, &tab);
    /* there should be no failures */
    if (ep == NULL) {
      fprintf(stderr, "entry failed\n");
      exit(1);
    }
  }
  for (i = 22; i < 26; i++) {
    /* print two entries from the table, and
       show that two are not in the table */
    e.key = data[i];
    ret = hsearch_r(e, FIND, &ep, &tab);
    printf("%9.9s -> %9.9s:%d\n", e.key,
	   ep ? ep->key : "NULL",
	   ep ? (int)(ep->data) : 0);
  }
  return 0;
}
