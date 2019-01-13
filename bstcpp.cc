#include <iostream>
#include <sstream>
#include <string>
using namespace std;

// see bst2.c: port insert (search), findmin, findnext, traverse, prt_node
// BUT use ints instead of strings

class Node {
public: 
  Node( Node *p, int v ) : parent(p), value(v) { left = right = NULL; }
  Node *getParent() { return parent; } 
  void setParent(Node *p) { parent = p; } 
  Node **getaLeft() { return &left; } 
  Node **getaRight() { return &right; } 
  Node *getLeft() { return left; } 
  Node *getRight() { return right; } 
  int getValue() { return value; }
private:
  Node *parent; 
  Node *left; 
  Node *right; 
  int value;
};

class BTree {
public:
  BTree() : head (NULL) {};
  ~BTree() {}; // tbd
  Node *getHead() { return head; } 
  Node **search(int i, Node **p); 
  bool insert(int i);
  bool remove(int i) {return false;} // tbd
  void prtnode(Node *h);
  void traverse(Node *n);
  int findmin(); // tbd
  Node *findnext(int i); // tbd
protected:
  
  Node *head;
};

Node **BTree::search(int i, Node **p) {
  Node **h = &head;
  while (*h) { // see if a node with this value is already there
    int v = (*h)->getValue();
    if (p) *p = *h;
    if (i < v) h = (*h)->getaLeft();
    else if (i > v) h = (*h)->getaRight();
    else break;
  }
  return h;
}

bool BTree::insert(int i) {
  if (head == NULL) { // 1st node is special
    head = new Node(NULL, i);
    prtnode(head);
    //cout << "dbg insert: h" << head << endl; 
    return true;
  }

  Node *p;
  Node **h = search(i, &p);

  //cout << "dbg insert: h" << h << endl; 
  if (*h) return false; // node with this value is already there
  // chg the null ptr to point to our new node
  else {
    *h = new Node(p, i); // die? Node::getParent this=0
  }
  prtnode(*h);
  return true;
}

void BTree::prtnode(Node *h) {
  cout << h->getValue() << " " << h << " p " << h->getParent() << 
    " l " << h->getLeft() << " r " << h->getRight() << endl;
}

void BTree::traverse(Node *h) {
  if (h == NULL)  return;
  traverse(h->getLeft());
  prtnode(h);
  traverse(h->getRight());
}

int BTree::findmin() {
  Node *n = head;
  while(n && n->getLeft()) n = n->getLeft();
  return n->getValue();
}

Node * BTree::findnext(int i) {
  Node **t = search(i, NULL);
  if (t == NULL) return NULL;
  Node *r = *t;
  if (r->getRight()) {
    r = r->getRight();
    while (r && r->getLeft()) r = r->getLeft();
  } else {
    while(r) {
      if (r->getParent() && r == r->getParent()->getLeft()) {
        r = r->getParent();
        break;
      } else r = r->getParent();
    }
  }
  return r;
}

int main(int argc, char *argv[]) {

  if (argc < 4) {
    cout << argv[0] << " 3 or more numbers" << endl;
    return 0;
  }

  BTree *t = new BTree();

  for (int i = 1; i < argc; i++) {
    istringstream mystream(argv[i]);
    int num;
    mystream >> num;
    cout << num << " ";
    t->insert(num);
  }
  cout << endl;

  Node *h = t->getHead();
  t->traverse(h);

  cout << "min value is " << t->findmin() << endl;

  for (int i = 1; i < argc; i++) {
    istringstream mystream(argv[i]);
    int num, val = -1;
    mystream >> num;
    Node *n = t->findnext(num);
    if (n) val = n->getValue();
    cout << "next value after "<< num << " is " << val << endl;
  }

  return 0;
} 
