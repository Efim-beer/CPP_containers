#ifndef SRC_S21_MULTISET_CC_
#define SRC_S21_MULTISET_CC_
#include "s21_multiset.h"

namespace s21 {

template <class value_type>
multiset<value_type>::multiset() : set<value_type>::set() {}

template <class value_type>
multiset<value_type>::multiset(const multiset<value_type>& other)
    : set<value_type>::set(other) {}

template <class value_type>
multiset<value_type>::multiset(multiset<value_type>&& other)
    : set<value_type>::set(other) {}

template <class value_type>
multiset<value_type>::multiset(std::initializer_list<value_type> const& items) {
  for (auto& i : items) {
    insert(i);
  }
}

template <class value_type>
multiset<value_type>::~multiset() {}

template <class value_type>
typename multiset<value_type>::iterator multiset<value_type>::insert(
    const_reference value) {
  iterator iterResult;
  if (this->root_ == nullptr) {
    this->root_ = new NodeSet(value);
    ++this->size_;
    this->createEndNode(this->root_);
    this->root_->pRight_ = this->endNode_;
    iterResult.iter_ = this->root_;
  } else {
    iterResult = addNode(this->root_, value);
  }
  return iterResult;
}

template <class value_type>
typename multiset<value_type>::iterator multiset<value_type>::addNode(
    NodeSet* node, const value_type& key) {
  iterator result;
  if (node->value_ > key) {
    if (node->pLeft_ != nullptr) {
      result = addNode(node->pLeft_, key);
    } else {
      node->pLeft_ = new NodeSet(key, nullptr, nullptr, node);
      ++this->size_;
      result.iter_ = node->pLeft_;
    }
  } else if (node->value_ <= key) {
    if (node->pRight_ != nullptr && node->pRight_ != this->endNode_) {
      result = addNode(node->pRight_, key);
    } else {
      if (node->pRight_ == nullptr) {
        node->pRight_ = new NodeSet(key, nullptr, nullptr, node);
        ++this->size_;
        result.iter_ = node->pRight_;
      } else if (node->pRight_ == this->endNode_) {
        node->pRight_ = new NodeSet(key, nullptr, this->endNode_, node);
        ++this->size_;
        this->endNode_->parent_ = node->pRight_;
        result.iter_ = node->pRight_;
      }
    }
  }
  return result;
}

template <class value_type>
typename multiset<value_type>::iterator multiset<value_type>::upper_bound(
    const value_type& key) {
  iterator iterResult;
  iterResult = this->find(key);
  if (iterResult == this->end()) {
    if (key < *this->begin()) {
      iterResult = this->begin();
    } else {
      iterResult = this->begin();
      while (key >= *iterResult && iterResult.iter_ != nullptr) {
        ++iterResult;
      }
    }
  } else {
    auto temp = *iterResult;
    ++iterResult;
    auto result = *iterResult;
    while (temp == result) {
      ++iterResult;
      result = *iterResult;
    }
  }
  return iterResult;
}

template <class value_type>
typename multiset<value_type>::iterator multiset<value_type>::lower_bound(
    const value_type& key) {
  iterator iterResult;
  iterResult = this->find(key);
  if (iterResult == this->end()) {
    if (key < *this->begin()) {
      iterResult = this->begin();
    } else {
      iterResult = this->begin();
      while (key > *iterResult) {
        ++iterResult;
      }
    }
  }
  return iterResult;
}

template <class value_type>
void multiset<value_type>::erase(const value_type& key) {
  while (this->find(key) != this->end()) {
    iterator it = this->deleteOneNode(this->root_, key);
    delete it.iter_;
    it.iter_ = nullptr;
    --this->size_;
  }
}

template <class value_type>
void multiset<value_type>::erase(iterator deleteIter) {
  if (deleteIter.iter_ != nullptr) {
    iterator it = this->deleteOneNode(this->root_, deleteIter.iter_->value_);
    delete it.iter_;
    it.iter_ = nullptr;
    --this->size_;
  }
}

template <class value_type>
typename multiset<value_type>::size_type multiset<value_type>::count(
    const value_type& key) {
  size_type count = 0;
  if (this->contains(key)) {
    iterator it = this->find(key);
    while (*it == key) {
      ++count;
      ++it;
    }
  }
  return count;
}

template <class value_type>
std::pair<typename multiset<value_type>::iterator,
          typename multiset<value_type>::iterator>
multiset<value_type>::equal_range(const value_type& key) {
  return std::pair<iterator, iterator>(lower_bound(key), upper_bound(key));
}

template <class value_type>
template <class... Args>
typename multiset<value_type>::iterator multiset<value_type>::emplace(
    Args&&... args) {
  iterator result;
  std::vector<value_type> arguments = {args...};
  for (auto& a : arguments) {
    result = insert(a);
  }
  return result;
}

}  // namespace s21

#endif  // SRC_S21_MULTISET_CC_