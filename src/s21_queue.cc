#ifndef SRC_S21_QUEUE_CC_
#define SRC_S21_QUEUE_CC_
#include "s21_queue.h"

#include <iostream>
#include <vector>

namespace s21 {
/* Конструкторы, деструкторы *************************************/

//конструктор по умолчанию, создает пустую очередь
template <class value_type>
queue<value_type>::queue() : first_(nullptr), last_(nullptr), size_(0) {}

//конструктор списка инициализаторов,
//создает очередь, инициализированную с помощью std::initializer_list<T>
template <class value_type>
queue<value_type>::queue(std::initializer_list<value_type> const &items)
    : queue() {
  for (auto i = items.begin(); i != items.end(); i++) {
    push(*i);
  }
}

//конструктор копирования
template <class value_type>
queue<value_type>::queue(const queue &q)
    : first_(nullptr), last_(nullptr), size_(0) {
  if (q.first_ != nullptr && this != &q) {
    push(q.first_->data_);
    if (q.first_->pNext_ != nullptr) {
      Node *tmp = q.first_->pNext_;
      while (tmp != nullptr) {
        push(tmp->data_);
        tmp = tmp->pNext_;
      }
    }
  }
}

// конструктор переноса
template <class value_type>
queue<value_type>::queue(queue &&q)
    : first_(nullptr), last_(nullptr), size_(0) {
  swap_queue(std::move(q));
}

//мусоросжигающая печь
template <class value_type>
queue<value_type>::~queue() {
  while (size_) {
    pop();
  }
}

// Перегрузка оператора присваивания для движущегося объекта
template <class value_type>
value_type &queue<value_type>::operator=(queue &&q) {
  this->first_ = q.first_;
  this->last_ = q.last_;
  this->size_ = q.size_;
  q.first_ = q.last_ = nullptr;
  q.size_ = 0;
  return *this;
}

/******************************************************************/

// получить доступ к первому элементу
template <class value_type>
typename s21::queue<value_type>::const_reference queue<value_type>::front() {
  if (first_ == nullptr) {
    throw std::invalid_argument("first_ = null pointer");
  }
  return this->first_->data_;
}

// получить доступ к последниму элементу элементу
template <class value_type>
typename s21::queue<value_type>::const_reference queue<value_type>::back() {
  if (last_ == nullptr) {
    throw std::invalid_argument("last_ = null pointer");
  }
  return this->last_->data_;
}

/*******************************************************************/

//проверяет, пуст ли контейнер
template <class value_type>
bool queue<value_type>::empty() const {
  return bool(size_);
}

// возвращает количество элементов
template <class value_type>
typename queue<value_type>::size_type queue<value_type>::size() const {
  return size_;
}

template <class value_type>
typename queue<value_type>::size_type queue<value_type>::max_size() const {
  return (SIZE_MAX / (sizeof(first_) + sizeof(first_->data_)));
}

/*******************************************************************/

//вставляет элемент в конце
template <class value_type>
void queue<value_type>::push(const_reference value) {
  if (first_ == nullptr) {
    first_ = last_ = new Node(value);
  } else {
    Node *tmp = this->first_;
    while (tmp->pNext_ != nullptr) {
      tmp = tmp->pNext_;
    }
    tmp->pNext_ = new Node(value);
    last_ = tmp->pNext_;
  }
  size_++;
}

// удаляет первый элемент
template <class value_type>
void queue<value_type>::pop() {
  if (first_ == nullptr) {
    throw std::invalid_argument("first_ = null pointer");
  }
  Node *tmp = first_;
  first_ = first_->pNext_;
  if (first_ == nullptr) {
    last_ = nullptr;
  }
  delete tmp;
  size_--;
}

// меняет содержимое
template <class value_type>
void queue<value_type>::swap(queue &other) {
  swap_queue(std::move(other));
}

// добавляет новые элементы в конец контейнера
template <class value_type>
template <class... Args>
void queue<value_type>::emplace_back(Args &&...args) {
  std::vector<value_type> arguments = {args...};
  for (auto &a : arguments) {
    push(a);
  }
}

/**********************************************************************/

template <class value_type>
value_type &queue<value_type>::operator[](const int index) {
  int counter = 0;
  Node *tmp = this->first_;
  while (tmp != nullptr) {
    if (counter == index) {
      break;
      ;
    }
    tmp = tmp->pNext_;
    counter++;
  }
  return tmp->data_;
}

template <class value_type>
void queue<value_type>::swap_queue(queue &&q) {
  std::swap(first_, q.first_);
  std::swap(last_, q.last_);
  std::swap(size_, q.size_);
}

}  // namespace s21

#endif  // SRC_S21_QUEUE_CC_