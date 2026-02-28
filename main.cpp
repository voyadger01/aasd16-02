#include <cstddef>
#include <utility>

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
  BiList< T >* head = new BiList< T >(); // T::T()
  head->next = head;
  head->prev = head;
  return head;
}

template < class T, class D >
BiList<T>* insert(BiList<T>* head, const T& val)
{
  if (!head) {
    return nullptr;
  }
  BiList<T>* node = new BiList<T>{std::forward< D >(val), head->next, head}; // T::T(const T&), T::T(T&&)
  head->next->prev = node;
  head->next = node;
  return head;
}

template < class T, class D >
BiList< T >* add(BiList< T >* head, const T& val)
{
  if (!head) {
    return nullptr;
  }
  BiList< T >* node = new BiList< T >{std::forward< D >(val), head, head->prev}; // T::T(const T&), T::T(T&&)
  head->prev->next = node;
  head->prev = node;
  return head;
}

template < class T >
void pop_front(BiList< T >* head) noexcept
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
void clear(BiList< T >* head) noexcept
{
  if (!head) {
    return;
  }
  while (head->next != head) {
    pop_front(head);
  }
  delete head;
}

template< class T, class F >
F traverse(BiList< T >* head, F f)
{
  if (!head) {
    return f;
  }
  BiList< T >* cur = head->next;
  while (cur != head) {
    f(cur->val); // F::operator()
    cur = cur->next;
  }
  return f; // F::F(const F&)
}

template< class T >
BiList< T >* convert(T* arr, size_t s)
{
  if (!arr) {
    return nullptr;
  }
  BiList< T >* head = create_list< T >();
  for (size_t i = 0; i < s; i++) {
    try {
      insert(head, arr[i]); // T::T(const T&), T::T(T&&)
    } catch (...) {
      clear(head);
      throw;
    }
  }
  delete[] arr; 
  return head;
}
