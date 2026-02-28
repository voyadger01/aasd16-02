#include <iostream>

template < class T >
struct BiList
{
  T val;
  BiList< T >* next;
  BiList< T >* prev;
};
