#ifndef SRC_S21_ARRAY_HH_
#define SRC_S21_ARRAY_HH_

#include <initializer_list>
#include <iostream>
#include <limits>

namespace s21 {

template <typename T, size_t size_>
class array {
 private:
  // В этой таблице перечислены внутриклассовые переопределения типов (типичные
  // для стандартной библиотеки STL), принятые для удобства восприятия кода
  // класса:
  typedef T
      value_type;  //определяет тип заданного параметра (Т - параметр шаблона)
  typedef T &reference;  //определяет тип ссылки на элемент
  typedef const T &const_reference;  // определяет тип постоянной ссылки
  typedef T *iterator;  //определяет тип для итерации через контейнер
  typedef const T
      *const_iterator;  //определяет тип константы для итерации по контейнеру
  typedef size_t
      size_type;  //определяет тип размера контейнера (стандартный тип — size_t)

  value_type head_[size_ ? size_ : 1];

  // В этой таблице перечислены основные публичные методы для взаимодействия с
  // классом:
 public:
  array();  //конструктор по умолчанию, создает пустой массив
  array(std::initializer_list<value_type> const
            &items);  // конструктор списка инициализаторов, создает массив,
  // инициализированный с помощью std::initializer_list<T>
  array(const array &a);  // конструктор копирования
  array(array &&a);       // конструктор перемещения
  ~array();               //мусоросжигательная печь
  void operator=(
      array &&a);  //Перегрузка оператора присваивания для движущегося объекта

  // В этой таблице перечислены публичные методы для доступа к элементам класса:
  reference at(
      size_type pos);  //доступ к указанному элементу с проверкой границ
  reference operator[](size_type pos);  // доступ к указанному элементу
  const_reference front();  //получить доступ к первому элементу
  const_reference back();  //получить доступ к последнему элементу
  value_type *data();  //прямой доступ к базовому массиву

  // В этой таблице перечислены публичные методы для итерирования по элементам
  // класса (доступ к итераторам):
  iterator begin();  //возвращает итератор в начало
  iterator end();    //возвращает итератор в конец

  // В этой таблице перечислены публичные методы для доступа к информации о
  // наполнении контейнера:
  bool empty();      //проверяет, пуст ли контейнер
  size_type size();  //возвращает количество элементов
  size_type max_size();  //возвращает максимально возможное количество элементов

  //В этой таблице перечислены публичные методы для изменения контейнера:
  void swap(array &other);  //меняет содержимое
  void fill(const_reference value);  //присваивает заданное значение value всем
                                     //элементам в контейнере.

  void PrintList();
};
}  // namespace s21
#include "s21_array.cc"
#endif  // SRC_S21_ARRAY_HH_