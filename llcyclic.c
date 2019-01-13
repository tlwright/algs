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

/* Takes a pointer to the head of a linked list and determines if
 * the list ends in a cycle or is NULL terminated  */
bool determineTermination( Node *head ){
  Node *fast, *slow;

  if (!head) return false;
  slow = head;
  fast = head->next;
  while( true ){
    if( !fast || !fast->next ) return false;
    else if( fast == slow || fast->next == slow ) return true;
    else {
      slow = slow->next;
      fast = fast->next->next;
    }
  }
}
  
int main(void) {
  Node *n = NULL, *third, *last;
  bool rc;
  
  last = list_add(&n, 0); /* list: 0 */
  list_add(&n, 1); /* list: 1 0 */
  third = list_add(&n, 2); /* list: 2 1 0 */
  list_add(&n, 3); /* list: 3 2 1 0 */
  list_add(&n, 4); /* list: 4 3 2 1 0 */
 
  rc = determineTermination(n);
  printf("list is %s\n", rc ? "cyclic" : "terminated");

  last->next = third;
  rc = determineTermination(n);
  printf("list is %s\n", rc ? "cyclic" : "terminated");

  return 0;
}
