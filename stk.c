#include <stdio.h>    /* for printf */
#include <stdlib.h>   /* for malloc */
 
typedef struct node {
  int data;
  struct node *next; /* pointer to next element in list */
} node;

void prt_node(char * name, node * node) { 
  if (node) {
    printf("%s %d: %p %d n %p \n", name, node->data, 
	   node, node->data, node->next);
  } else printf("node is NULL\n");
}

void push(int i, node **first) {
  /* add node before first element */
  node *n = (node *) malloc(sizeof(node));
  if (n == NULL) return; /* error */
  n->next = *first;
  *first = n;
  n->data = i;
  prt_node("psh", n);
}
 
node * pop(node **first) /* remove first element */ {
  node *p = *first;
  if (*first == NULL) return NULL; /* empty */
  *first = p->next;
  return p; 
}
 
void list_print(node **first) {
  node * n = *first;
  if (n == NULL) { printf("list is empty\n"); }
  while (n != NULL) {
    prt_node("lst", n);
    n = n->next;
  }
}
 
int main(void) {
  node *first = NULL; /* pointer to first element in list */
  node *p = NULL;
  int i;
  for (i = 1; i <= 4; i++) push(i, &first);
  list_print(&first);
  p = pop(&first);
  do { prt_node("pop", p); p = pop(&first); } while (p);
  list_print(&first);
  return 0;
}
