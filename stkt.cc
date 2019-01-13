// http://www.bgsu.edu/departments/compsci/docs/page95187.html
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
using namespace std;

template <class T>
class Stack {
public:
  Stack();
  void push(T i);
  T pop();
private:
  int top;
  T st[100];
};
 
template <class T>
Stack<T>::Stack()
{
  top = -1;
}
 
template <class T>
void Stack<T>::push(T i)
{
  st[++top] = i;
}
 
template <class T>
T Stack<T>::pop()
{
  // if (st[top] == -1) throw std::invalid_argument( "empty queue" );
  return st[top--];
}

int main(int argc, char *argv[]) {
  int cnt, i, num;
  string s;
  
  if (argc != 2) {
    cout << argv[0] << " n" << endl;
    return 0;
  }

  Stack<int> ii;
  Stack<string> ss;

  istringstream myStream(argv[1]);
  myStream >> cnt;

  cout << "pushing into stack ii and ss";
  for (i = 0; i != cnt; i++) {
    cout << " " << i;
    ii.push(i);
    s = static_cast<ostringstream*>(&(ostringstream() << i))->str();
    ss.push(s);
  }

  cout << endl << "popping from stack ii";
  for (i = 0; i != cnt; i++) {
    num = ii.pop();
    cout << " " << num;
  }

  cout << endl << "popping from stack ss";
  for (i = 0; i != cnt; i++) {
    s = ss.pop();
    cout << " " << s;
  }
  cout << endl;

  return 0;
} 
