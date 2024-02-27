#ifndef SRC_S21_MAP_H_
#define SRC_S21_MAP_H_
#include <cstring>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <queue>

namespace s21 {

template <typename Key, typename T>
class map {
 private:
  typedef Key key_type;
  typedef T mapped_type;
  typedef std::pair<const Key, T> value_type;
  typedef value_type &reference;
  typedef const value_type &const_reference;
  typedef size_t size_type;
  enum Child { LEFT_CHILD, RIGHT_CHILD };

  class Node {
   public:
    Node(value_type data, Node *parent = nullptr);
    value_type data_;
    Node *parent_;
    Node *left_;
    Node *right_;

    const key_type &GetKey() const;
    mapped_type &GetValue();
    bool IsNodeLeftChild() const;
    bool IsNodeRightChild() const;
  };

  int size_;
  Node *fake_;

  Node *&Root();
  std::pair<bool, Node *> FindPosToInsert(Node *node, const_reference value,
                                          Child &child = Child::LEFT_CHILD);
  void InsertToBlank(Node *&new_node);
  void InsertToNotBlank(Node *&node, const Child &child, const_reference value);
  bool HasNodeLeftChild(Node *&node) const;
  bool HasNodeRightChild(Node *&node) const;
  int HowMuchChildren(Node *&node) const;
  void SwapNodes(Node *&node1, Node *&node2);
  void DeleteNodeLeft(Node *&node);
  void DeleteNodeRight(Node *&node);

  void DeleteAll(Node *node);
  Node *CopyAll(Node *&m_node, const Node *&m_fake, Node *node);
  bool ContainsKey(Node *node, const key_type &key) const;

 public:
  map();
  map(std::initializer_list<value_type> const &items);
  map(const map &m);
  map(map &&m);
  ~map();
  void operator=(map &&m);

  typedef class MapIterator {
   protected:
    const map *obj_;

   public:
    Node *iter_;
    MapIterator();
    MapIterator(Node *&iter, const map &obj);
    MapIterator(const MapIterator &it) = default;
    ~MapIterator() = default;
    MapIterator &operator=(const MapIterator &other);
    reference operator*();
    value_type *operator->();
    MapIterator &operator++();
    MapIterator operator++(int);
    MapIterator &operator--();
    bool operator==(const MapIterator &other) const;
    bool operator!=(const MapIterator &other) const;

  } iterator;

  iterator begin();
  iterator end();

  T &at(const key_type &key);
  T &operator[](const key_type &key);

  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  void clear();
  std::pair<iterator, bool> insert(const_reference value);
  std::pair<iterator, bool> insert(const key_type &key, const mapped_type &obj);
  std::pair<iterator, bool> insert_or_assign(const key_type &key,
                                             const mapped_type &obj);
  void erase(iterator pos);
  void swap(map &other);
  void merge(map &other);

  bool contains(const key_type &key) const;

  template <class... Args>
  std::vector<std::pair<iterator, bool>> emplace(Args &&...args);

 private:
  std::pair<iterator, bool> UniversalInsert(const_reference value,
                                            bool is_assign);
};
}  // namespace s21
#include "s21_map.cc"
#endif  // SRC_S21_MAP_H_
