#include <cstddef>

// Fake + Loop, Bidir
// Неявный интерфейс для Т: T(), T(const T&), T(T&&)
// Неявный интерфейс для F: operator(), F(const F&)

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
BiList<T>* add(BiList<T>* head, const T& val)
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
BiList< T >* insert(BiList< T >* head, const T& val)
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

template< class T >
void clear(BiList< T >* head)
{
  while (head->next != head) {
    pop_front(head);
  }
  delete head;
}

template< class T, class F >
F traverse(BiList< T >* head, F f)
{
  BiList< T >* cur = head;
  while (cur != head) {
    f(cur->val);
    cur = cur->next;
  }
  return f;
}

template< class T >
BiList< T >* convert(T* arr, size_t s)
{
  BiList< T >* head = create_list< T >();
  for (size_t i = 0; i < s; i++) {
    push_back(head, arr[i]);
  }
  delete[] arr; 
  return head;
}
