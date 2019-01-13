#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 Try running with 5 3 7 2 4 6 8 1 9:
             5
           3   7
          2 4 6 8
         1       9

 create tree, traverse it breadth-first using queue from q.c. 
 should print 5 3 7 2 4 6 8 1 9.
*/

typedef struct node {
  void * data;
  struct node * next; /* pointer to next element in list */
} DLLNODE;
 
DLLNODE * first = NULL; /* pointer to first element in list */
DLLNODE * last = NULL; /* pointer to last element in list */

struct bst_node {
  void * data;
  struct bst_node * left;
  struct bst_node * right;
};

void prt_node(char * name, struct bst_node* node) { 
  if (node) printf("%s %s: %p %s l %p r %p\n", name, (char *) node->data, 
		   node, (char *) node->data, node->left, node->right);
  else printf("%s node is NULL\n", name);
}

void prt_qnode(char * name, DLLNODE * node) { 
  if (node) {
    prt_node(name, node->data);
  } else printf("qnode is NULL\n");
}

struct bst_node* new_node(void* data) {
  struct bst_node* result = malloc(sizeof(struct bst_node));
  result->data = data;
  result->left = result->right = NULL;
  prt_node("new   ", result);
  return result;
}

void free_node(struct bst_node* node) { 
  prt_node("free  ", node);
  free(node); 
}

/* 
   Returns negative (left<right), zero (left==right), or positive (left>right).
*/
typedef int comparator(void* left, void* right);

struct bst_node** search(struct bst_node** root, comparator compare, void* data) {
  struct bst_node** node = root;
  while (*node != NULL) {
    int compare_result = compare(data, (*node)->data);
    prt_node("search", *node);
    if (compare_result < 0) node = &(*node)->left;
    else if (compare_result > 0) node = &(*node)->right;
    else break;
  }
  return node;
}

void  traverse(struct bst_node* node) {
  if (node == NULL)  return;
  traverse(node->left);
  prt_node("traver", node);
  traverse(node->right);
}

void insert(struct bst_node** root, comparator compare, void* data) {
  struct bst_node** node = search(root, compare, data);
  if (*node == NULL) { *node = new_node(data); }
}

void delete(struct bst_node** node) {
  struct bst_node* old_node = *node;
  void *temp;
  prt_node("delete", *node);
  if ((*node)->left == NULL) {
    *node = (*node)->right;
    free_node(old_node);
  } else if ((*node)->right == NULL) {
    *node = (*node)->left;
    free_node(old_node);
  } else {
    /* delete node with two children */
    struct bst_node** pred = &(*node)->left;
    while ((*pred)->right != NULL) {
      pred = &(*pred)->right;
    }
    /* Swap values */
    temp = (*pred)->data;
    (*pred)->data = (*node)->data;
    (*node)->data = temp;
    delete(pred);
  }
}

int cmp(void *left, void *right) {
  return strcmp(left, right);
}

void enqueue(void * i) {
  /* add node to last element */
  DLLNODE *n = (DLLNODE *) malloc(sizeof(DLLNODE));
  if (n == NULL) return; /* error */
  if (first == NULL) { /* empty */
    first = n;
  } else {
    DLLNODE *p = last;
    p->next = n;
  }
  last = n;
  n->next = NULL;
  n->data = i;
  prt_qnode("e", n);
}
 
struct bst_node * dequeue() /* remove first element */ {
  DLLNODE *p = first;
  if (first == NULL) return NULL; /* empty */
  first = p->next;
  if (first == NULL) last = NULL;
  return p->data; 
}

void btraverse(struct bst_node* node) {
  if (node == NULL)  return;
  enqueue(node);
  while (node) {
    node = dequeue();
    prt_node("d", node);
    if (node) { 
      if (node->left) enqueue(node->left);
      if (node->right) enqueue(node->right);
    }
  }
}

int main (int argc, char *argv[]) {
  int i;
  struct bst_node *r;
  if (argc < 8) {
    printf("%s 7 or more numbers\n", argv[0]);
    return 0;
  }
  r = new_node(argv[1]);
  for(i = 2; i < argc; i++) insert(&r, cmp, argv[i]);
  traverse(r);
  btraverse(r);
  return 0;
}
