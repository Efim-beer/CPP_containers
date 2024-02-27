#ifndef SRC_S21_STACK_CC_
#define SRC_S21_STACK_CC_
#include "s21_stack.h"

namespace s21 {

template <class value_type>
stack<value_type>::stack() : head_(nullptr), size_(0) {}

template <class value_type>
stack<value_type>::stack(std::initializer_list<value_type> const &items)
    : stack() {
  for (auto i = items.begin(); i != items.end(); i++) {
    push(*i);
  }
}

// конструктор копирования
template <class value_type>
stack<value_type>::stack(const stack &s) : stack() {
  if (s.head_ != nullptr && this != &s) {
    stack<value_type> buf;
    Node *tmp = s.head_;
    while (tmp != nullptr) {
      buf.push(tmp->data_);
      tmp = tmp->pNext_;
    }
    while (buf.head_ != nullptr) {
      push(buf.head_->data_);
      buf.pop();
    }
  }
}

// конструктор переноса
template <class value_type>
stack<value_type>::stack(stack &&s) : stack() {
  swap_stack(std::move(s));
}

// мусоросжигающая печь
template <class value_type>
stack<value_type>::~stack() {
  while (size_) {
    pop();
  }
}

// Перегрузка оператора присваивания для движущегося объекта
template <class value_type>
typename stack<value_type>::reference stack<value_type>::operator=(stack &&s) {
  this->size_ = s.size_;
  this->head_ = s.head_;
  s.head_ = nullptr;
  s.size = 0;
  return *this;
}

/*************************************************************/

//обращается к верхнему элементу
template <class value_type>
typename s21::stack<value_type>::const_reference stack<value_type>::top() {
  return head_->data_;
}

/****************************************************************/

// проверяет, пуст ли контейнер
template <class value_type>
bool stack<value_type>::empty() const {
  return bool(size_);
}

// возрощает кол-во элементов
template <class value_type>
typename stack<value_type>::size_type stack<value_type>::size() const {
  return size_;
}

template <class value_type>
void stack<value_type>::push(const_reference value) {
  Node *temp = new Node(value);
  if (size_ == 0) {
    head_ = temp;
  } else {
    temp->pNext_ = head_;
    head_ = temp;
  }
  size_++;
}

template <class value_type>
void stack<value_type>::pop() {
  if (!head_)
    throw std::invalid_argument("pointer being freed was not allocated");
  Node *temp = head_->pNext_;
  delete head_;
  if (size_ > 1) {
    head_ = temp;
  } else {
    head_ = nullptr;
  }
  size_--;
}

// меняет содержимое
template <class value_type>
void stack<value_type>::swap(stack &other) {
  swap_stack(std::move(other));
}
/******************************************************************/

template <class value_type>
void stack<value_type>::swap_stack(stack &&other) {
  std::swap(size_, other.size_);
  std::swap(head_, other.head_);
}

// добавляет новые элементы в верхнюю часть контейнера
template <class value_type>
template <class... Args>
void stack<value_type>::emplace_back(Args &&...args) {
  std::vector<value_type> arguments = {args...};
  for (auto &a : arguments) {
    push(a);
  }
}

template <class value_type>
void stack<value_type>::printStack() {  // распечатывает и удаляет
  while (size_ != 0) {
    std::cout << this->top() << " ";
    this->pop();
  }
  std::cout << std::endl;
}

}  // namespace s21

#endif  // SRC_S21_STACK_CC_
