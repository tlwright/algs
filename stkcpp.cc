#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
using namespace std;

class Stack {
public:
  Stack() : head( NULL ) {};
  ~Stack();
  void push( void *data);
  void *pop();
protected:
  class Element { 
  public:
    Element( Element *n, void *d ): next(n), data( d ) { } 
    Element *getNext() const { return next; }
    void *value() const { return data; }
  private:
    Element *next; 
    void *data;
  };

  Element *head; 
};

Stack::~Stack() { 
  while( head ) {
    Element *next = head->getNext(); 
    delete head;
    head = next;
  } 
}

void Stack::push( void *data ) {
  //Allocation error will throw exception 
  Element *element = new Element(head,data); 
  head = element;
}

void *Stack::pop() {
  Element *popElement = head; 
  void *data;
  /* Assume StackError exception class is defined elsewhere */ 
  if( head == NULL )
    // throw StackError( E_EMPTY );
    throw std::invalid_argument( "empty stack" );
  data = head->value(); 
  head = head->getNext(); 
  delete popElement; 
  return data;
}

int main(int argc, char *argv[]) {
  int cnt, *itemp;
  
  if (argc != 2) {
    cout << argv[0] << " n" << endl;
    return 0;
  }

  istringstream myStream(argv[1]);
  myStream >> cnt;
  Stack *s = new Stack();

  cout << "pushing into stack";
  for (int i = 0; i != cnt; i++) {
    cout << " " << i;
    itemp = new int (i);
    s->push(itemp);
  }

  cout << endl << "popping from stack";
  bool notempty = true;
  while (notempty) {
    try {
      itemp = (int *) s->pop();
    }
    catch (exception& e) {
      // cout << endl << "Caught exception: " << e.what();
      notempty = false;
      break;
    }
    cout << " " << (int) *itemp;
    delete itemp;
  }
  cout << endl;

  delete s;
  return 0;
} 
