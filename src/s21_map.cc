#ifndef SRC_S21_MAP_CC_
#define SRC_S21_MAP_CC_
#include "s21_map.h"

namespace s21 {

template <typename Key, typename T>
map<Key, T>::map() : size_(0) {
  fake_ = new Node({key_type(), mapped_type()});
  fake_->left_ = fake_->right_ = fake_;
}

template <typename Key, typename T>
map<Key, T>::map(std::initializer_list<value_type> const &items) : map() {
  for (const_reference val : items) insert(val);
}

template <typename Key, typename T>
map<Key, T>::map(const map &m) : map() {
  if (this != &m) {
    if (m.size_) {
      Node *new_node = nullptr;
      Node *m_node = m.fake_->parent_;
      const Node *m_fake = m.fake_;
      fake_->parent_ = CopyAll(m_node, m_fake, new_node);
      size_ = m.size_;
    }
  }
}

template <typename Key, typename T>
typename map<Key, T>::Node *map<Key, T>::CopyAll(Node *&m_node,
                                                 const Node *&m_fake,
                                                 Node *node) {
  if (!m_node) return nullptr;
  if (m_node == m_fake) return fake_;
  Node *parent = node;
  node = new Node(m_node->data_);
  node->left_ = CopyAll(m_node->left_, m_fake, node);
  if (node->left_ == fake_) {
    fake_->left_ = node;
  }
  node->right_ = CopyAll(m_node->right_, m_fake, node);
  if (node->right_ == fake_) {
    fake_->right_ = node;
  }
  node->parent_ = parent;
  return node;
}

template <typename Key, typename T>
map<Key, T>::map(map &&m) : map() {
  if (this != &m) swap(m);
}

template <typename Key, typename T>
map<Key, T>::~map() {
  clear();
  delete fake_;
}

template <typename Key, typename T>
void map<Key, T>::operator=(map &&m) {
  if (this != &m) {
    clear();
    swap(m);
  }
}

template <typename Key, typename T>
map<Key, T>::Node::Node(value_type data, Node *parent)
    : data_{data}, parent_{parent}, left_{nullptr}, right_{nullptr} {}

template <typename Key, typename T>
map<Key, T>::MapIterator::MapIterator() : obj_{nullptr}, iter_{nullptr} {}

template <typename Key, typename T>
map<Key, T>::MapIterator::MapIterator(Node *&iter, const map &obj)
    : obj_{&obj}, iter_{iter} {}

template <typename Key, typename T>
typename map<Key, T>::MapIterator &map<Key, T>::iterator::operator=(
    const MapIterator &other) {
  this->iter_ = other.iter_;
  this->obj_ = other.obj_;
  return *this;
}

template <typename Key, typename T>
typename map<Key, T>::reference map<Key, T>::iterator::operator*() {
  return iter_->data_;
}

template <typename Key, typename T>
typename map<Key, T>::value_type *map<Key, T>::iterator::operator->() {
  return &operator*();
}

template <typename Key, typename T>
typename map<Key, T>::MapIterator &map<Key, T>::iterator::operator++() {
  if (iter_->right_) {
    iter_ = iter_->right_;
    while (iter_ != obj_->fake_ && iter_->left_) iter_ = iter_->left_;
  } else {
    Node *right_child = nullptr;
    do {
      right_child = iter_;
      iter_ = iter_->parent_;
    } while (iter_->parent_ && iter_->right_ == right_child);
  }
  return *this;
}

template <typename Key, typename T>
typename map<Key, T>::MapIterator map<Key, T>::iterator::operator++(int) {
  iterator tmp(*this);
  operator++();
  return tmp;
}

template <typename Key, typename T>
typename map<Key, T>::MapIterator &map<Key, T>::iterator::operator--() {
  if (iter_ == obj_->fake_) {
    iter_ = obj_->fake_->right_;
  } else if (iter_->left_) {
    iter_ = iter_->left_;
    while (iter_ != obj_->fake_ && iter_->right_) {
      iter_ = iter_->right_;
    }
  } else {
    Node *left_child = nullptr;
    do {
      left_child = iter_;
      iter_ = iter_->parent_;
    } while (iter_->parent_ && iter_->left_ == left_child);
  }
  return *this;
}

template <typename Key, typename T>
bool map<Key, T>::iterator::operator==(const MapIterator &other) const {
  return iter_ == other.iter_;
}

template <typename Key, typename T>
bool map<Key, T>::iterator::operator!=(const MapIterator &other) const {
  return iter_ != other.iter_;
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::begin() {
  if (!empty()) return iterator(fake_->left_, *this);
  return end();
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::end() {
  return iterator(this->fake_, *this);
}

template <typename Key, typename T>
typename map<Key, T>::mapped_type &map<Key, T>::at(const key_type &key) {
  if (size_) {
    Child child = Child::LEFT_CHILD;
    std::pair<bool, Node *> res_pair =
        FindPosToInsert(Root(), std::make_pair(key, mapped_type()), child);
    if (!res_pair.first) return res_pair.second->GetValue();
  }
  throw std::out_of_range("Out of range");
}

template <typename Key, typename T>
typename map<Key, T>::mapped_type &map<Key, T>::operator[](
    const key_type &key) {
  return insert(std::make_pair(key, mapped_type())).first->second;
}

template <typename Key, typename T>
bool map<Key, T>::empty() const {
  return !size_;
}

template <typename Key, typename T>
typename map<Key, T>::size_type map<Key, T>::size() const {
  return size_;
}

template <typename Key, typename T>
typename map<Key, T>::size_type map<Key, T>::max_size() const {
  return std::numeric_limits<int64_t>::max() / sizeof(Node);
}

template <typename Key, typename T>
void map<Key, T>::clear() {
  DeleteAll(fake_->parent_);
  size_ = 0;
  fake_->parent_ = fake_->left_ = fake_->right_ = nullptr;
}

template <typename Key, typename T>
void map<Key, T>::DeleteAll(Node *node) {
  if (!node || node == fake_) return;
  DeleteAll(node->left_);
  DeleteAll(node->right_);
  delete node;
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
    const_reference value) {
  return UniversalInsert(value, false);
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
    const key_type &key, const mapped_type &obj) {
  return insert(std::make_pair(key, obj));
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert_or_assign(
    const key_type &key, const mapped_type &obj) {
  return UniversalInsert(std::make_pair(key, obj), true);
}

template <typename Key, typename T>
std::pair<bool, typename map<Key, T>::Node *> map<Key, T>::FindPosToInsert(
    Node *node, const_reference value, map<Key, T>::Child &child) {
  key_type key = node->GetKey();
  if (value.first == key) {
    return {false, node};
  }
  if (value.first < key) {
    if (!node->left_ || node->left_ == fake_) {
      return {true, node};
    }
    node = node->left_;
  } else {
    if (!node->right_ || node->right_ == fake_) {
      child = Child::RIGHT_CHILD;
      return {true, node};
    }
    node = node->right_;
  }
  return FindPosToInsert(node, value, child);
}

template <typename Key, typename T>
void map<Key, T>::InsertToBlank(Node *&new_node) {
  new_node->left_ = new_node->right_ = fake_;
  Root() = fake_->left_ = fake_->right_ = new_node;
  ++size_;
}

template <typename Key, typename T>
void map<Key, T>::InsertToNotBlank(Node *&node, const Child &child,
                                   const_reference value) {
  Node *new_node = new Node(value, node);
  if (child == Child::LEFT_CHILD) {
    if (node == fake_->left_) {
      fake_->left_ = new_node;
      new_node->left_ = fake_;
    }
    node->left_ = new_node;
  } else {
    if (node->right_ == fake_) {
      new_node->right_ = fake_;
      fake_->right_ = new_node;
    }
    node->right_ = new_node;
  }
  node = new_node;
  ++size_;
}

template <typename Key, typename T>
void map<Key, T>::erase(iterator pos) {
  if (size_ == 1) {
    fake_->left_ = fake_->right_ = nullptr;
    delete fake_->parent_;
    fake_->parent_ = nullptr;
    size_ = 0;
    return;
  }
  Node *node = pos.iter_;
  if (!node || node == fake_)
    throw std::runtime_error("Node for erase is NULL");
  int mask_count_children = HowMuchChildren(node);
  if (mask_count_children == 0b10) {
    SwapNodes(node, node->left_);
    return;
  } else if (mask_count_children == 0b01) {
    SwapNodes(node, node->right_);
    return;
  } else if (mask_count_children == 0b11) {
    Node *next_node = (++pos).iter_;
    if (node == Root()) {
      fake_->parent_ = next_node;
    } else if (node->IsNodeLeftChild()) {
      node->parent_->left_ = next_node;
    } else {
      node->parent_->right_ = next_node;
    }
    if (next_node->left_ && next_node->left_ != fake_)
      next_node->left_->parent_ = node;

    if (next_node->right_ && next_node->right_ != fake_)
      next_node->right_->parent_ = node;
    if (node == next_node->right_) {
      node->right_ = next_node->right_;
      next_node->right_ = node;
      next_node->parent_ = node->parent_;
      node->parent_ = next_node;
      std::swap(node->left_, next_node->left_);
    } else {
      Node *node_left = node->left_;
      Node *node_right = node->right_;
      Node *next_node_parent = next_node->parent_;
      std::swap(node->left_, next_node->left_);
      std::swap(node->right_, next_node->right_);
      std::swap(node->parent_, next_node->parent_);
      node_left->parent_ = next_node;
      node_right->parent_ = next_node;
      next_node_parent->left_ = node;
    }
  }
  if (node->IsNodeLeftChild())
    DeleteNodeLeft(node->parent_);
  else
    DeleteNodeRight(node->parent_);
}

template <typename Key, typename T>
void map<Key, T>::DeleteNodeLeft(Node *&node) {
  Node *child = node->left_;
  if (child->left_ == fake_) {
    fake_->left_ = node;
    node->left_ = fake_;
  } else {
    node->left_ = nullptr;
  }
  delete child;
  --size_;
}

template <typename Key, typename T>
void map<Key, T>::DeleteNodeRight(Node *&node) {
  Node *child = node->right_;
  if (child->right_ == fake_) {
    fake_->right_ = node;
    node->right_ = fake_;
  } else {
    node->right_ = nullptr;
  }
  delete child;
  --size_;
}

template <typename Key, typename T>
void map<Key, T>::SwapNodes(Node *&node1, Node *&node2) {
  if (node1->left_ == fake_ || node1->right_ == fake_) {
    if (node1->left_ == fake_) {
      node2->left_ = fake_;
      fake_->left_ = node2;
    } else {
      node2->right_ = fake_;
      fake_->right_ = node2;
    }
  }
  if (node1 == Root())
    fake_->parent_ = node2;
  else if (node1->IsNodeLeftChild())
    node1->parent_->left_ = node2;
  else
    node1->parent_->right_ = node2;
  node2->parent_ = node1->parent_;
  delete node1;
  --size_;
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::UniversalInsert(
    const_reference value, bool is_assign) {
  if (size_) {
    Child child = Child::LEFT_CHILD;
    std::pair<bool, Node *> res_pair = FindPosToInsert(Root(), value, child);
    bool res = res_pair.first;
    Node *node = res_pair.second;
    if (res) {
      InsertToNotBlank(node, child, value);
    } else if (is_assign) {
      node->GetValue() = value.second;
    }
    return {iterator(node, *this), res};
  } else {
    Node *new_node = new Node(value);
    InsertToBlank(new_node);
    return {iterator(new_node, *this), true};
  }
}

template <typename Key, typename T>
bool map<Key, T>::Node::IsNodeLeftChild() const {
  if (!parent_) throw std::runtime_error("Parent is NULL");
  return this == parent_->left_;
}

template <typename Key, typename T>
bool map<Key, T>::Node::IsNodeRightChild() const {
  return !IsNodeLeftChild();
}

template <typename Key, typename T>
bool map<Key, T>::HasNodeLeftChild(Node *&node) const {
  return node->left_ && node->left_ != fake_;
}

template <typename Key, typename T>
bool map<Key, T>::HasNodeRightChild(Node *&node) const {
  return node->right_ && node->right_ != fake_;
}

template <typename Key, typename T>
int map<Key, T>::HowMuchChildren(Node *&node) const {
  return (HasNodeLeftChild(node) << 1) + HasNodeRightChild(node);
}

template <typename Key, typename T>
typename map<Key, T>::Node *&map<Key, T>::Root() {
  return fake_->parent_;
}

template <typename Key, typename T>
const typename map<Key, T>::key_type &map<Key, T>::Node::GetKey() const {
  return data_.first;
}

template <typename Key, typename T>
typename map<Key, T>::mapped_type &map<Key, T>::Node::GetValue() {
  return data_.second;
}

template <typename Key, typename T>
void map<Key, T>::swap(map &other) {
  std::swap(fake_, other.fake_);
  std::swap(size_, other.size_);
}

template <typename Key, typename T>
void map<Key, T>::merge(map &other) {
  iterator other_it = other.begin();
  iterator other_it_end = other.end();
  while (other_it != other_it_end) {
    auto res = insert(*other_it);
    if (res.second) {
      other.erase(other_it++);
    } else {
      ++other_it;
    }
  }
}

template <typename Key, typename T>
bool map<Key, T>::contains(const key_type &key) const {
  return ContainsKey(fake_->parent_, key);
}

template <typename Key, typename T>
template <class... Args>
std::vector<std::pair<typename map<Key, T>::iterator, bool>>
map<Key, T>::emplace(Args &&...args) {
  std::vector<std::pair<iterator, bool>> result;
  std::vector<value_type> arguments = {args...};
  for (const auto &val : arguments) {
    result.push_back(insert(val));
  }
  return result;
}

template <typename Key, typename T>
bool map<Key, T>::ContainsKey(Node *node, const key_type &key) const {
  if (!node || node == fake_) return false;
  key_type this_key = node->GetKey();
  if (key == this_key)
    return true;
  else if (key > this_key)
    return ContainsKey(node->right_, key);
  else
    return ContainsKey(node->left_, key);
}

}  // namespace s21

#endif  // SRC_S21_MAP_CC_