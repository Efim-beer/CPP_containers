#include <gtest/gtest.h>

#include <set>

// #include "s21_containers.h"
#include "s21_multiset.h"
#include "s21_set.h"

TEST(Set, Constructor_1) {
  s21::set<int> st;
  ASSERT_EQ(st.size(), 0);
  ASSERT_FALSE(st.empty());
}

TEST(Set, Constructor_2) {
  s21::set<int> st{3, 5, 8, 7, 2};
  ASSERT_EQ(st.size(), 5);
  ASSERT_TRUE(st.empty());
}

TEST(Set, Copy_Constructor) {
  s21::set<int> st{3, 5, 8, 7, 2};
  s21::set<int> result(st);
  s21::set<int>::iterator my_it = result.begin();
  EXPECT_EQ(result.size(), st.size());
  EXPECT_EQ(*my_it, 2);
  ++my_it;
  EXPECT_EQ(*my_it, 3);
  EXPECT_TRUE(result.empty());
}

TEST(Set, Move_Constructor) {
  s21::set<int> st{3, 5, 8, 7, 2};
  s21::set<int> result = std::move(st);
  s21::set<int>::iterator my_it = result.begin();
  EXPECT_EQ(result.size(), 5);
  EXPECT_EQ(*my_it, 2);
  ++my_it;
  EXPECT_EQ(*my_it, 3);
  EXPECT_TRUE(result.empty());
}

TEST(Set, Clear) {
  s21::set<int> st{3, 5, 8, 7, 2};
  EXPECT_EQ(st.size(), 5);
  EXPECT_TRUE(st.empty());
  st.clear();
  EXPECT_EQ(st.size(), 0);
  EXPECT_FALSE(st.empty());
}

TEST(Set, Insert) {
  s21::set<int> st;
  st.insert(8);
  EXPECT_EQ(st.size(), 1);
  EXPECT_TRUE(st.empty());
  EXPECT_TRUE(st.insert(35).second);
  EXPECT_FALSE(st.insert(35).second);
  s21::set<int>::iterator iter;
  iter = st.insert(588).first;
  EXPECT_EQ(*iter, 588);
}

TEST(Set, Contains) {
  s21::set<int> st{8, 25, 35, 45, 11, 9, 7, 4, 14};
  EXPECT_TRUE(st.contains(45));
  EXPECT_TRUE(st.contains(11));
  EXPECT_TRUE(st.contains(7));
  EXPECT_TRUE(st.contains(9));
  EXPECT_FALSE(st.contains(4555));
  EXPECT_FALSE(st.contains(-5));
  EXPECT_FALSE(st.contains(987));
  EXPECT_FALSE(st.contains(654));
}

TEST(Set, Iterator_1) {
  s21::set<int> st{8, 25, 35, 45, 11, 9, 7, 4, 14};
  s21::set<int>::iterator my_it = st.begin();
  EXPECT_EQ(*my_it, 4);
  ++my_it;
  EXPECT_EQ(*my_it, 7);
  ++my_it;
  EXPECT_EQ(*my_it, 8);
  ++my_it;
  EXPECT_EQ(*my_it, 9);
  ++my_it;
  EXPECT_EQ(*my_it, 11);
  ++my_it;
  EXPECT_EQ(*my_it, 14);
  ++my_it;
  EXPECT_EQ(*my_it, 25);
  ++my_it;
  EXPECT_EQ(*my_it, 35);
  ++my_it;
  EXPECT_EQ(*my_it, 45);
}

TEST(Set, Iterator_2) {
  s21::set<int> st{8, 25, 35, 45, 11, 9, 7, 4, 14};
  s21::set<int>::iterator my_it = st.end();
  --my_it;
  EXPECT_EQ(*my_it, 45);
  --my_it;
  EXPECT_EQ(*my_it, 35);
  --my_it;
  EXPECT_EQ(*my_it, 25);
  --my_it;
  EXPECT_EQ(*my_it, 14);
  --my_it;
  EXPECT_EQ(*my_it, 11);
  --my_it;
  EXPECT_EQ(*my_it, 9);
  --my_it;
  EXPECT_EQ(*my_it, 8);
  --my_it;
  EXPECT_EQ(*my_it, 7);
}

TEST(Set, Find) {
  s21::set<int> st{8, 25, 35, 45, 11, 9, 7, 4, 14};
  s21::set<int>::iterator my_it = st.begin();
  EXPECT_EQ(st.find(4), my_it);
  ++my_it;
  EXPECT_EQ(st.find(7), my_it);
  --my_it;
  EXPECT_EQ(st.find(4), my_it);
  s21::set<int>::iterator iterator_25 = st.find(25);
  EXPECT_EQ(*iterator_25, 25);
}

TEST(Set, Merge) {
  s21::set<int> st{8, 25};
  s21::set<int> add{0, 15, 57, 25};
  st.merge(add);
  s21::set<int>::iterator my_it = st.begin();
  EXPECT_EQ(*my_it, 0);
  EXPECT_EQ(st.find(0), my_it);
  EXPECT_EQ(st.size(), 5);
}

TEST(Set, Erase) {
  s21::set<int> st{4, 6, 7, 3, 1};
  s21::set<int>::iterator iter = st.begin();
  ++iter;  // 3
  st.erase(iter);
  ++iter;  // 4
  st.erase(iter);
  EXPECT_FALSE(st.contains(3));
  EXPECT_TRUE(st.contains(1));
  EXPECT_FALSE(st.contains(4));
  EXPECT_EQ(st.size(), 3);
}

TEST(Set, Erase_1) {
  s21::set<double> st{4, 4.00001, 8, 3, 1};
  s21::set<double>::iterator iter = st.begin();
  ++iter;
  ++iter;
  st.erase(iter);
  EXPECT_FALSE(st.contains(4));
  EXPECT_TRUE(st.contains(4.00001));
}

TEST(Set, Emplace) {
  s21::set<int> st{4, 7, 9};
  st.emplace(1);
  EXPECT_EQ(st.size(), 4);
  EXPECT_TRUE(st.empty());
  s21::set<int>::iterator iter;
  iter = st.begin();
  EXPECT_EQ(*iter, 1);
}

TEST(Set, Emplace_2) {
  s21::set<int> st{4, 7, 9};
  st.emplace(1, 2, 3);
  EXPECT_EQ(st.size(), 6);
  EXPECT_TRUE(st.empty());
  s21::set<int>::iterator iter;
  iter = st.begin();
  EXPECT_EQ(*iter, 1);
  ++iter;
  EXPECT_EQ(*iter, 2);
  ++iter;
  EXPECT_EQ(*iter, 3);
  ++iter;
}

/*******************************************************************/

TEST(Multiset, Constructor) {
  s21::multiset<int> st;
  EXPECT_EQ(st.size(), 0);
  EXPECT_FALSE(st.empty());
}

TEST(Multiset, Constructor_1) {
  s21::multiset<int> st{1, 3, 5};
  EXPECT_EQ(st.size(), 3);
  EXPECT_TRUE(st.empty());
  s21::multiset<int>::iterator it = st.begin();
  EXPECT_EQ(1, *it);
  ++it;
  EXPECT_EQ(3, *it);
  ++it;
  EXPECT_EQ(5, *it);
}

TEST(Multiset, Constructor_Copy) {
  s21::multiset<int> st{1, 3, 5};
  s21::multiset<int> st2(st);
  s21::multiset<int>::iterator it = st2.begin();
  EXPECT_EQ(1, *it);
  ++it;
  EXPECT_EQ(3, *it);
  ++it;
  EXPECT_EQ(5, *it);
  EXPECT_EQ(st.size(), 3);
  EXPECT_TRUE(st.empty());
  EXPECT_EQ(st2.size(), 3);
  EXPECT_TRUE(st2.empty());
}

TEST(Multiset, Constructor_Move) {
  s21::multiset<int> st{1, 3, 5};
  s21::multiset<int> st2 = std::move(st);
  s21::multiset<int>::iterator it = st2.begin();
  EXPECT_EQ(1, *it);
  ++it;
  EXPECT_EQ(3, *it);
  ++it;
  EXPECT_EQ(5, *it);
  EXPECT_EQ(st2.size(), 3);
  EXPECT_TRUE(st2.empty());
}

TEST(Multiset, Erase_1) {
  s21::multiset<int> st{7, 7, 3, 1, 1, 5};
  s21::multiset<int>::iterator it = st.begin();
  st.erase(1);
  EXPECT_FALSE(st.contains(1));
  st.erase(7);
  EXPECT_FALSE(st.contains(7));
}

TEST(Multiset, Erase_3) {
  s21::multiset<int> st{4, 8, 2};
  s21::multiset<int>::iterator it = st.begin();
  ++it;
  ++it;
  st.erase(it);
  EXPECT_FALSE(st.contains(8));
  EXPECT_TRUE(st.contains(4));
  EXPECT_EQ(st.size(), 2);
}

TEST(Multiset, Lower_bound) {
  s21::multiset<int> st{7, 1, 3, 3, 4, 4, 4, 3};
  std::multiset<int> fset{7, 1, 3, 3, 4, 4, 4, 3};
  EXPECT_EQ(*st.lower_bound(2), *fset.lower_bound(2));
  EXPECT_EQ(*st.lower_bound(3), *fset.lower_bound(3));
  EXPECT_EQ(*st.lower_bound(4), *fset.lower_bound(4));
  EXPECT_EQ(*st.lower_bound(5), *fset.lower_bound(5));
}

TEST(Multiset, Upper_bound) {
  s21::multiset<int> st{7, 1, 3, 3, 4, 4, 4, 3, 5};
  std::multiset<int> fset{7, 1, 3, 3, 4, 4, 4, 3, 5};
  EXPECT_EQ(*st.upper_bound(1), *fset.upper_bound(1));
  EXPECT_EQ(*st.upper_bound(3), *fset.upper_bound(3));
  EXPECT_EQ(*st.upper_bound(4), *fset.upper_bound(4));
  EXPECT_EQ(*st.upper_bound(5), *fset.upper_bound(5));
}

TEST(Multiset, Count) {
  s21::multiset<int> st{7, 1, 3, 3, 4, 4, 4, 3, 5};
  EXPECT_EQ(st.count(1), 1);
  EXPECT_EQ(st.count(3), 3);
  EXPECT_EQ(st.count(4), 3);
  EXPECT_EQ(st.count(5), 1);
  EXPECT_EQ(st.count(88), 0);
}

TEST(Multiset, Find) {
  s21::multiset<int> st{7, 1, 3, 3, 4, 4, 4, 3, 5};
  s21::multiset<int>::iterator it = st.begin();
  EXPECT_EQ(*st.find(1), *it);
  ++it;
  EXPECT_EQ(*it, *st.find(3));
  ++it;
  ++it;
  ++it;
  EXPECT_EQ(*it, *st.find(4));
  it = st.end();
  EXPECT_EQ(*it, *st.find(888));
}

TEST(Multiset, Contains) {
  s21::multiset<int> st{7, 1, 3, 3, 4, 4, 4, 3, 5};
  EXPECT_TRUE(st.contains(7));
  EXPECT_TRUE(st.contains(4));
  EXPECT_TRUE(st.contains(5));
  EXPECT_TRUE(st.contains(1));
  EXPECT_FALSE(st.contains(888));
}

TEST(Multiset, Emplace) {
  s21::multiset<int> st{7, 4, 9};
  st.emplace(3, 1, 20);
  s21::multiset<int>::iterator it = st.begin();
  EXPECT_EQ(st.size(), 6);
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 3);
  s21::multiset<int>::iterator it_end = st.end();
  --it_end;
  EXPECT_EQ(*it_end, 20);
  --it_end;
  EXPECT_EQ(*it_end, 9);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
