#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */
#include <string.h> /* strcmp */
#include <sys/param.h> /* MAX */

/*
 Try running with 5 3 7 2 4 6 8 1 9:
             5
           3   7
          2 4 6 8
         1       9
*/

struct bst_node {
  void* data;
  struct bst_node* parent;
  struct bst_node* left;
  struct bst_node* right;
};

void prt_node(char * name, struct bst_node* node) { 
  if (node)
    printf("%s %s: %p %s p %p l %p r %p\n", name, (char *) node->data, 
	   node, (char *) node->data, node->parent, node->left, node->right);
  else 
    printf("%s: %p\n", name, node); 
}

struct bst_node *new_node(void *data, struct bst_node *parent) {
  struct bst_node *result = malloc(sizeof(struct bst_node));
  result->data = data;
  result->parent = parent; /* so we can walk upward */
  result->left = result->right = NULL;
  return result;
}

void free_node(struct bst_node* node) { /* NOT used by this code! */
  free(node); 
}

/* 
   Returns negative (left<right), zero (left==right), or positive (left>right).
*/
typedef int comparator(void *left, void *right);

struct bst_node **search(struct bst_node **root, comparator compare, 
			 void *data, struct bst_node **parent) {
  struct bst_node **node = root;
  while (*node != NULL) {
    int compare_result = compare(data, &(*node)->data);
    if (parent) *parent = *node; /* set parent if needed */
    if (compare_result < 0) node = &(*node)->left;
    else if (compare_result > 0) node = &(*node)->right;
    else break;
  }
  return node;
}

void traverse(struct bst_node *root) {
  if (root == NULL)  return;
  traverse(root->left);
  printf("%s ", (char *) root->data); 
  prt_node("traver", root);
  traverse(root->right);
}

void insert(struct bst_node **root, comparator compare, void *data) {
  struct bst_node *parent; /* pass from search to new_node */
  struct bst_node **node = search(root, compare, data, &parent);
  if (*node == NULL) { *node = new_node(data, parent); }
}

void delete(struct bst_node** node) { /* NOT USED in this code! */
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

/*---------------------------------------------------------------------------*/

struct bst_node * findlowestcommonancestor(struct bst_node *root, 
					   char * d1, char * d2) {
  while (root) {
    int r1, r2;
    r1 = cmp(root->data, d1);
    r2 = cmp(root->data, d2);
    if (r1 > 0 && r2 > 0) root = root->left;
    else if (r1 < 0 && r2 < 0) root = root->right;
    else return root;
  }
  return NULL;
}

int treeheight(struct bst_node *r) {
  if (r == NULL) return 0;
  return 1 + MAX(treeheight(r->left), treeheight(r->right));
}  

struct bst_node * rotateright(struct bst_node *r) {
  /* chg this 
       3 p: 0, l: 2, r: 0
      2  p: 3, l: 1, r: 0
     1   p: 2, l: 0, r: 0
     to this
      2  p: 0*, l: 1,  r: 3*
     1   p: 2,  l: 0,  r: 0  
       3 p: 2*, l: 0*, r: 0
  */
  struct bst_node *new = r->left;
  r->left = new->right;
  r->parent = new;
  new->right = r;
  new->parent = NULL;
  return new;
}

struct bst_node * rotateleft(struct bst_node *r) {
  struct bst_node *new = r->right;
  r->right = new->left;
  r->parent = new;
  new->left = r;
  new->parent = NULL;
  return new;
}

struct bst_node * findmin(struct bst_node *r) {
  while (r && r->left) r = r->left;
  return r;
}

struct bst_node * findmax(struct bst_node *r) {
  while (r && r->right) r = r->right;
  return r;
}

struct bst_node *findnext(struct bst_node *r, char *data) {
  struct bst_node **t = search(&r, cmp, data, NULL);
  if (*t == NULL) return NULL;
  r = *t; /* see suggested tree values above */
  if (r->right) { /* 3 5 (right AND left) 7 8 */
    r = r->right;
    while (r && r->left) r = r->left;
  } else { /* 1 2 4 6: 9 returns null */
    while(r) {
      if (r->parent && r == r->parent->left) {
	r = r->parent;
	break; /* found it */
      } else r = r->parent; /* keep looking */
    } /* while: next not found, return null */
  } /* else */
  return r;
}

struct bst_node *findprev(struct bst_node *r, char *data) {
  struct bst_node **t = search(&r, cmp, data, NULL);
  if (*t == NULL) return NULL;
  r = *t;
  if (r->left) {
    r = r->left;
    while (r && r->right) r = r->right;
  } else {
    while(r) {
      if (r->parent && r == r->parent->right) {
	r = r->parent;
	break;
      } else r = r->parent;
    }
  }
  return r;
}

/*---------------------------------------------------------------------------*/

int main (int argc, char *argv[]) {
  int i, h, hl, hr;
  struct bst_node *r;
  struct bst_node *t;

  if (argc < 4) {
    printf("%s 3 or more numbers\n", argv[0]);
    return 0;
  }
  r = new_node(argv[1], NULL);
  printf("%s ", argv[1]);
  for(i = 2; i < argc; i++) {
    insert(&r, cmp, argv[i]);
    printf("%s ", argv[i]);
  }
  printf("\n");

  /* find the height of the tree and left and right subtrees */
  h = treeheight(r);
  printf("height of tree is %d, ", h);
  hl = treeheight(r->left);
  printf("height of left subtree is %d, ", hl);
  hr = treeheight(r->right);
  printf("height of right subtree is %d\n", hr);

  /* balance the tree if unequal... 
             5
           4   6
          3     7
         2       8
        1         9
	but NOT the subtrees! */
  traverse(r);
  if (hl > hr) for (; hl > hr; hr++, hl--) r = rotateright(r);
  else if (hl < hr) for (; hl < hr; hr--, hl++) r = rotateleft(r);
  hl = treeheight(r->left);
  printf("height of rotated left subtree is %d, ", hl);
  hr = treeheight(r->right);
  printf("height of rotated right subtree is %d\n", hr);  
  traverse(r);

  /* find the lowest/nearest common ancestor of two nodes */
  /* Try running with 5 3 7 2 4 6 8 1 9 */
  t = findlowestcommonancestor(r, "1", "4");
  prt_node("lca", t);
  printf("lowest common ancestor of %s and %s is %s\n", "1", "4",
	 t ? (char *) t->data: "none");

  /* find lowest element ("1") */
  t = findmin(r);
  printf("min element is %s, ", t ? (char *) t->data: "none");
  /* find highest element ("9") */
  t = findmax(r);
  printf("max element is %s, ", t ? (char *) t->data: "none");
  printf("root element is %s\n", r ? (char *) r->data: "none");

  for(i = 1; i < argc; i++) {
    /* find next and previous in order elements */
    t = findnext(r, argv[i]);
    printf("next element after %s is %s, ", 
	   argv[i], t ? (char *) t->data: "none");
    t = findprev(r, argv[i]);
    printf("prev element before %s is %s\n", 
	   argv[i], t ? (char *) t->data: "none");
  }

  return 0;
}
