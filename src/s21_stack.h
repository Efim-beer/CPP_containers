#ifndef SRC_S21_STACK_H_
#define SRC_S21_STACK_H_
#include <initializer_list>
#include <iostream>
#include <set>
#include <vector>

namespace s21 {
template <typename T>
class stack {
 public:
  /*В этой таблице перечислены внутриклассовые переопределения типов (типичные
  для стандартной библиотеки STL), принятые для удобства восприятия кода
  класса:*/
  typedef T value_type;  //параметр шаблона T
  typedef T &reference;  //определяет тип ссылки на элемент
  typedef const T &const_reference;  //определяет тип постоянной ссылки
  typedef size_t size_type;  // определяет тип размера контейнера (стандартный
                             // тип — size_t)

  /*конструкторы и деструкторы*/
  stack();  // конструктор по умолчанию, создает пустой стек
  ~stack();  // мусоросжигающая печь
  stack(std::initializer_list<value_type> const
            &s); /*конструктор списка инициализаторов, создает стек,
инициализированный с помощью std::initializer_list<T>*/
  stack(const stack &s);  // конструктор копирования
  stack(stack &&s);       // конструктор переноса
  reference operator=(
      stack &&s);  // Перегрузка оператора присваивания для движущегося объекта

  /*В этой таблице перечислены публичные методы для доступа к элементам
   * класса:*/
  const_reference top();  //обращается к верхнему элементу

  /*В этой таблице перечислены публичные методы для доступа к информации о
   * наполнении контейнера:*/
  bool empty() const;  // проверяет, пуст ли контейнер
  size_type size() const;  // возрощает кол-во элементов

  /*В этой таблице перечислены публичные методы для изменения контейнера:*/
  void push(const_reference value);  //вставляет элемент вверху
  void pop();               // удаляет верхний элемент
  void swap(stack &other);  // меняет содержимое

  /*Для отладки*/
  void printStack();
  void swap_stack(stack &&other);
  // добавляет новые элементы в верхнюю часть контейнера
  template <class... Args>
  void emplace_back(Args &&...args);

 private:
  class Node {
   public:
    value_type data_;
    Node *pNext_;
    Node(value_type data_ = value_type(), Node *pNext_ = nullptr) {
      this->data_ = data_;
      this->pNext_ = pNext_;
    }
  };
  Node *head_;
  int size_;
};
}  // namespace s21
#include "s21_stack.cc"
#endif  // SRC_S21_STACK_H_