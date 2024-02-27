#include <gtest/gtest.h>

#include <stack>

#include "s21_containers.h"

TEST(Stack, Constructor_1) {
  s21::stack<int> st;
  EXPECT_EQ(st.size(), 0);
  EXPECT_FALSE(st.empty());
}

TEST(Stack, Constructor_2) {
  s21::stack<int> *st = new s21::stack<int>();
  EXPECT_EQ(st->size(), 0);
  EXPECT_FALSE(st->empty());
}

TEST(Stack, Constructor_3) {
  s21::stack<int> st{3, 5, 6, 7, 8, 9, 10, 11, 12};
  EXPECT_EQ(st.size(), 9);
  EXPECT_EQ(st.top(), 12);
  EXPECT_TRUE(st.empty());
}

TEST(Stack, Constructor_4) {
  s21::stack<int> st{3, 5, 6, 7, 8, 9, 10, 11, 12};
  s21::stack<int> st2 = std::move(st);
  EXPECT_EQ(st2.size(), 9);
  EXPECT_EQ(st2.top(), 12);
  EXPECT_TRUE(st2.empty());
}

TEST(Stack, Copy) {
  s21::stack<int> *st = new s21::stack<int>{3, 5, 6, 7, 8, 9, 10, 11, 12};
  s21::stack<int> st2(*st);
  EXPECT_EQ(st2.size(), 9);
  EXPECT_EQ(st2.top(), 12);
  EXPECT_TRUE(st2.empty());
}

TEST(Stack, Push) {
  s21::stack<int> st;
  st.push(7);
  EXPECT_EQ(st.size(), 1);
  EXPECT_TRUE(st.empty());
}

TEST(Stack, Pop) {
  s21::stack<int> st;
  st.push(7);
  st.push(8);
  st.push(9);
  st.pop();
  EXPECT_EQ(st.size(), 2);
  EXPECT_TRUE(st.empty());
}

TEST(Stack, Top) {
  s21::stack<int> st;
  st.push(7);
  EXPECT_EQ(st.size(), 1);
  EXPECT_TRUE(st.empty());
  EXPECT_EQ(st.top(), 7);
}

TEST(Stack, Swap) {
  s21::stack<int> st{3, 5, 6, 7, 8};
  s21::stack<int> swap_st;
  swap_st.swap(st);
  EXPECT_EQ(swap_st.size(), 5);
  EXPECT_TRUE(swap_st.empty());
  EXPECT_EQ(swap_st.top(), 8);
}

TEST(Stack, Ravno) {
  s21::stack<int> *st = new s21::stack<int>();
  st->push(7);
  st->push(8);
  st->push(9);
  s21::stack<int> *st2 = new s21::stack<int>();
  st2 = st;
  EXPECT_EQ(st2->size(), 3);
  EXPECT_TRUE(st2->empty());
}

TEST(Stack, Emplace) {
  s21::stack<int> my_queue{1, 8, 7};
  my_queue.emplace_back(11);
  EXPECT_EQ(my_queue.size(), 4);
  EXPECT_TRUE(my_queue.empty());
}

TEST(Stack, Emplace_2) {
  s21::stack<int> my_queue{1, 8, 7};
  my_queue.emplace_back(11, 22, 33, 44);
  EXPECT_EQ(my_queue.size(), 7);
  EXPECT_TRUE(my_queue.empty());
}
