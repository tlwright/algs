#include <stdio.h>    /* for printf */
#include <stdlib.h>   /* for malloc */
 
typedef struct node {
  int data;
  struct node *next; /* pointer to next element in list */
} LLIST;
 
void prt_node(char * name, LLIST * node) { 
  printf("%s %d: %p %d n %p \n", name, node->data, 
	 node, node->data, node->next);
}

LLIST *list_add(LLIST **p, int i) {
  LLIST *n = (LLIST *) malloc(sizeof(LLIST));
  if (n == NULL) return NULL;
   n->next = *p; /* the previous element (*p) now becomes the "next" element */
  *p = n;       /* add new empty element to the front (head) of the list */
  n->data = i;
  prt_node("add   ", n);
  return *p;
}
 
void list_remove(LLIST **p) /* remove head */ {
  if (*p != NULL)    {
    LLIST *n = *p;
    prt_node("remove", *p);
    *p = (*p)->next;
    free(n);
  }
}
 
void node_remove(LLIST *p) /* remove node */ {
  if (p && p->next)    {
    /* copy data from next node, remove next node */ 
    LLIST *n = p->next;
    prt_node("node remove", p);
    p->next = n->next;
    p->data = n->data;
    free(n);
  }
}
 
LLIST **list_search(LLIST **n, int i) {
  while (*n != NULL) {
    prt_node("search", *n);
    if ((*n)->data == i) { return n; }
    n = &(*n)->next;
  }
  return NULL;
}
 
void list_print(LLIST *n) {
  if (n == NULL) { printf("list is empty\n"); }
  while (n != NULL) {
    prt_node("list  ", n);
    n = n->next;
  }
}
 
int main(void) {
  LLIST *n = NULL, *p = NULL, *d = NULL;

  list_add(&n, 0); /* list: 0 */
  list_add(&n, 1); /* list: 1 0 */
  list_add(&n, 2); /* list: 2 1 0 */
  list_add(&n, 3); /* list: 3 2 1 0 */
  list_add(&n, 4); /* list: 4 3 2 1 0 */
  list_print(n);

  list_remove(&n);                 /* remove first (4) */
  list_print(n);
  list_remove(&n->next);           /* remove new second (2) */
  list_print(n);
  list_remove(list_search(&n, 1)); /* remove cell containing 1 (first) */
  list_print(n);
  list_remove(&n->next);           /* remove second to last node (0) */
  list_print(n);
  list_remove(&n);                 /* remove last (3) */
  list_print(n);

  p = list_add(&n, 0); /* list: 0 */
  p = list_add(&p->next, 1); /* list: 1 */
  d = p = list_add(&p->next, 2); /* list: 2 */
  p = list_add(&p->next, 3); /* list: 3 */
  p = list_add(&p->next, 4); /* list: 4 */
  list_print(n);
  node_remove(d);
  list_print(n);
  return 0;
}
