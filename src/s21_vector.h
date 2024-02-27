#ifndef SRC_S21_VECTOR_H_
#define SRC_S21_VECTOR_H_
#include <initializer_list>
#include <limits>

namespace s21 {

template <typename T>
class vector {
 private:
  typedef T value_type;
  typedef T &reference;
  typedef const T &const_reference;
  typedef size_t size_type;

  size_type size_;
  size_type capacity_;
  value_type *head_;

  void InitMemory();
  void IncreaseCapacity();
  void CopyVector(value_type *dst, value_type *src);
  void ReserveWithoutCheck();

 public:
  vector();
  vector(size_type n);
  vector(size_type n, value_type x);
  vector(std::initializer_list<value_type> const &items);
  vector(const vector &v);
  vector(vector &&v);
  ~vector();
  void operator=(vector &&v);

  typedef class VectorIterator {
   protected:
    value_type *iter_;

   public:
    VectorIterator();
    VectorIterator(value_type *iter);
    reference operator*();
    void operator++();
    void operator--();
    bool operator==(const VectorIterator &other) const;
    bool operator!=(const VectorIterator &other) const;
    value_type *base();
  } iterator;

  typedef const VectorIterator const_iterator;

  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  value_type *data();

  iterator begin();
  iterator end();

  const_iterator cbegin();
  const_iterator cend();

  bool empty();
  size_type size();
  size_type max_size();
  void reserve(size_type size);
  size_type capacity();
  void shrink_to_fit();

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector &other);

  template <typename... Args>
  iterator emplace(const_iterator pos, Args &&...args);

  template <typename... Args>
  void emplace_back(Args &&...args);
};
}  // namespace s21
#include "s21_vector.cc"
#endif  // SRC_S21_VECTOR_H_
