#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct bst_node {
  void* data;
  struct bst_node* left;
  struct bst_node* right;
};

struct bst_node* new_node(void* data) {
  struct bst_node* result = malloc(sizeof(struct bst_node));
  printf("new %s: %p\n", (char *) data, result);
  result->data = data;
  result->left = result->right = NULL;
  return result;
}

void free_node(struct bst_node* node) { free(node); }

/* 
   Returns negative (left<right), zero (left==right), or positive (left>right).
*/
typedef int comparator(void* left, void* right);

struct bst_node** search(struct bst_node** root, comparator compare, void* data) {
  struct bst_node** node = root;
  while (*node != NULL) {
    int compare_result = compare(data, (*node)->data);
    printf("search %s: %p %s l %p r %p\n", (char *) data, *node, 
	   (char *) (*node)->data, (*node)->left, (*node)->right);
    if (compare_result < 0) node = &(*node)->left;
    else if (compare_result > 0) node = &(*node)->right;
    else break;
  }
  return node;
}

void  traverse(struct bst_node* root) {
  struct bst_node* node = root;
  if (node == NULL)  return;
  traverse(node->left);
  printf("traverse: %p %s l %p r %p\n", 
	 node, (char *) node->data, node->left, node->right);
  traverse(node->right);
}

void insert(struct bst_node** root, comparator compare, void* data) {
  struct bst_node** node = search(root, compare, data);
  if (*node == NULL) { *node = new_node(data); }
}

void delete(struct bst_node** node) {
  struct bst_node* old_node = *node;
  void *temp;
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

int main (int argc, char *argv[]) {
  int i;
  struct bst_node *r;
  if (argc < 2) {
    printf("%s numbers\n", argv[0]);
    return 0;
  }
  r = new_node(argv[1]);
  for(i = 2; i < argc; i++) insert(&r, cmp, argv[i]);
  traverse(r);
  return 0;
}
