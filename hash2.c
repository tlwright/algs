/*
  write code to print just unique words...
  given ab cd ef ab cd, just print ab cd and ef
*/
 
#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc */
#include <string.h> /* strcmp */

#define SIZE 11
enum {NOCREATE, CREATE} create;  

/* from The Practice of Programming: Kerninghan and Pike */

typedef struct node {
  char *val;
  int count;
  struct node *next;
} node;

node * tbl[SIZE] = {'\0'};

int myhash(char * word) {
  int val = 0;
  
  for (; *word; word++) {
    val = *word + val * 31;
  }
  return val % SIZE;
}

node * lookup(char * val, int create) {
  int h;
  node * sym;

  h = myhash(val);
  for( sym = tbl[h]; sym; sym = sym->next) {
    if (strcmp(val, sym->val) == 0) {
      if (create) {
	printf("found %s, count = %d\n", sym->val, sym->count); 
	sym->count++;
      }
      return sym;
    } else if (tbl[h]) printf("handling collision for tbl[%d]\n", h);
  }

  if (create) {
    sym = (node *) malloc(sizeof(node));
    sym->val = val;
    sym->count = 1;
    sym->next = tbl[h];
    tbl[h] = sym;
  }
  return sym;
}

int main(int argc, char * argv[]) {
  int i;
  node * mynode;

  memset(tbl, 0, sizeof(tbl));
  printf("building hash tbl\n");
  for (i = 1; i < argc; i++) mynode = lookup(argv[i], CREATE);  
  printf("searching hash tbl\n");
  for (i = 1; i < argc; i++) {
    mynode = lookup(argv[i], NOCREATE);
    if (mynode->count == 1) 
      printf ("%s ", mynode->val);
  }
  printf("\n");
  return 0;
}
