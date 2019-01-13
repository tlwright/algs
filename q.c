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

void enqueue(int i, node **first, node **last) {
  /* add node to last element */
  node *n = (node *) malloc(sizeof(node));
  if (n == NULL) return; /* error */
  if (*first == NULL) { /* empty */
    *first = n;
  } else {
    node *p = *last;
    p->next = n;
  }
  *last = n;
  n->next = NULL;
  n->data = i;
  prt_node("e", n);
}
 
node * dequeue(node **first, node **last) /* remove first element */ {
  node *p = *first;
  if (*first == NULL) return NULL; /* empty */
  *first = p->next;
  if (*first == NULL) last = NULL;
  return p; 
}
 
void list_print(node **first) {
  node * n = *first;
  if (n == NULL) { printf("list is empty\n"); }
  while (n != NULL) {
    prt_node("l", n);
    n = n->next;
  }
}
 
int main(void) {
  node *first = NULL; /* pointer to first element in list */
  node *last = NULL; /* pointer to last element in list */
  node *p = NULL;
  int i;
  for (i = 1; i <= 4; i++) enqueue(i, &first, &last);
  list_print(&first);
  p = dequeue(&first, &last);
  do { prt_node("d", p); p = dequeue(&first, &last); } while (p);
  list_print(&first);
  return 0;
}
