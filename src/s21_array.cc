#ifndef SRC_S21_ARRAY_CC_
#define SRC_S21_ARRAY_CC_
#include "s21_array.h"

namespace s21 {
/*конструкторы, деструкторы
 * **************************************************************************************/

/*конструктор по умолчанию, создает пустой массив*/
template <class value_type, size_t size_>
array<value_type, size_>::array() {
  for (size_type i = 0; i < size_; ++i) *(head_ + i) = 0;
}

/*конструктор списка инициализаторов, создает массив,
 инициализированный с помощью std::initializer_list<T>*/
template <class value_type, size_t size_>
array<value_type, size_>::array(
    std::initializer_list<value_type> const &items) {
  size_type i = 0;
  for (const auto &val : items) {
    if (i >= size_) break;
    *(head_ + i) = val;
    ++i;
  }
  for (; i < size_; ++i) *(head_ + i) = 0;
}

/* конструктор копирования *************************/
template <class value_type, size_t size_>
array<value_type, size_>::array(const array &a) {
  if (this != &a) {
    for (size_type i = 0; i < size_; ++i) *(head_ + i) = *(a.head_ + i);
  }
}

/* конструктор перемещения *************************/
template <class value_type, size_t size_>
array<value_type, size_>::array(array &&a) {
  if (this != &a) {
    std::move(std::begin(a.head_), std::end(a.head_), &head_[0]);
  }
}

/* мусоросжигательная печь ************************/
template <class value_type, size_t size_>
array<value_type, size_>::~array() {}

//Перегрузка оператора присваивания для движущегося объекта
template <class value_type, size_t size_>
void array<value_type, size_>::operator=(array &&a) {
  array(std::move(a));
}

/*В этой таблице перечислены публичные методы для доступа к элементам класса:
 * **************************************/

//доступ к указанному элементу с проверкой границ
template <class value_type, size_t size_>
typename array<value_type, size_>::reference array<value_type, size_>::at(
    size_type pos) {
  if (pos < size_) return operator[](pos);
  throw std::out_of_range("Out of range");
}

// доступ к указанному элементу
template <class value_type, size_t size_>
typename array<value_type, size_>::reference
array<value_type, size_>::operator[](size_type pos) {
  return *(head_ + pos);
}

//получить доступ к первому элементу
template <class value_type, size_t size_>
typename array<value_type, size_>::const_reference
array<value_type, size_>::front() {
  return *head_;
}

//получить доступ к последнему элементу
template <class value_type, size_t size_>
typename array<value_type, size_>::const_reference
array<value_type, size_>::back() {
  return *(head_ + size_ - 1);
}

//прямой доступ к базовому массиву
template <class value_type, size_t size_>
typename array<value_type, size_>::value_type *
array<value_type, size_>::data() {
  return head_;
}

/*В этой таблице перечислены публичные методы для итерирования по элементам
 * класса (доступ к итераторам): ********************/

//возвращает итератор в начало
template <class value_type, size_t size_>
typename array<value_type, size_>::iterator array<value_type, size_>::begin() {
  return head_;
}

//возвращает итератор в конец
template <class value_type, size_t size_>
typename array<value_type, size_>::iterator array<value_type, size_>::end() {
  return head_ + size_;
}

/* В этой таблице перечислены публичные методы для доступа к информации о
 * наполнении контейнера: ***************************/

//проверяет, пуст ли контейнер
template <class value_type, size_t size_>
bool array<value_type, size_>::empty() {
  return !size_;
}

//возвращает количество элементов
template <class value_type, size_t size_>
typename array<value_type, size_>::size_type array<value_type, size_>::size() {
  return size_;
}

//возвращает максимально возможное количество элементов
template <class value_type, size_t size_>
typename array<value_type, size_>::size_type
array<value_type, size_>::max_size() {
  return size_;
}

/*В этой таблице перечислены публичные методы для изменения контейнера:
 * **************************************************/

//меняет содержимое
template <class value_type, size_t size_>
void array<value_type, size_>::swap(array &other) {
  if (this != &other && size_ == other.size())
    for (size_type i = 0; i < size_; ++i) std::swap(head_[i], other.head_[i]);
}

//присваивает заданное значение value всем элементам в контейнере.
template <class value_type, size_t size_>
void array<value_type, size_>::fill(const_reference value) {
  for (size_type i = 0; i < size_; ++i) *(head_ + i) = value;
}

int main() {
  using namespace std;
  // s21::array<int, 10>
  int my_array[4];
  for (int i = 0; i <= 4; i++) {
    std::cout << "my_array[" << i << "]= " << my_array[i] << "\n";
  }

  system("pause");
  return 0;
}

template <class value_type, size_t size_>
void array<value_type, size_>::PrintList() {
  std::cout << "size of lise: " << size_ << std::endl;
  for (iterator i = begin(); i != end(); ++i) {
    std::cout << *i << " ";
  }
  std::cout << std::endl;
}

}  // namespace s21

#endif  // SRC_S21_ARRAY_CC_
