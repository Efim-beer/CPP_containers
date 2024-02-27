#include <gtest/gtest.h>

#include <array>

#include "s21_containersplus.h"

TEST(Array, Constructor_1) {
  s21::array<int, 4> my_array;
  std::array<int, 4> fact;
  EXPECT_EQ(my_array.size(), fact.size());
}

TEST(Array, Constructor_2) {
  s21::array<int, 4> my_array{};
  std::array<int, 4> fact{};
  EXPECT_EQ(my_array.size(), fact.size());
  int i = 0;
  for (const auto &val : fact) {
    EXPECT_EQ(val, my_array[i]);
    ++i;
  }
}

TEST(Array, Constructor_3) {
  s21::array<char, 5> my_array{};
  std::array<char, 5> fact{};
  EXPECT_EQ(my_array.size(), fact.size());
  int i = 0;
  for (const auto &val : fact) {
    EXPECT_EQ(val, my_array[i]);
    ++i;
  }
}

TEST(Array, Constructor_4) {
  s21::array<int, 8> my_array{1, 2, 3, 4, 5, 6, 7, 8};
  std::array<int, 8> fact{1, 2, 3, 4, 5, 6, 7, 8};
  EXPECT_EQ(my_array.size(), fact.size());
  for (size_t i = 0; i < fact.size(); ++i) {
    EXPECT_EQ(fact[i], my_array[i]);
  }
}

TEST(Array, Constructor_5) {
  s21::array<int, 10> my_array{1, 2, 3, 4, 5, 6, 7, 8};
  std::array<int, 10> fact{1, 2, 3, 4, 5, 6, 7, 8};
  EXPECT_EQ(my_array.size(), fact.size());
  for (size_t i = 0; i < fact.size(); ++i) {
    EXPECT_EQ(fact[i], my_array[i]);
  }
}

TEST(Array, Copy_Constructor_1) {
  s21::array<int, 10> my_array1{1, 2, 3, 4, 5, 6, 7, 8};
  s21::array<int, 10> my_array2{my_array1};
  EXPECT_EQ(my_array1.size(), my_array2.size());
  for (size_t i = 0; i < my_array1.size(); i++) {
    EXPECT_EQ(my_array1[i], my_array2[i]);
  }
}

TEST(Array, Move_Constructor_1) {
  s21::array<int, 5> my_array1 = {3, 4, 5};
  s21::array<int, 5> my_array2(std::move(my_array1));
  EXPECT_EQ(my_array1.size(), my_array2.size());
  for (size_t i = 0; i < my_array1.size(); ++i) {
    EXPECT_EQ(my_array1[i], my_array2[i]);
  }
}

TEST(Array, Operator_Assign_1) {
  s21::array<int, 5> my_array1 = {3, 4, 5};
  s21::array<int, 5> my_array2 = std::move(my_array1);
  EXPECT_EQ(my_array1.size(), my_array2.size());
  for (size_t i = 0; i < my_array1.size(); ++i) {
    EXPECT_EQ(my_array1[i], my_array2[i]);
  }
}

TEST(Array, At_1) {
  s21::array<int, 5> my_array{0, 1, 2, 3, 4};
  EXPECT_EQ(my_array.at(2), 2);
}

TEST(Array, At_2) {
  s21::array<int, 5> my_array{0, 1, 2, 3, 4};
  EXPECT_EQ(my_array.at(3), 3);
  my_array.at(3) = 88;
  EXPECT_EQ(my_array.at(3), 88);
}

TEST(Array, At_3) {
  s21::array<int, 5> my_array{0, 1, 2, 3, 4};
  EXPECT_ANY_THROW(my_array.at(5) = 55);
}

TEST(Array, front_1) {
  s21::array<int, 10> my_array{-171, 45, 67, 9, 4, 45};
  EXPECT_EQ(my_array.front(), -171);
}

TEST(Array, back_1) {
  s21::array<int, 6> my_array{-171, 45, 67, 9, 4, 45};
  EXPECT_EQ(my_array.back(), 45);
}

TEST(Array, Data_1) {
  s21::array<int, 5> my_array{};
  EXPECT_EQ(my_array.data(), &my_array[0]);
}

TEST(Array, Data_2) {
  s21::array<double, 0> my_array{4.45};
  EXPECT_EQ(my_array.data(), &my_array[0]);
}

TEST(Array, Iterator_1) {
  s21::array<int, 3> my_array{7, 4, -99};
  size_t i = 0;
  for (int *it = my_array.begin(); it < my_array.end(); ++it, ++i)
    EXPECT_EQ(*it, my_array[i]);
}

TEST(Array, Iterator_2) {
  s21::array<int, 3> my_array{7, 4, -99};
  size_t i = 2;
  for (int *it = my_array.end() - 1; it >= my_array.begin(); --it, --i)
    EXPECT_EQ(*it, my_array[i]);
}

TEST(Array, Empty_1) {
  s21::array<int, 0> my_array;
  std::array<int, 0> fact;
  EXPECT_EQ(my_array.empty(), fact.empty());
}

TEST(Array, Empty_2) {
  s21::array<int, 8> my_array;
  std::array<int, 8> fact;
  EXPECT_EQ(my_array.empty(), fact.empty());
}

TEST(Array, Max_size_1) {
  s21::array<int, 20> my_array{2,  10, 15, 3, 2, 1, 11, 5,
                               12, 12, 12, 4, 6, 9, 8};
  std::array<int, 20> fact{2, 10, 15, 3, 2, 1, 11, 5, 12, 12, 12, 4, 6, 9, 8};
  EXPECT_EQ(my_array.max_size(), fact.max_size());
}

TEST(Array, Swap_1) {
  s21::array<int, 3> my_vec1{11, 22, 33};
  s21::array<int, 3> my_vec2{};
  std::array<int, 3> fact1{11, 22, 33};
  std::array<int, 3> fact2{};
  my_vec1.swap(my_vec2);
  fact1.swap(fact2);
  EXPECT_EQ(my_vec1.size(), fact1.size());
  EXPECT_EQ(my_vec2.size(), fact2.size());
  for (size_t i = 0; i < fact1.size(); ++i) {
    EXPECT_EQ(my_vec1[i], fact1[i]);
  }
  for (size_t i = 0; i < fact2.size(); ++i) {
    EXPECT_EQ(my_vec2[i], fact2[i]);
  }
}

TEST(Array, Fill_1) {
  s21::array<int, 3> my_vec;
  my_vec.fill(-55);
  std::array<int, 3> fact;
  fact.fill(-55);
  for (size_t i = 0; i < fact.size(); ++i) {
    EXPECT_EQ(my_vec[i], fact[i]);
  }
}
