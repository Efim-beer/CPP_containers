#include <gtest/gtest.h>

#include <queue>

#include "s21_containers.h"

TEST(Queue, Copy_Constructor_2) {
  s21::queue<int> *ls = new s21::queue<int>{101, 5, 6, 6, 3, 3, 444};
  s21::queue<int> ls2(*ls);
  EXPECT_EQ(ls->size(), 7);
  EXPECT_EQ(ls->back(), 444);
  EXPECT_EQ(ls->front(), 101);
  EXPECT_EQ(ls2.size(), 7);
  EXPECT_EQ(ls2.back(), 444);
  EXPECT_EQ(ls2.front(), 101);
}

TEST(Queue, Move_Constructor) {
  s21::queue<int> ls{10, 15, 3, 2, 1, 11, 5};
  s21::queue<int> ls2 = std::move(ls);
  EXPECT_EQ(ls2.size(), 7);
  EXPECT_EQ(ls.size(), 0);
  EXPECT_EQ(ls2.back(), 5);
  EXPECT_EQ(ls2.front(), 10);
}

TEST(Queue, Push) {
  s21::queue<int> my_queue;
  my_queue.push(8);
  my_queue.push(11);
  EXPECT_EQ(my_queue.size(), 2);
  EXPECT_TRUE(my_queue.empty());
}

TEST(Queue, Push_2) {
  s21::queue<int> my_queue{1, 8, 7};
  my_queue.push(8);
  EXPECT_EQ(my_queue.size(), 4);
  EXPECT_TRUE(my_queue.empty());
}

TEST(Queue, Pop) {
  s21::queue<int> my_queue{1, 8, 7};
  my_queue.pop();
  EXPECT_EQ(my_queue.size(), 2);
  EXPECT_TRUE(my_queue.empty());
}

TEST(Queue, Pop_Error) {
  s21::queue<int> my_queue;
  EXPECT_THROW(my_queue.pop(), std::invalid_argument);
}

TEST(Queue, Front) {
  s21::queue<int> my_queue{1, 8, 7};
  EXPECT_EQ(my_queue.front(), 1);
  EXPECT_TRUE(my_queue.empty());
}

TEST(Queue, Front_Error) {
  s21::queue<int> my_queue;
  EXPECT_THROW(my_queue.front(), std::invalid_argument);
}

TEST(Queue, Back) {
  s21::queue<int> my_queue{1, 8, 7};
  EXPECT_EQ(my_queue.back(), 7);
  EXPECT_TRUE(my_queue.empty());
}

TEST(Queue, Back_Error) {
  s21::queue<int> my_queue;
  EXPECT_THROW(my_queue.back(), std::invalid_argument);
}

TEST(Queue, Swap) {
  s21::queue<int> queue_1{11, 22, 33};
  s21::queue<int> queue_2{77, 88, 99};
  queue_1.swap(queue_2);
  EXPECT_EQ(queue_1.front(), 77);
  EXPECT_EQ(queue_2.front(), 11);
  EXPECT_EQ(queue_1.back(), 99);
  EXPECT_EQ(queue_2.back(), 33);
}

TEST(Queue, Swap_2) {
  s21::queue<int> queue_1{11, 22, 222, 333, 33};
  s21::queue<int> queue_2{77, 88};
  queue_1.swap(queue_2);
  EXPECT_EQ(queue_1.front(), 77);
  EXPECT_EQ(queue_1.back(), 88);
  EXPECT_EQ(queue_2.front(), 11);
  EXPECT_EQ(queue_2.back(), 33);
}

TEST(Queue, Swap_3) {
  s21::queue<int> queue_1;
  s21::queue<int> queue_2{77, 88, 99};
  queue_1.swap(queue_2);
  EXPECT_EQ(queue_1.front(), 77);
  EXPECT_EQ(queue_1.back(), 99);
  EXPECT_THROW(queue_2.back(), std::invalid_argument);
  EXPECT_THROW(queue_2.front(), std::invalid_argument);
}

TEST(Queue, Swap_4) {
  s21::queue<int> queue_1;
  s21::queue<int> queue_2{77};
  queue_1.swap(queue_2);
  EXPECT_EQ(queue_1.front(), 77);
  EXPECT_EQ(queue_1.back(), 77);
  EXPECT_THROW(queue_2.back(), std::invalid_argument);
  EXPECT_THROW(queue_2.front(), std::invalid_argument);
}

TEST(Queue, Swap_Null) {
  s21::queue<int> queue_1;
  s21::queue<int> queue_2;
  queue_1.swap(queue_2);
  EXPECT_FALSE(queue_1.empty());
  EXPECT_FALSE(queue_2.empty());
  EXPECT_THROW(queue_1.back(), std::invalid_argument);
  EXPECT_THROW(queue_1.front(), std::invalid_argument);
  EXPECT_THROW(queue_2.back(), std::invalid_argument);
  EXPECT_THROW(queue_2.front(), std::invalid_argument);
}

TEST(Queue, Emplace) {
  s21::queue<int> my_queue{1, 8, 7};
  my_queue.emplace_back(11);
  EXPECT_EQ(my_queue.size(), 4);
  EXPECT_TRUE(my_queue.empty());
}
