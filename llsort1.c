#include <stdio.h>    /* for printf */
#include <stdlib.h>   /* for malloc */
 
typedef struct node {
  int data;
  struct node *next; /* pointer to next element in list */
} LLIST;
 
struct bst_node {
  int data;
  struct bst_node* left;
  struct bst_node* right;
};

void prt_node(char * name, LLIST * node) { 
  printf("%s %d: %p %d n %p\n", name, node->data, 
	 node, node->data, node->next);
}

LLIST *list_add(LLIST **p, int i) {
  LLIST *n = (LLIST *) malloc(sizeof(LLIST));
  if (n == NULL) return NULL;
  n->next = *p;
  n->data = i;
  *p = n;
  prt_node("add   ", n);
  return n;
}
 
void list_print(LLIST *n) {
  if (n == NULL) { printf("list is empty\n"); }
  while (n != NULL) {
    prt_node("list  ", n);
    n = n->next;
  }
}

/*===================================================================*/
void prt_tnode(char * name, struct bst_node* node) { 
  printf("%s %d: %p %d l %p r %p\n", name, node->data, 
	 node, node->data, node->left, node->right);
}

struct bst_node* new_node(int data) {
  struct bst_node* result = malloc(sizeof(struct bst_node));
  result->data = data;
  result->left = result->right = NULL;
  prt_tnode("new   ", result);
  return result;
}

void free_node(struct bst_node* node) { 
  prt_tnode("free  ", node);
  free(node); 
}

/* 
   Returns negative (left<right), zero (left==right), or positive (left>right).
*/
typedef int comparator(int left, int right);

struct bst_node** search(struct bst_node** root, comparator compare, int data) {
  struct bst_node** node = root;
  while (*node != NULL) {
    int compare_result = compare(data, (*node)->data);
    prt_tnode("search", *node);
    if (compare_result < 0) node = &(*node)->left;
    else if (compare_result > 0) node = &(*node)->right;
    else break;
  }
  return node;
}

void insert(struct bst_node** root, comparator compare, int data) {
  struct bst_node** node = search(root, compare, data);
  if (*node == NULL) { *node = new_node(data); }
}

void delete(struct bst_node** node) {
  struct bst_node* old_node = *node;
  int temp;
  prt_tnode("delete", *node);
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

int cmp(int left, int right) {
  return left == right ? 0 : left > right ? 1 : -1 ;
}
 
void  traverse(struct bst_node *root) {
  struct bst_node *node = root;
  if (node == NULL)  return;
  traverse(node->left);
  prt_tnode("traver", node);
  traverse(node->right);
}

void list_copy(LLIST *n, struct bst_node *r) {
  if (n == NULL) { printf("list is empty\n"); }
  while (n != NULL) {
    insert(&r, cmp, n->data);
    n = n->next;
  }
}

void bst_copy(struct bst_node *r, LLIST *n) {
  struct bst_node *node = r;
  if (node == NULL)  return;
  bst_copy(node->left, n->next);
  prt_tnode("bst_copy", r);
  prt_node("bst_copy", n);
  n->data = r->data;
  bst_copy(node->right, n->next);
}

int main(int argc, char *argv[]) {
  LLIST *n = NULL;
  LLIST *p = NULL;
  struct bst_node *r = NULL;
  int i;

  if (argc < 3) {
    printf("%s 2 or more numbers\n", argv[0]);
    return 0;
  }
  p = list_add(&n, atoi(argv[1]));
  for(i = 2; i < argc; i++) p = list_add(&p->next, atoi(argv[i]));
  list_print(n);
 
  /* To sort the LL: */
  /* copy to a BST: traverse LL via modified list_print and insert */
  /* copy the BST back to the LL via traverse and modified list_print  */
  /* Note: LL data is int, BST data was void *! Changed BST to int. */

  r = new_node(n->data);
  list_copy(n, r);
  traverse(r);
  bst_copy(r, n);
  list_print(n);

  return 0;
}
