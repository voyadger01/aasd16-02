#include <iostream>

// Fake + Loop, Bidir

template < class T >
struct BiList
{
  T val;
  BiList< T >* next;
  BiList< T >* prev;
};

template < class T >
BiList< T >* create_list()
{
  BiList< T >* head = new BiList< T >();
  head->next = head;
  head->prev = head;
  return head;
}

template < class T >
BiList<T>* push_front(BiList<T>* head, const T& val)
{
  if (!head) {
      return nullptr;
  }
  BiList<T>* node = new BiList<T>{val, head->next, head};
  head->next->prev = node;
  head->next = node;
  return head;
}

template < class T >
BiList< T >* push_back(BiList< T >* head, const T& val)
{
  if (!head) {
      return nullptr;
  }
  BiList< T >* node = new BiList< T >{val, head, head->prev};
  head->prev->next = node;
  head->prev = node;
  return head;
}

template < class T >
void pop_front(BiList< T >* head)
{
  if (!head || head->next == head) {
    return;
  }
  BiList< T >* temp = head->next;
  head->next = temp->next;
  temp->next->prev = head;
  delete temp;
}
