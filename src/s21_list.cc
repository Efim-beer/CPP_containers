#ifndef SRC_S21_LIST_CC_
#define SRC_S21_LIST_CC_
#include "s21_list.h"

namespace s21 {
/*Конструкторы, деструкторы ************************************/

template <class value_type>
list<value_type>::list() : list(0, value_type()) {}

template <class value_type>
list<value_type>::list(size_type n) : list(n, value_type()) {}

template <class value_type>
list<value_type>::list(size_type n, value_type x) : size_{0} {
  CreateFake();
  for (size_type i = 0; i < n; i++) push_back(x);
}

template <class value_type>
list<value_type>::list(std::initializer_list<value_type> const &items)
    : list(0, 0) {
  for (const_reference val : items) {
    push_back(val);
  }
}

/* Copy Constructor*/
template <class value_type>
list<value_type>::list(const list &l) : list(0, 0) {
  if (this != &l) {
    const_iterator iter = l.cbegin();
    const_iterator iter_end = l.cend();
    for (; iter != iter_end; ++iter) {
      push_back(*iter);
    }
  }
}

/* Move Constructor*/

template <class value_type>
list<value_type>::list(list &&l) : list(0, 0) {
  if (this != &l) {
    std::swap(head_, l.head_);
    std::swap(fake_, l.fake_);
    std::swap(size_, l.size_);
  }
}

/* мусоросжигающая печь*/
template <class value_type>
list<value_type>::~list() {
  while (size_) {
    pop_front();
  }
  delete fake_;
}

/* список итераторов*/
template <class value_type>
list<value_type>::ListIterator::ListIterator() : iter_{nullptr} {}

/* обнуление*/
template <class value_type>
list<value_type>::ListIterator::ListIterator(Node *iter) : iter_{iter} {}

/* ну я так понимаю присваивание одного итерала узла другому*/
template <class value_type>
typename list<value_type>::ListIterator &list<value_type>::iterator::operator=(
    const ListIterator &other) {
  if (this->iter_ != other.iter_) {
    this->iter_ = other.iter_;
  }
  return *this;
}

template <class value_type>
typename list<value_type>::reference list<value_type>::iterator::operator*() {
  return iter_->data_;
}

template <class value_type>
typename list<value_type>::ListIterator &
list<value_type>::iterator::operator++() {
  iter_ = iter_->pNext_;
  return *this;
}

template <class value_type>
typename list<value_type>::ListIterator &
list<value_type>::iterator::operator--() {
  iter_ = iter_->pPrev_;
  return *this;
}

template <class value_type>
bool list<value_type>::iterator::operator==(const ListIterator &other) const {
  return iter_ == other.iter_;
}

template <class value_type>
bool list<value_type>::iterator::operator!=(const ListIterator &other) const {
  return iter_ != other.iter_;
}

/*получить узел*/
template <class value_type>
typename list<value_type>::Node *list<value_type>::iterator::getNode() const {
  return list<value_type>::iterator::iter_;
}

/*начинать*/
template <class value_type>
typename list<value_type>::iterator list<value_type>::begin() {
  return iterator(this->head_);
}

/*конец*/
template <class value_type>
typename list<value_type>::iterator list<value_type>::end() {
  return iterator(this->fake_);
}

/*список интералов*/
template <class value_type>
list<value_type>::ListConstIterator::ListConstIterator() : ListIterator() {}

template <class value_type>
list<value_type>::ListConstIterator::ListConstIterator(Node *iter)
    : ListIterator{iter} {}

template <class value_type>
typename list<value_type>::ListConstIterator &
list<value_type>::const_iterator::operator=(const ListConstIterator &other) {
  if (ListIterator::iter_ != other.iter_) {
    clear();
    ListIterator::iter_ = other.iter_;
  }
  return *this;
}

template <class value_type>
typename list<value_type>::const_reference
list<value_type>::const_iterator::operator*() {
  return ListIterator::iter_->data_;
}

template <class value_type>
typename list<value_type>::ListConstIterator &
list<value_type>::const_iterator::operator++() {
  ListIterator::iter_ = ListIterator::iter_->pNext_;
  return *this;
}

template <class value_type>
typename list<value_type>::ListConstIterator &
list<value_type>::const_iterator::operator--() {
  ListIterator::iter_ = ListIterator::iter_->pPrev_;
  return *this;
}

template <class value_type>
bool list<value_type>::const_iterator::operator==(
    const ListConstIterator &other) const {
  return ListIterator::iter_ == other.iter_;
}

template <class value_type>
bool list<value_type>::const_iterator::operator!=(
    const ListConstIterator &other) const {
  return ListIterator::iter_ != other.iter_;
}

template <class value_type>
list<value_type> &list<value_type>::operator=(list &&l) {
  head_ = l.head_;
  fake_ = l.fake_;
  size_ = l.size_;
  l.head_ = l.fake_ = nullptr;
  l.size_ = 0;
  return *this;
}

/*********************************************************************************/

/*c начало*/
template <class value_type>
typename list<value_type>::const_iterator list<value_type>::cbegin() const {
  return const_iterator(this->head_);
}

/*с конца*/
template <class value_type>
typename list<value_type>::const_iterator list<value_type>::cend() const {
  return const_iterator(this->fake_);
}

/*********************************************************************************/

/*Создать подделку*/
template <class value_type>
void list<value_type>::CreateFake() {
  fake_ = new Node;
  fake_->data_ = 0;
  head_ = fake_->pNext_ = fake_->pPrev_ = fake_;
}

/*Увеличить размер*/
template <class value_type>
void list<value_type>::IncreaseSize() {
  size_++;
  fake_->data_++;
}

/*вставить узел вперёд*/
template <class value_type>
void list<value_type>::InsertNodeFront(Node *node) {
  node->pPrev_ = fake_;
  node->pNext_ = head_;
  if (head_ == fake_) {
    fake_->pPrev_ = node;
  } else {
    head_->pPrev_ = node;
  }
  head_ = node;
}

/*Вставить узел назад*/
template <class value_type>
void list<value_type>::InsertNodeBack(Node *node) {
  node->pNext_ = fake_;
  node->pPrev_ = fake_->pPrev_;
  if (head_ == fake_) {
    head_ = node;
    fake_->pNext_ = head_;
  } else {
    fake_->pPrev_->pNext_ = node;
  }
  fake_->pPrev_ = node;
}

/*Вставить узел перед текущим*/
template <class value_type>
void list<value_type>::InsertNodeBeforeCurrent(Node *new_node,
                                               Node *current_node) {
  new_node->pNext_ = current_node;
  new_node->pPrev_ = current_node->pPrev_;
  current_node->pPrev_->pNext_ = new_node;
  current_node->pPrev_ = new_node;
}

/*вставить вперед*/
template <class value_type>
void list<value_type>::InsertFront(Node *node) {
  InsertNodeFront(node);
  fake_->pNext_ = head_;
  IncreaseSize();
}

/*Вставить Назад*/
template <class value_type>
void list<value_type>::InsertBack(Node *node) {
  InsertNodeBack(node);
  IncreaseSize();
}

/*вставить перед текущим*/
template <class value_type>
void list<value_type>::InsertBeforeCurrent(Node *new_node, Node *current_node) {
  InsertNodeBeforeCurrent(new_node, current_node);
  IncreaseSize();
}

/*переместить ущел спереди*/
template <class value_type>
void list<value_type>::MoveNodeFront(Node *moving_node) {
  moving_node->pPrev_->pNext_ = moving_node->pNext_;
  moving_node->pNext_->pPrev_ = moving_node->pPrev_;
  InsertNodeFront(moving_node);
}

/*Переместить узел перед текущим справа налево*/
template <class value_type>
void list<value_type>::MoveNodeBeforeCurrentFromRightToLeft(
    Node *moving_node, Node *current_node) {
  moving_node->pPrev_->pNext_ = moving_node->pNext_;
  moving_node->pNext_->pPrev_ = moving_node->pPrev_;
  InsertNodeBeforeCurrent(moving_node, current_node);
}

/*Сортировка слиянием*/
template <class value_type>
void list<value_type>::MergeSort(Node **node1_start, Node **node2_start) {
  Node *node1 = *node1_start;
  Node *node2 = *node2_start;

  do {
    if (node1 == fake_ || node2->data_ < node1->data_) {
      // перемещение node_2 перед node_1
      Node *node2_pNext = node2->pNext_;
      if (node1 == head_) {
        MoveNodeFront(node2);
      } else if (node1 != fake_) {
        MoveNodeBeforeCurrentFromRightToLeft(node2, node1);
      }
      if (node2_pNext->data_ < node2->data_) {
        *node1_start = node2_pNext;
        break;
      } else {
        *node2_start = node2 = node2_pNext;
      }
    } else {
      node1 = node1->pNext_;
    }
  } while (node2 != fake_ && node1 != *node2_start);
  if (node1 == *node2_start) *node1_start = node1->pNext_;
}

/*Удалить узел*/
template <class value_type>
void list<value_type>::RemoveNode(Node *node) {
  if (node == fake_)
    throw std::invalid_argument("double free or corruption (out)");
  if (node == head_) {
    pop_front();
  } else if (node == fake_->pPrev_) {
    pop_back();
  } else {
    node->pPrev_->pNext_ = node->pNext_;
    node->pNext_->pPrev_ = node->pPrev_;
    delete node;
    size_--;
    fake_->data_--;
  }
}

/********************************************************************************/

/* удаляет первый элемент*/
template <class value_type>
void list<value_type>::pop_front() {
  if (head_ == fake_)
    throw std::invalid_argument("pointer being freed was not allocated");
  Node *temp = head_->pNext_;
  delete head_;
  head_ = temp;
  head_->pPrev_ = fake_;
  fake_->pNext_ = temp;
  size_--;
  fake_->data_--;
}

/*удалять последний элемент*/
template <class value_type>
void list<value_type>::pop_back() {
  if (fake_->pPrev_ == fake_)
    throw std::invalid_argument("pointer being freed was not allocated");
  Node *temp = fake_->pPrev_->pPrev_;
  delete fake_->pPrev_;
  temp->pNext_ = fake_;
  if (size_ == 2)
    head_->pNext_ = fake_;
  else if (size_ == 1)
    head_ = fake_;
  fake_->pPrev_ = temp;
  if (size_ == 1) fake_->pNext_ = fake_;

  size_--;
  fake_->data_--;
}

/* добавляет элемент в конец*/
template <class value_type>
void list<value_type>::push_back(value_type data) {
  Node *new_node = new Node;
  new_node->data_ = data;
  InsertBack(new_node);
}

/*добовлять элемент в начало*/
template <class value_type>
void list<value_type>::push_front(value_type data) {
  Node *new_node = new Node;
  new_node->data_ = data;
  InsertFront(new_node);
}

/*удалять целиком*/
template <class value_type>
void list<value_type>::clear() {
  while (size_) {
    pop_front();
  }
}

/*пустой*/
template <class value_type>
bool list<value_type>::empty() {
  return bool(!size_);
}

/*перевернуть*/
template <class value_type>
void list<value_type>::reverse() {
  Node *iter = fake_->pPrev_;
  while (iter != fake_) {
    std::swap(iter->pNext_, iter->pPrev_);
    iter = iter->pNext_;
  }
  head_ = fake_->pPrev_;
  std::swap(fake_->pNext_, fake_->pPrev_);
}

/*размер*/
template <class value_type>
typename list<value_type>::size_type list<value_type>::size() {
  return size_;
}

/*передний*/
template <class value_type>
typename list<value_type>::const_reference list<value_type>::front() {
  return head_->data_;
}

/*задний*/
template <class value_type>
typename list<value_type>::const_reference list<value_type>::back() {
  return fake_->pPrev_->data_;
}

/*вставлять*/
template <class value_type>
typename list<value_type>::iterator list<value_type>::insert(
    iterator pos, const_reference value) {
  Node *current_node = pos.getNode();
  if (current_node == head_) {
    push_front(value);
    return begin();
  } else if (current_node == head_) {
    push_back(value);
    return iterator(this->fake_->pPrev_);
  } else {
    Node *new_node = new Node;
    new_node->data_ = value;
    InsertBeforeCurrent(new_node, current_node);
    return iterator(new_node);
  }
}

/*стереть*/
template <class value_type>
void list<value_type>::erase(iterator pos) {
  Node *node = pos.getNode();
  RemoveNode(node);
}

/*максимальный размер*/
template <class value_type>
typename list<value_type>::size_type list<value_type>::max_size() {
  return std::numeric_limits<int64_t>::max() / sizeof(*this);
}

/*сливаться*/
template <class value_type>
void list<value_type>::merge(list &other) {
  Node *current_node = head_;
  while (other.head_ != other.fake_) {
    if (current_node == fake_ || other.head_->data_ < current_node->data_) {
      // перемещение ноды other перед current_node
      Node *other_pNext = other.head_->pNext_;
      if (current_node == head_) {
        InsertFront(other.head_);
      } else if (current_node == fake_) {
        InsertBack(other.head_);
      } else {
        InsertBeforeCurrent(other.head_, current_node);
      }
      //  схлапывание листа other
      other.head_ = other_pNext;
      other.size_--;
      other.fake_->data_--;
    } else {
      current_node = current_node->pNext_;
    }
  }
}

/*соединение*/
/*// TODO: НЕОБХОДИМО изменить позиция итератора на константную позицию
 * итератора*/
template <class value_type>
void list<value_type>::splice(const_iterator pos, list &other) {
  Node *current_node = pos.getNode();
  while (other.head_ != other.fake_) {
    // перемещение ноды other перед current_node
    Node *other_pNext = other.head_->pNext_;
    if (current_node == head_) {
      InsertFront(other.head_);
    } else if (current_node == fake_) {
      InsertBack(other.head_);
    } else {
      InsertBeforeCurrent(other.head_, current_node);
    }
    //  схлапывание листа other
    other.head_ = other_pNext;
    other.size_--;
    other.fake_->data_--;
  }
}

/* меняет содержимое*/
template <class value_type>
void list<value_type>::swap(list &other) {
  std::swap(head_, other.head_);
  std::swap(fake_, other.fake_);
  std::swap(size_, other.size_);
}

/*уникальный*/
template <class value_type>
void list<value_type>::unique() {
  if (size_ > 1) {
    Node *first = head_;
    for (; first != fake_;) {
      Node *second = first->pNext_;
      if (second != fake_) {
        if (first->data_ == second->data_) {
          RemoveNode(second);
        } else {
          first = first->pNext_;
        }
      } else {
        break;
      }
    }
  }
}

/*сортировка*/
template <class value_type>
void list<value_type>::sort() {
  bool return_sort = false;
  if (size_ > 1) {
    Node *node1_start = head_;
    Node *node = head_->pNext_;
    bool sublist1 = true;
    while (node != fake_) {
      if (node->data_ < node->pPrev_->data_) {
        if (!sublist1) {
          sublist1 = true;
          node = node->pNext_;
        } else {
          Node *node2_start = node;
          MergeSort(&node1_start, &node2_start);
          if (node1_start != fake_) return_sort = true;
          sublist1 = false;
          node = node1_start;
        }
      } else {
        node = node->pNext_;
      }
    }
  }
  if (return_sort) sort();
}

/*заменить узел*/
template <class value_type>
void list<value_type>::replace_node(Node &first, Node &second) {
  Node *tmp = new Node;
  tmp->data = first.data_;
  first.data_ = second.data_;
  second.data_ = tmp->data_;
}

/*устанавливать back*/
template <class value_type>
template <class... Args>
void list<value_type>::emplace_back(Args &&...args) {
  std::vector<value_type> arguments = {args...};
  for (auto &a : arguments) {
    push_back(a);
  }
}

/*устанавливать front*/
template <class value_type>
template <class... Args>
void list<value_type>::emplace_front(Args &&...args) {
  std::vector<value_type> arguments = {args...};
  for (auto &a : arguments) {
    push_front(a);
  }
}

/*emplace*/
template <class value_type>
template <class... Args>
typename list<value_type>::iterator list<value_type>::emplace(
    const_iterator pos, Args &&...args) {
  std::vector<value_type> arguments = {args...};
  iterator res;
  for (auto &a : arguments) {
    res = insert(pos, a);
  }
  return res;
}

template <class value_type>
void list<value_type>::PrintList() {
  std::cout << "size of lise: " << size_ << std::endl;
  for (iterator i = begin(); i != end(); ++i) {
    std::cout << *i << " ";
  }
  std::cout << std::endl;
}

}  // namespace s21

#endif  // SRC_S21_LIST_CC_
