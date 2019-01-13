#include <stdio.h>  /* printf */
#include <string.h> /* memset */
#include <stdlib.h> /* malloc */

#define SIZE 11
#define ARRAYSIZE 6
enum {NOCREATE, CREATE} create;  

typedef struct node {
  int val;
  struct node *next;
} node;

node * tbl[SIZE] = {'\0'};

int myhash(int word) {
  int val = 0, i;
  char * p = (char *) &word;

  for (i = 0; i < sizeof(int); i++) {
    val = *p + val * 31;
  }
  return val % SIZE;
}

node * lookup(int val, int create) {
  int h;
  node * sym;

  h = myhash(val);
  for( sym = tbl[h]; sym; sym = sym->next) {
    if (val == sym->val) {
      if (create) {
	printf("found %d\n", sym->val); 
      }
      return sym;
    } else if (tbl[h]) printf("handling collision for tbl[%d]\n", h);
  }

  if (create) {
    sym = (node *) malloc(sizeof(node));
    sym->val = val;
    sym->next = tbl[h];
    tbl[h] = sym;
  }
  return sym;
}

int main (int argc, char *argv[]) {
  int in, diff, i = 0;
  int x[] = {3, 4, 5, 7, 50, 100}; /* sorted list */ 
  node * mynode;

  if (argc != 2) {
    printf("%s num\n", argv[0]);
    return 0;
  }
  memset(tbl, 0, sizeof(tbl));

  /* generate hash index from x[i] */ 
  for (in = 0; in < ARRAYSIZE; in++) {
    mynode = lookup(x[in], CREATE);
    printf("%d ", x[in]);
  }
  printf("\n");

  in = atoi(argv[1]); /* get the sum */

  /* look for num - 1st value */
  diff = in - x[0];
  mynode = lookup(diff, NOCREATE);
  while (i < ARRAYSIZE) {
    if (!mynode) {
      printf("%d + %d = %d: %d not found\n", x[i], diff, in, diff);
      diff = in - x[++i];
      mynode = lookup(diff, NOCREATE);
    } else break;
  }

  if (mynode && mynode->val == diff) 
    printf("%d + %d = %d\n", x[i], diff, in);
  else printf("no 2 numbers found whose sum = %d\n", in);
  return 0;
}
