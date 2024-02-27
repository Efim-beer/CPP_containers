#ifndef SRC_S21_LIST_H_
#define SRC_S21_LIST_H_

#include <initializer_list>
#include <iostream>
#include <limits>
#include <vector>

namespace s21 {

template <typename T>
class list {
 private:
  typedef T value_type;
  typedef T &reference;
  typedef const T &const_reference;
  typedef size_t size_type;

  struct Node {
    value_type data_;
    Node *pPrev_;
    Node *pNext_;
  };

  int size_;
  Node *head_;
  Node *fake_;
  void CreateFake();
  void IncreaseSize();
  void ReferenceToFake();
  void InsertNodeFront(Node *node);
  void InsertNodeBack(Node *node);
  void InsertNodeBeforeCurrent(Node *new_node, Node *current_node);
  void InsertFront(Node *node);
  void InsertBack(Node *node);
  void InsertBeforeCurrent(Node *new_node, Node *current_node);
  void MoveNodeFront(Node *moving_node);
  void MoveNodeBeforeCurrentFromRightToLeft(Node *moving_node,
                                            Node *current_node);
  void MergeSort(Node **node1_start, Node **node2_start);
  void RemoveNode(Node *node);

 public:
  list();
  list(size_type n);
  list(size_type n, value_type x);
  list(std::initializer_list<value_type> const &items);
  list(const list &l);
  list(list &&l);
  ~list();

  typedef class ListIterator {
   protected:
    Node *iter_;

   public:
    ListIterator();
    ListIterator(Node *iter);
    ListIterator(const ListIterator &other) = default;
    ListIterator &operator=(const ListIterator &other);
    reference operator*();
    ListIterator &operator++();
    ListIterator &operator--();
    bool operator==(const ListIterator &other) const;
    bool operator!=(const ListIterator &other) const;
    Node *getNode() const;
  } iterator;
  iterator begin();
  iterator end();

  typedef class ListConstIterator : public ListIterator {
   public:
    ListConstIterator();
    ListConstIterator(Node *iter);
    ListConstIterator(const ListConstIterator &other) = default;
    ListConstIterator &operator=(const ListConstIterator &other);
    const_reference operator*();
    ListConstIterator &operator++();
    ListConstIterator &operator--();
    bool operator==(const ListConstIterator &other) const;
    bool operator!=(const ListConstIterator &other) const;
  } const_iterator;
  const_iterator cbegin() const;
  const_iterator cend() const;

  list<value_type> &operator=(list &&l);

  void pop_front();
  void pop_back();
  void push_back(value_type data);
  void push_front(value_type data);
  void clear();
  bool empty();
  void reverse();
  size_type size();
  const_reference front();
  const_reference back();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  size_type max_size();
  void merge(list &other);
  void splice(const_iterator pos, list &other);
  void swap(list &other);
  void unique();
  void sort();
  void swap_move(list &&other);
  void replace_node(Node &first, Node &second);

  template <class... Args>
  void emplace_back(Args &&...args);

  template <class... Args>
  void emplace_front(Args &&...args);

  template <class... Args>
  iterator emplace(const_iterator pos, Args &&...args);

  /*For debug*/
  void PrintList();
};
}  // namespace s21
#include "s21_list.cc"
#endif  // SRC_S21_LIST_H_
