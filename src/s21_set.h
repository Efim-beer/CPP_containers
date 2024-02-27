#ifndef SRC_S21_SET_H_
#define SRC_S21_SET_H_
#include <initializer_list>
#include <iostream>
#include <set>

#include "s21_vector.h"

namespace s21 {
template <class Key>
class set {
 public:
  typedef Key key_type;
  typedef key_type value_type;
  typedef key_type& reference;
  typedef const key_type& const_reference;
  typedef size_t size_type;

  set();
  set(std::initializer_list<key_type> const& items);
  set(const set& s);
  set(set&& s);
  ~set();
  void operator=(set&& s);

  class Node {
   public:
    value_type value_;
    Node* pLeft_;
    Node* pRight_;
    Node* parent_;
    Node(value_type value = value_type(), Node* pLeft = nullptr,
         Node* pRight = nullptr, Node* parent = nullptr)
        : value_{value}, pLeft_(pLeft), pRight_(pRight), parent_(parent) {}
  };

  typedef class SetIterator {
   public:
    Node* iter_;

    SetIterator();
    SetIterator(Node& iter);
    SetIterator(const SetIterator& iter);
    ~SetIterator();

    SetIterator& operator=(const SetIterator& iter);
    bool operator==(const SetIterator& iter) const;
    bool operator!=(const SetIterator& iter) const;
    reference operator*();
    void operator++();
    void operator--();
  } iterator;
  iterator begin();
  iterator end();

  typedef const SetIterator const_iterator;
  const_iterator cbegin() const;
  const_iterator cend() const;

  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  void clear();

  std::pair<iterator, bool> insert(const value_type& value);

  bool contains(const_reference key);

  iterator find(const_reference key);

  void erase(iterator pos);

  void swap(set& other);

  void merge(set& other);

  void deleteAllNode(Node*& dNode);

  template <class... Args>
  s21::vector<std::pair<iterator, bool>> emplace(Args&&... args);

 protected:
  Node* root_{};
  Node* endNode_;
  size_type size_;
  void createEndNode(Node* node);
  iterator addNode(Node* addNode, const value_type& value);
  void deleteAllNodes(Node*& Node);
  iterator deleteOneNode(Node* deleteNode, const value_type& key);
  value_type getMinimumKey(Node* Node);
  void replace(Node* deleteNode, Node* replaceNode);
};
}  // namespace s21
#include "s21_set.cc"
#endif  // SRC_S21_SET_H_
