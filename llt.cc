// http://codereview.stackexchange.com/questions/4569/linked-list-implementation-in-c
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
using namespace std;

template <class T>
struct Node
{
  T data;
  Node * next;
};

template <class T>
class LinkedList
{
public:
  LinkedList() : head(NULL), size(0) {};
  ~LinkedList() { destroyList(); };
  bool addNode(T data);
  bool deleteNode(T data);
  Node<T> * searchNode(T data);
  void printList();
  void reverseList();
  void sortList();
private:
  Node<T> * head;
  int size;
  void destroyList();
  Node<T>* mergeSort(Node<T> * head, int total);
  Node<T>* Merge(Node<T>* left, int lcount, Node<T>* right, int rcount);
  void print(Node<T> * tmp);
};


template <class T>
bool LinkedList<T>::addNode(T data)
{
try
  {
    Node<T> * tmp = new Node<T>();
    tmp->data = data;
    tmp->next = head;
    head = tmp;
    ++size;
    return true;
  }
catch(std::exception & ex)
  {
    return false;
  }
}

template <class T>
bool LinkedList<T>::deleteNode(T data)
{
  Node<T> *curr = head, *prev = NULL;

  while (curr)
    {
      if (curr->data == data) break;

      prev = curr;
      curr = curr->next;
    }

  if (curr)
    {
      if (prev)
        {
          prev->next = curr->next;
        }
      else
        {
          head = curr->next;
        }
      delete(curr);
      --size;
      return true;
    }
  else
    {
      return false;
    }
}

template <class T>
Node<T> * LinkedList<T>::searchNode(T data)
{
  Node<T> * tmp = head;
  while (tmp)
    {
      if (tmp->data == data)
        {
          return tmp;
        }
      tmp = tmp->next;
    }
  return NULL;
}

template <class T>
void LinkedList<T>::print(Node<T> * tmp)
{
  bool printNewLine = (tmp) ? true : false;
  while (tmp)
    {
      std::cout << tmp->data << ",";
      tmp = tmp->next;
    } 

  if (printNewLine)
    {
      std::cout << std::endl;
    }
}

template <class T>
void LinkedList<T>::printList()
{
  Node<T> * tmp = head;
  bool printNewLine = (tmp) ? true : false;
  while (tmp)
    {
      std::cout << tmp->data << "|";
      tmp = tmp->next;
    } 

  if (printNewLine)
    {
      std::cout << std::endl;
    }
}

template <class T>
void LinkedList<T>::destroyList()
{
  Node<T> * tmp = NULL;
  while (head)
    {
      tmp = head;
      head = head->next;
      //std::cout << "deleting data " << tmp->data << std::endl;
      delete(tmp);
    }
}

template <class T>
void LinkedList<T>::reverseList()
{
  Node<T> *curr = head, *prev = head, *save = NULL;

  while (curr)
    {
      save = curr->next;
      curr->next = prev;
      prev = curr;
      curr = save;
    }

  head->next = NULL;
  head = prev;
}

//use merge sort
template <class T>
void LinkedList<T>::sortList()
{
  head = mergeSort(head, size);
}

template <class T>
Node<T>* LinkedList<T>::mergeSort(Node<T> * first, int total)
{
  if (total < 1) { return first; }
  if (total < 2) { first->next = NULL; return first;}

  Node<T> * curr = first;
  int count = total/2;
  while (count--)
    {
      curr = curr->next;
    }


  count = total/2;
  first = mergeSort(first, count);

  curr = mergeSort(curr, total-count);

  return Merge(first, count, curr, total-count);
}

template <class T>
Node<T>* LinkedList<T>::Merge(Node<T>* left, int lcount, Node<T>* right, int rcount)
{
  Node<T> * h = new Node<T>();
  h->next = NULL;
  Node<T> * tmp = h;

  while (lcount > 0 && rcount > 0)
    {
      if (left->data < right->data)
        {
          tmp->next = left;
          tmp = tmp->next;
          left = left->next;
          --lcount;
        }
      else if (right->data < left->data)
        {
          tmp->next = right;
          tmp = tmp->next;
          right = right->next;
          --rcount;
        }
      else
        {
          tmp->next = left;
          tmp = tmp->next;
          left = left->next;
          --lcount;

          tmp->next = right;
          tmp = tmp->next;
          right = right->next;
          --rcount;
        }
    }

  while (lcount > 0)
    {
      tmp->next = left;
      tmp = tmp->next;
      left = left->next;
      --lcount;
    }

  while (rcount > 0)
    {
      tmp->next = right;
      tmp = tmp->next;
      right = right->next;
      --rcount;
    }

  tmp = h;
  h = h->next;
  delete(tmp);

  return h;
}

int main()
{
  LinkedList<int> l;
  l.addNode(3);
  l.addNode(2);
  l.addNode(6);
  l.addNode(4);
  l.addNode(3);

  l.printList();
  l.reverseList();
  l.printList();

  l.sortList();
  l.printList();

  l.deleteNode(3);
  l.deleteNode(3);
  l.deleteNode(4);

  l.printList();
  l.reverseList();
  l.printList();

  l.sortList();
  l.printList();

  if (l.searchNode(2))
    {
      std::cout << "2 found \n";
    }

  if (!l.searchNode(5))
    {
      std::cout << "5 not found \n";
    }

  return 0;
}

