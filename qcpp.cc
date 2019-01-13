#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
using namespace std;

class Queue {
public:
  Queue() : head( NULL ) {};
  ~Queue();
  void enqueue( void *data);
  void *dequeue();
protected:
  class Element { 
  public:
    Element( Element *n, void *d ): next(n), data( d ) { } 
    Element *getNext() const { return next; }
    void setNext(Element *n) { next = n; }
    void *value() const { return data; }
  private:
    Element *next; 
    void *data;
  };

  Element *head; 
  Element *last; 
};

Queue::~Queue() { 
  while( head ) {
    Element *next = head->getNext(); 
    delete head;
    head = next;
  } 
}

void Queue::enqueue( void *data ) {
  //Allocation error will throw exception 
  Element *element = new Element(NULL,data); 
  if (head == NULL) {
    head = element;
  } else {
    last->setNext(element);
  }
  last = element;
}

void *Queue::dequeue() {
  Element *dequeueElement = head; 
  void *data;
  /* Assume QueueError exception class is defined elsewhere */ 
  if( head == NULL )
    // throw QueueError( E_EMPTY );
    throw std::invalid_argument( "empty queue" );
  data = head->value(); 
  head = head->getNext(); 
  delete dequeueElement; 
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
  Queue *s = new Queue();

  cout << "enqueueing into queue";
  for (int i = 0; i != cnt; i++) {
    cout << " " << i;
    itemp = new int (i);
    s->enqueue(itemp);
  }

  cout << endl << "dequeueing from queue";
  bool notempty = true;
  while (notempty) {
    try {
      itemp = (int *) s->dequeue();
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
