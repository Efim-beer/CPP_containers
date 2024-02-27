#ifndef SRC_S21_VECTOR_CC_
#define SRC_S21_VECTOR_CC_

#include "s21_vector.h"

#include <iostream>

namespace s21 {
/* Конструкторы, деструкторы *************************************/

template <class value_type>
vector<value_type>::vector() : vector(0, value_type()) {}

template <class value_type>
vector<value_type>::vector(size_type n) : vector(n, value_type()) {}

template <class value_type>
vector<value_type>::vector(size_type n, value_type x) : size_{n}, capacity_{n} {
  InitMemory();
  for (size_type i = 0; i < size_; ++i) *(head_ + i) = x;
}

// конструктор списка инициализаторов, создает вектор,
// инициализированный с помощью std::initializer_list<T>
template <class value_type>
vector<value_type>::vector(std::initializer_list<value_type> const &items) {
  size_ = capacity_ = items.size();
  InitMemory();
  size_type i = 0;
  for (const_reference val : items) {
    *(head_ + i) = val;
    ++i;
  }
}

/* Copy Constructor */
template <class value_type>
vector<value_type>::vector(const vector &v) {
  if (this != &v) {
    size_ = v.size_;
    capacity_ = v.capacity_;
    InitMemory();
    CopyVector(head_, v.head_);
  }
}

/* Move Constructor*/
template <class value_type>
vector<value_type>::vector(vector &&v) {
  if (this != &v) {
    size_ = capacity_ = 0;
    head_ = nullptr;
    std::swap(size_, v.size_);
    std::swap(capacity_, v.capacity_);
    std::swap(head_, v.head_);
  }
}

template <class value_type>
vector<value_type>::~vector() {
  delete[] head_;
}

// Перегрузка оператора присваивания для движущегося объекта
template <class value_type>
void vector<value_type>::operator=(vector &&v) {
  vector(std::move(v));
}

/*****************************************/

/* Инициализировать память*/
template <class value_type>
void vector<value_type>::InitMemory() {
  if (size_)
    head_ = new value_type[size_];
  else
    head_ = nullptr;
}

template <class value_type>
void vector<value_type>::CopyVector(value_type *dst, value_type *src) {
  for (size_type i = 0; i < size_; ++i) {
    *(dst + i) = *(src + i);
  }
}

template <class value_type>
void vector<value_type>::IncreaseCapacity() {
  if (size_ == capacity_) {
    if (capacity_)
      capacity_ *= 2;
    else
      capacity_ = 1;
    if (capacity_ > max_size()) throw("capacity_ > max_size()");
  }
}

/***********************************************/

// доступ к указанному элементу с проверкой границ
template <class value_type>
typename vector<value_type>::reference vector<value_type>::at(size_type pos) {
  if (pos < size_) return operator[](pos);
  throw std::out_of_range("Out of range");
}

// доступ к указанному элементу
template <class value_type>
typename vector<value_type>::reference vector<value_type>::operator[](
    size_type pos) {
  return *(head_ + pos);
}

// получить доступ к первому элементу
template <class value_type>
typename vector<value_type>::const_reference vector<value_type>::front() {
  return *head_;
}

// получить доступ к последниму элементу
template <class value_type>
typename vector<value_type>::const_reference vector<value_type>::back() {
  return *(head_ + size_ - 1);
}

// прямой доступ к базовому массиву
template <class value_type>
typename vector<value_type>::value_type *vector<value_type>::data() {
  return head_;
}

/***************************************************************/

// base
template <class value_type>
typename vector<value_type>::value_type *vector<value_type>::iterator::base() {
  return iter_;
}

/**************************************************************/

// возвращает итератор в начало
template <class value_type>
typename vector<value_type>::iterator vector<value_type>::begin() {
  return iterator(this->head_);
}

// возвращает итератор конец
template <class value_type>
typename vector<value_type>::iterator vector<value_type>::end() {
  return iterator(this->head_ + size_);
}

/***************************************************************/

// проверяет, пуст ли контейнер
template <class value_type>
bool vector<value_type>::empty() {
  return !size_;
}

// возращает кол-во элементов
template <class value_type>
typename vector<value_type>::size_type vector<value_type>::size() {
  return size_;
}

// возвращает максимально возможное количество элементов
template <class value_type>
typename vector<value_type>::size_type vector<value_type>::max_size() {
  return std::numeric_limits<int64_t>::max() / sizeof(value_type);
}

// выделяет хранилище элементов размера и копирует текущие элементы массива в
// новый выделенный массив
template <class value_type>
void vector<value_type>::reserve(size_type size) {
  if (size > capacity_ && size < max_size()) {
    capacity_ = size;
    ReserveWithoutCheck();
  }
}

template <class value_type>
void vector<value_type>::ReserveWithoutCheck() {
  value_type *tmp = new value_type[capacity_];
  CopyVector(tmp, head_);
  delete[] head_;
  head_ = tmp;
}

// возвращает количество элементов, которые могут храниться в выделенном в
// данный момент
template <class value_type>
typename vector<value_type>::size_type vector<value_type>::capacity() {
  return capacity_;
}

// уменьшает использование памяти, освобождая неиспользуемую
template <class value_type>
void vector<value_type>::shrink_to_fit() {
  if (capacity_ > size_) {
    capacity_ = size_;
    ReserveWithoutCheck();
  }
}
/***********************************************/

// //очищает содержимое
template <class value_type>
void vector<value_type>::clear() {
  size_ = 0;
}

// вставляет элементы в конкретную позицию и возвращает итератор,
// указывающий на новый элемент
template <class value_type>
typename vector<value_type>::iterator vector<value_type>::insert(
    iterator pos, const_reference value) {
  value_type *ptr_end = end().base();
  IncreaseCapacity();
  ++size_;
  value_type *tmp = new value_type[size_];
  value_type *ptr_pos = pos.base();
  size_type i = 0;
  for (; head_ != ptr_pos; ++head_, ++i) {
    tmp[i] = *head_;
  }
  value_type *result = head_;
  tmp[i++] = value;
  for (; head_ != ptr_end; ++head_, ++i) {
    tmp[i] = *head_;
  }
  head_ = tmp;
  return iterator(result);
}

// стирает элемент в позиции
template <class value_type>
void vector<value_type>::erase(iterator pos) {
  value_type *ptr_pos = pos.base();
  value_type *ptr_end = end().base();
  while (ptr_pos != ptr_end) {
    value_type *tmp = ptr_pos;
    if (++ptr_pos != ptr_end) *tmp = *ptr_pos;
  }
  --size_;
}

// добавляет элемент в конец
template <class value_type>
void vector<value_type>::push_back(const_reference value) {
  IncreaseCapacity();
  ReserveWithoutCheck();
  *(head_ + size_) = value;
  ++size_;
}

// удаляет последний элемент
template <class value_type>
void vector<value_type>::pop_back() {
  if (size_ == 0)
    throw std::invalid_argument("pointer being freed was not allocated");
  --size_;
}

// меняет местами сожержимое
template <class value_type>
void vector<value_type>::swap(vector &other) {
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
  std::swap(head_, other.head_);
}

/*************************************************************/

// вставляет новые элементы в контейнер непосредственно перед pos
template <class value_type>
template <typename... Args>
typename vector<value_type>::iterator vector<value_type>::emplace(
    const_iterator pos, Args &&...args) {
  iterator result(pos);
  result = insert(result, value_type(std::forward<Args>(args)...));
  return result;
}

// добавляет новые элементы в конец контейнера
template <class value_type>
template <typename... Args>
void vector<value_type>::emplace_back(Args &&...args) {
  this->push_back(value_type(std::forward<Args>(args)...));
}

template <class value_type>
vector<value_type>::VectorIterator::VectorIterator() : iter_{nullptr} {}

template <class value_type>
vector<value_type>::VectorIterator::VectorIterator(value_type *iter)
    : iter_{iter} {}

template <class value_type>
typename vector<value_type>::reference
vector<value_type>::iterator::operator*() {
  return *iter_;
}

template <class value_type>
void vector<value_type>::iterator::operator++() {
  ++iter_;
}

template <class value_type>
void vector<value_type>::iterator::operator--() {
  --iter_;
}

template <class value_type>
bool vector<value_type>::iterator::operator==(
    const VectorIterator &other) const {
  return iter_ == other.iter_;
}

template <class value_type>
bool vector<value_type>::iterator::operator!=(
    const VectorIterator &other) const {
  return iter_ != other.iter_;
}

template <class value_type>
typename vector<value_type>::const_iterator vector<value_type>::cbegin() {
  return const_iterator(this->head_);
}

template <class value_type>
typename vector<value_type>::const_iterator vector<value_type>::cend() {
  return const_iterator(this->head_ + size_);
}

}  // namespace s21

#endif  // SRC_S21_VECTOR_CC_
