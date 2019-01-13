#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 Try running with 5 3 7 2 4 6 8 1 9:
             5
           3   7
          2 4 6 8
         1       9

 create tree, traverse it depth-first using stack and iteration from stk.c. 
 should print 1 2 3 4 5 6 7 8 9
*/

typedef struct node {
  void * data;
  struct node * next; /* pointer to next element in list */
} node;
 
typedef struct bst_node {
  void * data;
  struct bst_node * left;
  struct bst_node * right;
} bst_node;

void prt_node(char * name,  bst_node* nodep) { 
  if (nodep) printf("%s %s: %p %s l %p r %p\n", name, (char *) nodep->data, 
		   nodep, (char *) nodep->data, nodep->left, nodep->right);
  else printf("%s nodep is NULL\n", name);
}

void prt_qnode(char * name, node * nodep) { 
  if (nodep) {
    prt_node(name, nodep->data);
  } else printf("qnode is NULL\n");
}

bst_node* new_node(void* data) {
  bst_node* result = malloc(sizeof( bst_node));
  result->data = data;
  result->left = result->right = NULL;
  prt_node("new   ", result);
  return result;
}

void free_node( bst_node* nodep) { 
  prt_node("free  ", nodep);
  free(nodep); 
}

/* 
   Returns negative (left<right), zero (left==right), or positive (left>right).
*/
typedef int comparator(void* left, void* right); /* see cmp */

bst_node** search( bst_node** root, comparator compare, void* data) {
   bst_node** nodep = root;
  while (*nodep != NULL) {
    int compare_result = compare(data, (*nodep)->data);
    prt_node("search", *nodep);
    if (compare_result < 0) nodep = &(*nodep)->left;
    else if (compare_result > 0) nodep = &(*nodep)->right;
    else break;
  }
  return nodep;
}

void traverse( bst_node* nodep) {
  if (nodep == NULL)  return;
  traverse(nodep->left);
  prt_node("traver", nodep);
  traverse(nodep->right);
}

void insert( bst_node** root, comparator compare, void* data) {
   bst_node** nodep = search(root, compare, data);
  if (*nodep == NULL) { *nodep = new_node(data); }
}

void delete( bst_node** nodep) {
   bst_node* old_node = *nodep;
  void *temp;
  prt_node("delete", *nodep);
  if ((*nodep)->left == NULL) {
    *nodep = (*nodep)->right;
    free_node(old_node);
  } else if ((*nodep)->right == NULL) {
    *nodep = (*nodep)->left;
    free_node(old_node);
  } else {
    /* delete node with two children */
     bst_node** pred = &(*nodep)->left;
    while ((*pred)->right != NULL) {
      pred = &(*pred)->right;
    }
    /* Swap values */
    temp = (*pred)->data;
    (*pred)->data = (*nodep)->data;
    (*nodep)->data = temp;
    delete(pred);
  }
}

int cmp(void *left, void *right) {
  return strcmp(left, right);
}

void push(void * i, node **first) {
  /* add node before first element */
  node *n = (node *) malloc(sizeof(node));
  if (n == NULL) return; /* error */
  n->next = *first;
  *first = n;
  n->data = i;
  prt_qnode("psh", n);
}
 
bst_node * pop(node ** first) /* remove first element */ {
  bst_node * b;
  node *p = *first;
  if (*first == NULL) return NULL; /* empty */
  *first = p->next;
  b = p->data;
  free (p);
  return b;
}

void dtraverse( bst_node* bnodep, node **first) {
  while (bnodep || *first) {
    if (bnodep) {
      push(bnodep, first); /* save this bst_node */
      bnodep = bnodep->left; /* follow lower side */
    } else {
      bnodep = pop(first); /* get next bst_node */
      prt_node("pop", bnodep); /* print details */
      printf("%s\n", (char *) bnodep->data); /* print just data */
      bnodep = bnodep->right; /* follow higher side */
    } /* else */
  } /* while */
}

int main (int argc, char *argv[]) {
  node * first = NULL; /* pointer to first element in list */
  int i;
  bst_node *r;

  if (argc < 8) {
    printf("%s 7 or more numbers\n", argv[0]);
    return 0;
  }
  r = new_node(argv[1]);
  for(i = 2; i < argc; i++) insert(&r, cmp, argv[i]);
  traverse(r);
  dtraverse(r, &first);
  return 0;
}
