#ifndef SRC_S21_QUEUE_H_
#define SRC_S21_QUEUE_H_
#include <initializer_list>
#include <iostream>
#include <set>
#include <vector>

namespace s21 {
template <typename T>
class queue {
 public:
  //  В этой таблице перечислены внутриклассовые
  //   переопределения типов (типичные для стандартной библиотеки STL), принятые
  //   для удобства восприятия кода класса:
  typedef T value_type;  // параметр шаблона T
  typedef T &reference;  // определяет тип ссылки на элемент
  typedef const T &const_reference;  // определяет тип постоянной ссылки
  typedef size_t size_type;  // определяет тип размера контейнера (стандартный
                             // тип — size_t)
  //   В этой таблице перечислены основные публичные методы для взаимодействия с
  //   классом:
  queue();  //конструктор по умолчанию, создает пустую очередь
  queue(std::initializer_list<value_type> const
            &items);  //конструктор списка инициализаторов,
  //создает очередь, инициализированную с помощью std::initializer_list<T>
  queue(const queue &q);  //конструктор копирования
  queue(queue &&q);       //конструктор переноса
  ~queue();               //мусоросжигающая печь
  reference operator=(
      queue &&q);  // Перегрузка оператора присваивания для движущегося объекта

  const_reference front();  // получить доступ к первому элементу
  const_reference back();  // получить доступ к последниму элементу элементу

  bool empty() const;  //проверяет, пуст ли контейнер
  size_type size() const;  // возвращает количество элементов
  size_type max_size() const;  // возвращает максимальное количество элементов

  void push(const_reference value);  //вставляет элемент в конце
  void pop();               // удаляет первый элемент
  void swap(queue &other);  // меняет содержимое
  template <class... Args>
  void emplace_back(Args &&...args);  //поместить  назад

  /*For debug*/
  reference operator[](const int index);
  void swap_queue(queue &&other);
  void PrintQ();

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

  Node *first_;
  Node *last_;
  int size_;
};
}  // namespace s21
#include "s21_queue.cc"
#endif  // SRC_S21_QUEUE_H_
