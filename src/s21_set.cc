#ifndef SRC_S21_SET_CC_
#define SRC_S21_SET_CC_
#include "s21_set.h"

namespace s21 {

template <class value_type>
set<value_type>::set() : root_(nullptr), size_(0) {}

template <class value_type>
set<value_type>::set(std::initializer_list<value_type> const& items) : set() {
  for (auto i = items.begin(); i != items.end(); i++) {
    insert(*i);
  }
}

template <class value_type>
set<value_type>::set(const set& s) : set() {
  iterator iter;
  iter.iter_ = s.root_;
  while (iter.iter_->pLeft_ != nullptr) {
    iter.iter_ = iter.iter_->pLeft_;
  }
  for (size_t i = 0; i < s.size_; i++) {
    this->insert(*iter);
    ++iter;
  }
}

template <class value_type>
set<value_type>::set(set&& s) {
  if (root_ != s.root_) {
    this->root_ = s.root_;
    this->endNode_ = s.endNode_;
    this->size_ = s.size_;
    s.root_ = nullptr;
    s.endNode_ = nullptr;
  }
}

template <class value_type>
void set<value_type>::operator=(set&& s) {
  if (root_ != s.root_) {
    clear();
    this->root_ = s.root_;
    this->endNode_ = s.endNode_;
    this->size_ = s.size_;
    s.root_ = nullptr;
    s.endNode_ = nullptr;
  }
}

template <class value_type>
set<value_type>::~set() {
  if (root_ != nullptr) {
    deleteAllNodes(root_);
    delete endNode_;
    endNode_ = nullptr;
  }
}

//---------------------------------------------------------------------------------------------------------------------------

template <class value_type>
set<value_type>::SetIterator::SetIterator() : iter_(nullptr) {}

template <class value_type>
set<value_type>::SetIterator::SetIterator(Node& iter) : iter_(&iter) {}

template <class value_type>
set<value_type>::SetIterator::SetIterator(const SetIterator& iter)
    : iter_(iter.iter_) {}

template <class value_type>
set<value_type>::SetIterator::~SetIterator() {
  this->iter_ = nullptr;
}

template <class value_type>
typename set<value_type>::SetIterator& set<value_type>::SetIterator::operator=(
    const SetIterator& iter) {
  iter_ = iter.iter_;
  return *this;
}

template <class value_type>
bool set<value_type>::SetIterator::operator==(const SetIterator& iter) const {
  if (iter_ == iter.iter_) {
    return true;
  }
  return false;
}

template <class value_type>
bool set<value_type>::SetIterator::operator!=(const SetIterator& iter) const {
  if (iter_ != iter.iter_) {
    return true;
  }
  return false;
}
template <class value_type>
typename set<value_type>::reference set<value_type>::SetIterator::operator*() {
  return iter_->value_;
}

template <class value_type>
void set<value_type>::SetIterator::operator++() {
  if (iter_ == nullptr) {
    throw std::invalid_argument("iter_ = null pointer (operator++)");
  }
  if (iter_->pRight_ != nullptr) {
    iter_ = iter_->pRight_;
    while (iter_->pLeft_ != nullptr) {
      iter_ = iter_->pLeft_;
    }
  } else {
    Node* rightChild = nullptr;
    do {
      rightChild = iter_;
      iter_ = iter_->parent_;
    } while (iter_->parent_ && iter_->pRight_ == rightChild);
  }
}

template <class value_type>
void set<value_type>::SetIterator::operator--() {
  if (iter_ == nullptr) {
    throw std::invalid_argument("iter_ = null pointer (operator++)");
  }
  if (iter_->pLeft_ != nullptr) {
    iter_ = iter_->pLeft_;
    while (iter_->pRight_ != nullptr) {
      iter_ = iter_->pRight_;
    }
  } else {
    Node* leftChild = nullptr;
    do {
      leftChild = iter_;
      iter_ = iter_->parent_;
    } while (iter_->parent_ && iter_->pLeft_ == leftChild);
  }
}

template <class value_type>
typename set<value_type>::iterator set<value_type>::begin() {
  iterator first_element(*this->root_);
  if (first_element.iter_ != nullptr) {
    while (first_element.iter_->pLeft_ != nullptr) {
      first_element.iter_ = first_element.iter_->pLeft_;
    }
  }
  return first_element;
}

template <class value_type>
typename set<value_type>::iterator set<value_type>::end() {
  iterator after_last(*this->endNode_);
  return after_last;
}

template <class value_type>
typename set<value_type>::const_iterator set<value_type>::cbegin() const {
  const_iterator first_element(*this->begin());
  return first_element;
}

template <class value_type>
typename set<value_type>::const_iterator set<value_type>::cend() const {
  const_iterator last_element(*this->end());
  return last_element;
}

//---------------------------------------------------------------------------------------------------------------------------

template <class value_type>
bool set<value_type>::empty() const {
  return (bool)size_;
}

template <class value_type>
typename set<value_type>::size_type set<value_type>::size() const {
  return size_;
}

template <class value_type>
typename set<value_type>::size_type set<value_type>::max_size() const {
  return (SIZE_MAX / (sizeof(root_) * 3 + sizeof(this->root_->value_)));
}

template <class value_type>
void set<value_type>::clear() {
  deleteAllNodes(root_);
  delete endNode_;
  endNode_ = nullptr;
}

template <class value_type>
std::pair<typename set<value_type>::iterator, bool> set<value_type>::insert(
    const_reference value) {
  std::pair<iterator, bool> resultPair;
  if (root_ == nullptr) {
    root_ = new Node(value);
    size_++;
    createEndNode(root_);
    root_->pRight_ = endNode_;
    resultPair.first.iter_ = root_;
    resultPair.second = true;
  } else {
    size_type size_flag = size();
    resultPair.first.iter_ = addNode(root_, value).iter_;
    if (size_flag != size()) resultPair.second = true;
  }
  return resultPair;
}

template <class value_type>
void set<value_type>::erase(iterator deleteIter) {
  if (deleteIter.iter_ != nullptr) {
    iterator it = deleteOneNode(this->root_, deleteIter.iter_->value_);
    delete it.iter_;
    it.iter_ = nullptr;
    --size_;
  }
}

template <class value_type>
void set<value_type>::swap(set& other) {
  if (root_ != other.root_) {
    std::swap(root_, other.root_);
    std::swap(size_, other.size_);
    std::swap(endNode_, other.endNode_);
  }
}

template <class value_type>
void set<value_type>::merge(set& other) {
  if (root_ != other.root_) {
    iterator iter = other.begin();
    for (size_t i = 0; i < other.size_; i++) {
      insert(*iter);
      ++iter;
    }
    other.clear();
  }
}

template <class value_type>
typename set<value_type>::iterator set<value_type>::find(const_reference key) {
  iterator iter;
  if (this->root_ != nullptr) {
    iter = this->begin();
    for (size_t i = 0; i < this->size_; i++) {
      if (*iter == key) {
        return iter;
      }
      ++iter;
    }
    iter = this->end();
  }
  return iter;
}

template <class value_type>
bool set<value_type>::contains(const_reference key) {
  bool result = false;
  if (find(key) != this->end()) {
    result = true;
  }
  return result;
}

template <class value_type>
template <class... Args>
s21::vector<std::pair<typename set<value_type>::iterator, bool>>
set<value_type>::emplace(Args&&... args) {
  s21::vector<std::pair<typename set<value_type>::iterator, bool>> result;
  s21::vector<value_type> arguments = {args...};
  for (auto& a : arguments) {
    result.push_back(insert(a));
  }
  return result;
}

//---------------------------------------------------------------------------------------------------------------------------

template <class value_type>
typename set<value_type>::iterator set<value_type>::addNode(
    Node* node, const value_type& value) {
  iterator result;
  if (node->value_ == value) {
    result.iter_ = node;
    return result;
  }
  if (node->value_ > value) {
    if (node->pLeft_ != nullptr) {
      result = addNode(node->pLeft_, value);
    } else {
      node->pLeft_ = new Node(value, nullptr, nullptr, node);
      ++size_;
      result.iter_ = node->pLeft_;
    }
  } else if (node->value_ < value) {
    if (node->pRight_ != nullptr && node->pRight_ != endNode_) {
      result = addNode(node->pRight_, value);
    } else {
      if (node->pRight_ == nullptr) {
        node->pRight_ = new Node(value, nullptr, nullptr, node);
        ++size_;
        result.iter_ = node->pRight_;
      } else if (node->pRight_ == endNode_) {
        node->pRight_ = new Node(value, nullptr, endNode_, node);
        ++size_;
        endNode_->parent_ = node->pRight_;
        result.iter_ = node->pRight_;
      }
    }
  }
  return result;
}

template <class value_type>
void set<value_type>::deleteAllNodes(Node*& node) {
  if (node != nullptr && node != endNode_) {
    if (node->pLeft_ != nullptr) {
      deleteAllNodes(node->pLeft_);
    }
    if (node->pRight_ != nullptr) {
      deleteAllNodes(node->pRight_);
    }
    delete node;
    node = nullptr;
    size_ = 0;
  }
}

// template <class value_type>
// void set<value_type>::deleteOneNode(Node* deleteNode, const value_type& key)
// {
//   if (deleteNode != nullptr) {
//     if (deleteNode->value_ == key) {
//       if (deleteNode->pLeft_ == nullptr && deleteNode->pRight_ == nullptr) {
//         delete deleteNode;
//         deleteNode = nullptr;
//         --size_;
//       } else if (deleteNode->pLeft_ != nullptr &&
//                  deleteNode->pRight_ != nullptr) {
//         deleteNode->value_ = getMinimumKey(deleteNode->pRight_);
//         deleteOneNode(deleteNode->pRight_, deleteNode->value_);
//       } else if (deleteNode->pLeft_ != nullptr) {
//         replace(deleteNode, deleteNode->pLeft_);
//         delete deleteNode;
//         deleteNode = nullptr;
//         --size_;
//       } else if (deleteNode->pRight_ != nullptr &&
//                  deleteNode->pRight_ != endNode_) {
//         replace(deleteNode, deleteNode->pRight_);
//         delete deleteNode;
//         deleteNode = nullptr;
//         --size_;
//       } else if (deleteNode->pRight_ == endNode_) {
//         replace(deleteNode, deleteNode->pRight_);
//         delete deleteNode;
//         deleteNode = nullptr;
//         --size_;
//       }
//     } else if (deleteNode->value_ > key) {
//       deleteOneNode(deleteNode->pLeft_, key);
//     } else if (deleteNode->value_ < key) {
//       deleteOneNode(deleteNode->pRight_, key);
//     }
//   }
// }

// template <class value_type>
// void set<value_type>::replace(Node* deleteNode, Node* replaceNode) {
//   Node* temp = deleteNode;

//   delete temp;
//   deleteNode = replaceNode;
//   deleteNode = nullptr;
//   --size_;
// }

template <class value_type>
typename set<value_type>::iterator set<value_type>::deleteOneNode(
    Node* deleteNode, const value_type& key) {
  iterator iter;
  if (deleteNode != nullptr) {
    if (deleteNode->value_ == key) {
      if (deleteNode->pLeft_ == nullptr && deleteNode->pRight_ == nullptr) {
        iter.iter_ = deleteNode;
      } else if (deleteNode->pLeft_ != nullptr &&
                 deleteNode->pRight_ != nullptr) {
        deleteNode->value_ = getMinimumKey(deleteNode->pRight_);
        iter = deleteOneNode(deleteNode->pRight_, deleteNode->value_);
      } else if (deleteNode->pLeft_ != nullptr) {
        iter.iter_ = deleteNode->pLeft_;
        replace(deleteNode, iter.iter_);
      } else if (deleteNode->pRight_ != nullptr) {
        iter.iter_ = deleteNode->pRight_;
        replace(deleteNode, iter.iter_);
      }
    } else if (deleteNode->value_ > key) {
      deleteOneNode(deleteNode->pLeft_, key);
    } else if (deleteNode->value_ < key) {
      deleteOneNode(deleteNode->pRight_, key);
    }
  }
  return iter;
}

template <class value_type>
void set<value_type>::replace(Node* dNode, Node* curNode) {
  dNode->value_ = curNode->value_;
  dNode->pLeft_ = curNode->pLeft_;
  dNode->pRight_ = curNode->pRight_;
}

template <class value_type>
typename set<value_type>::value_type set<value_type>::getMinimumKey(
    Node* curNode) {
  while (curNode->pLeft_ != nullptr) {
    curNode = curNode->pLeft_;
  }
  return curNode->value_;
}

template <class value_type>
void set<value_type>::createEndNode(Node* node) {
  endNode_ = new Node;
  endNode_->value_ = 0;
  endNode_->parent_ = node;
}

}  // namespace s21

#endif  // SRC_S21_SET_CC_