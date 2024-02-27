#ifndef SRC_S21_MULTISET_H_
#define SRC_S21_MULTISET_H_
#include <vector>

#include "s21_set.h"

namespace s21 {
template <class Key>
class multiset : public set<Key> {
 public:
  typedef Key key_type;
  typedef key_type value_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef size_t size_type;
  typedef typename set<value_type>::iterator iterator;
  typedef typename set<value_type>::Node NodeSet;

  multiset();
  multiset(std::initializer_list<value_type> const& items);
  multiset(const multiset<value_type>& other);
  multiset(multiset<value_type>&& other);
  ~multiset();

  iterator insert(const value_type& value);

  void erase(iterator pos);
  void erase(const value_type& key);

  size_type count(const Key& value);
  std::pair<iterator, iterator> equal_range(const Key& value);

  iterator lower_bound(const Key& value);
  iterator upper_bound(const Key& value);
  template <class... Args>
  iterator emplace(Args&&... args);

 private:
  multiset<value_type>& operator=(multiset&& other);
  iterator addNode(NodeSet* node, const value_type& value);
  // iterator deleteOneNode(NodeSet* node, const value_type& value);
};

}  // namespace s21
#include "s21_multiset.cc"
#endif  // SRC_S21_MULTISET_CC_
