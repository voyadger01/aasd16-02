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
