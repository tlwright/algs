#include <stdio.h>    /* for printf */
#include <stdlib.h>   /* for malloc */

typedef enum  { false,  true } bool;

typedef struct node {
  int data;
  struct node *next; /* pointer to next element in list */
} Node;
 
 
Node *list_add(Node **p, int i) {
  Node *n = (Node *) malloc(sizeof(Node));
  if (n == NULL) return NULL;
 
  n->next = *p; /* the previous element (*p) now becomes the "next" element */
  *p = n;       /* add new empty element to the front (head) of the list */
  n->data = i;
 
  return *p;
}

Node *findMToLastElement( Node *head, int m ){
  Node *current, *mBehind;
  int i;

  if (!head) return NULL;
  /* Advance current m elements from beginning,
   * checking for the end of the list   */
  current = head;
  for( i = 0; i < m; i++ ) {
    if( current->next ) current = current->next;
    else return NULL;
  }
  /* Start mBehind at beginning and advance pointers
   * together until current hits last element
   */
  mBehind = head;
  while( current->next ){
    current = current->next;
    mBehind = mBehind->next;
  }
  /* mBehind now points to the element we were
   * searching for, so return it   */
  return mBehind;
}

void list_print(Node *n) {
  if (n == NULL) { printf("list is empty\n"); }
  while (n != NULL) {
      printf("print %p %p %d\n", n, n->next, n->data);
      n = n->next;
  }
}
  
int main(void) {
  Node *n = NULL, *m;
  
  list_add(&n, 0); /* list: 0 */
  list_add(&n, 1); /* list: 1 0 */
  list_add(&n, 2); /* list: 2 1 0 */
  list_add(&n, 3); /* list: 3 2 1 0 */
  list_add(&n, 4); /* list: 4 3 2 1 0 */
 
  list_print(n);

  m = findMToLastElement(n, 2);
  if (m) printf("2 to last is %d\n", m->data);
  else printf("2 to last is invalid\n");

  m = findMToLastElement(n, 5);
  if (m) printf("5 to last is %d\n", m->data);
  else printf("5 to last is invalid\n");

  return 0;
}
