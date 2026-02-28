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

template <class T>
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
