#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct bst_node {
  int data;
  struct bst_node* left;
  struct bst_node* right;
};

struct bst_node* new_node(int data) {
  struct bst_node* result = malloc(sizeof(struct bst_node));
  printf("newnod %d: %p\n", data, result);
  result->data = data;
  result->left = result->right = NULL;
  return result;
}

void free_node(struct bst_node* node) { free(node); }

struct bst_node** search(struct bst_node** root, int data) {
  struct bst_node** node = root;
  while (*node != NULL) {
    printf("search %d: %p %d l %p r %p\n", data, *node, 
	   (*node)->data, (*node)->left, (*node)->right);
    if (data < (*node)->data) node = &(*node)->left;
    else if (data > (*node)->data) node = &(*node)->right;
    else break;
  }
  return node;
}

void insert(struct bst_node** root, int data) {
  struct bst_node** node = search(root, data);
  if (*node == NULL) { *node = new_node(data); }
}

void delete(struct bst_node** node) {
  struct bst_node* old_node = *node;
  int temp;
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

void verifybstnode ( struct bst_node *node) {
  /* verify node data not <= left->data */
  if (node->left && node->data <= node->left->data) {
    printf("verifybs data <= left: %p data %d left %d %p r %p\n", 
	   node, node->data, node->left->data, node->left, node->right);
    exit(-1);
  }
  /* verify node data not >= right->data */
  if (node->right && node->data >= node->right->data) {
    printf("verifybs data >= right: %p data %d l %p right %d %p\n", 
	   node, node->data, node->left, node->right->data, node->right);
    exit(1);
  }
}

void verifybst ( struct bst_node *node) {
  /* for node data 5: left = 3, right = 7 */
  if (!node) return;
  verifybst(node->left);

  printf("verifybs: %p %d l %p r %p\n", node, node->data, 
	 node->left, node->right);

  verifybstnode(node);

  verifybst(node->right);
  return;
} 

int main (int argc, char *argv[]) {
  int i, old, new;
  struct bst_node *r, **n;
  if (argc < 2) {
    printf("%s numbers\n", argv[0]);
    return 0;
  }
  r = new_node(atoi(argv[1]));
  for(i = 2; i < argc; i++) insert(&r, atoi(argv[i]));

  /* 5 3 7 2 4 6 8 1 9 creates balanced tree:
             5
           3   7
          2 4 6 8
         1       9
  */
  /* verify bst (ok), corrupt bst, verify bst (fail) */
  verifybst(r);
  if (argc % 2) { /* enable verify test of both left and right nodes */
    old = atoi(argv[argc - 1]);
    new = atoi(argv[1]);
  } else {
    old = atoi(argv[1]);
    new = atoi(argv[argc - 1]);
  }
  n = search(&r, old); /* find node with data */
  (*n)->data = new;  /* chg found node data */
  printf("found node with data of %d, changed data to %d\n", 
	 old, new);
  verifybst(r);
  return 0;
}
