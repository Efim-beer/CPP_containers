#include <gtest/gtest.h>

#include <vector>

#include "s21_containers.h"

TEST(Vector, Constructor_1) {
  s21::vector<int> my_vec;
  std::vector<int> fact;
  EXPECT_EQ(my_vec.size(), fact.size());
  EXPECT_EQ(my_vec.capacity(), fact.capacity());
}

TEST(Vector, Constructor_2) {
  s21::vector<int> my_vec(4);
  std::vector<int> fact(4);
  EXPECT_EQ(my_vec.size(), fact.size());
  EXPECT_EQ(my_vec.capacity(), fact.capacity());
  int i = 0;
  for (const auto &val : fact) {
    EXPECT_EQ(val, my_vec[i]);
    ++i;
  }
}

TEST(Vector, Constructor_3) {
  s21::vector<double> my_vec(4, -5.65);
  std::vector<double> fact(4, -5.65);
  EXPECT_EQ(my_vec.size(), fact.size());
  EXPECT_EQ(my_vec.capacity(), fact.capacity());
  int i = 0;
  for (const auto &val : fact) {
    EXPECT_EQ(val, my_vec[i]);
    i++;
  }
}

TEST(Vector, Constructor_4) {
  s21::vector<int> my_vec{1, 2, 3, 4, 5, 6, 7, 8};
  std::vector<int> fact{1, 2, 3, 4, 5, 6, 7, 8};
  EXPECT_EQ(my_vec.size(), fact.size());
  EXPECT_EQ(my_vec.capacity(), fact.capacity());
  for (size_t i = 0; i < fact.size(); ++i) {
    EXPECT_EQ(fact[i], my_vec[i]);
  }
}

TEST(Vector, Copy_Constructor_1) {
  s21::vector<int> vec{101, 5, 6, 6, 3, 3, 444, 4};
  vec.push_back(-33);
  s21::vector<int> vec2(vec);
  std::vector<int> fact{101, 5, 6, 6, 3, 3, 444, 4};
  fact.push_back(-33);
  for (size_t i = 0; i < fact.size(); ++i) {
    EXPECT_EQ(vec2[i], fact[i]);
  }
  EXPECT_EQ(vec2.size(), fact.size());
  EXPECT_EQ(vec2.capacity(), fact.capacity());
}

TEST(Vector, Move_Constructor_1) {
  s21::vector<int> vec{10, 15, 3, 2, 1, 11, 5};
  s21::vector<int> vec2 = std::move(vec);
  s21::vector<int> vec3{10, 15, 3, 2, 1, 11, 5};
  for (size_t i; i < vec3.size(); ++i) {
    EXPECT_EQ(vec2[i], vec3[i]);
  }
  EXPECT_EQ(vec2.size(), vec3.size());
  EXPECT_EQ(vec2.capacity(), vec3.capacity());
  EXPECT_EQ(vec.size(), 0);
  EXPECT_EQ(vec.capacity(), 0);
}

TEST(Vector, push_back_1) {
  s21::vector<std::string> my_vec;
  my_vec.push_back("I");
  my_vec.push_back("love");
  my_vec.push_back("School21!");
  std::vector<std::string> fact;
  fact.push_back("I");
  fact.push_back("love");
  fact.push_back("School21!");
  for (size_t i; i < fact.size(); ++i) {
    EXPECT_EQ(my_vec[i], fact[i]);
  }
  EXPECT_EQ(my_vec.size(), fact.size());
  EXPECT_EQ(my_vec.capacity(), fact.capacity());
}

TEST(Vector, back_1) {
  s21::vector<int> my_vec;
  my_vec.push_back(5);
  my_vec.push_back(8);
  my_vec.push_back(88);
  my_vec.push_back(123);
  EXPECT_EQ(my_vec.back(), 123);
}

TEST(Vector, back_2) {
  s21::vector<int> my_vec(1);
  EXPECT_EQ(my_vec.back(), 0);
}

TEST(Vector, front_1) {
  s21::vector<int> my_vec(1);
  my_vec.push_back(5);
  my_vec.push_back(8);
  my_vec.push_back(88);
  my_vec.push_back(123);
  EXPECT_EQ(my_vec.front(), 0);
}

TEST(Vector, front_2) {
  s21::vector<int> my_vec;
  my_vec.push_back(5);
  my_vec.push_back(8);
  my_vec.push_back(88);
  my_vec.push_back(123);
  EXPECT_EQ(my_vec.front(), 5);
}

TEST(Vector, pop_back_1) {
  s21::vector<int> my_vec(3);
  my_vec.push_back(10);
  my_vec.push_back(13);
  my_vec.push_back(1234);
  my_vec.push_back(-5);
  EXPECT_EQ(my_vec[6], -5);
  my_vec.pop_back();
  EXPECT_EQ(my_vec[5], 1234);
  my_vec.pop_back();
  EXPECT_EQ(my_vec[4], 13);
  my_vec.pop_back();
  EXPECT_EQ(my_vec[3], 10);
  my_vec.pop_back();
  EXPECT_EQ(my_vec[2], 0);
  my_vec.pop_back();
  EXPECT_EQ(my_vec[1], 0);
  my_vec.pop_back();
  EXPECT_EQ(my_vec[0], 0);
  my_vec.pop_back();
  EXPECT_EQ(my_vec.size(), 0);
  EXPECT_EQ(my_vec.capacity(), 12);
}

TEST(Vector, Empty_1) {
  s21::vector<int> my_vec(8);
  std::vector<int> fact(8);
  EXPECT_EQ(my_vec.empty(), fact.empty());
}

TEST(Vector, Empty_2) {
  s21::vector<int> my_vec;
  std::vector<int> fact;
  EXPECT_EQ(my_vec.empty(), fact.empty());
}

TEST(Vector, Data_1) {
  s21::vector<int> my_vec(4);
  EXPECT_EQ(my_vec.data(), &my_vec[0]);
}

TEST(Vector, Data_2) {
  s21::vector<double> my_vec(4, 67.5);
  EXPECT_EQ(my_vec.data(), &my_vec[0]);
}

TEST(Vector, Max_size_1) {
  s21::vector<int> my_vec{12, 10, 15, 3, 2, 1, 11, 5, 12, 12, 12, 4, 6, 9, 8};
  std::vector<int> fact{12, 10, 15, 3, 2, 1, 11, 5, 12, 12, 12, 4, 6, 9, 8};
  EXPECT_EQ(my_vec.max_size(), fact.max_size());
}

TEST(Vector, Reserve_1) {
  s21::vector<float> my_vec;
  std::vector<float> fact;
  EXPECT_EQ(my_vec.size(), fact.size());
  EXPECT_EQ(my_vec.capacity(), fact.capacity());
  for (size_t i = 0; i < fact.size(); ++i) {
    EXPECT_EQ(fact[i], my_vec[i]);
  }
  my_vec.reserve(50);
  fact.reserve(50);
  EXPECT_EQ(my_vec.size(), fact.size());
  EXPECT_EQ(my_vec.capacity(), fact.capacity());
  for (size_t i = 0; i < fact.size(); ++i) {
    EXPECT_EQ(fact[i], my_vec[i]);
  }
}

TEST(Vector, Reserve_2) {
  s21::vector<float> my_vec{234.7, -234e3, 345.2342};
  std::vector<float> fact{234.7, -234e3, 345.2342};
  EXPECT_EQ(my_vec.size(), fact.size());
  EXPECT_EQ(my_vec.capacity(), fact.capacity());
  for (size_t i = 0; i < fact.size(); ++i) {
    EXPECT_EQ(fact[i], my_vec[i]);
  }
  my_vec.reserve(50);
  fact.reserve(50);
  EXPECT_EQ(my_vec.size(), fact.size());
  EXPECT_EQ(my_vec.capacity(), fact.capacity());
  for (size_t i = 0; i < fact.size(); ++i) {
    EXPECT_EQ(fact[i], my_vec[i]);
  }
}

TEST(Vector, Shrink_to_fit_1) {
  s21::vector<int> my_vec{1, 2, 3, 4, 5, 6, 7, 8};
  std::vector<int> fact{1, 2, 3, 4, 5, 6, 7, 8};
  EXPECT_EQ(my_vec.size(), fact.size());
  EXPECT_EQ(my_vec.capacity(), fact.capacity());
  my_vec.push_back(9);
  fact.push_back(9);
  EXPECT_EQ(my_vec.size(), fact.size());
  EXPECT_EQ(my_vec.capacity(), fact.capacity());
  my_vec.shrink_to_fit();
  fact.shrink_to_fit();
  EXPECT_EQ(my_vec.size(), fact.size());
  EXPECT_EQ(my_vec.capacity(), fact.capacity());
}

TEST(Vector, Shrink_to_fit_2) {
  s21::vector<int> my_vec{1, 2, 3, 4, 5, 6, 7, 8};
  std::vector<int> fact{1, 2, 3, 4, 5, 6, 7, 8};
  EXPECT_EQ(my_vec.size(), fact.size());
  EXPECT_EQ(my_vec.capacity(), fact.capacity());
  my_vec.shrink_to_fit();
  fact.shrink_to_fit();
  EXPECT_EQ(my_vec.size(), fact.size());
  EXPECT_EQ(my_vec.capacity(), fact.capacity());
}

TEST(Vector, Clear_1) {
  s21::vector<int> my_vec{1, 2, 3, 4, 5, 6, 7, 8};
  my_vec.push_back(9);
  my_vec.clear();
  std::vector<int> fact{1, 2, 3, 4, 5, 6, 7, 8};
  fact.push_back(9);
  fact.clear();
  EXPECT_EQ(my_vec.size(), fact.size());
  EXPECT_EQ(my_vec.capacity(), fact.capacity());
  for (size_t i = 0; i < fact.size(); ++i) {
    EXPECT_EQ(my_vec[i], fact[i]);
  }
}

TEST(Vector, At_1) {
  s21::vector<int> my_vec{0, 1, 2, 3, 4};
  EXPECT_EQ(my_vec.at(2), 2);
}

TEST(Vector, At_2) {
  s21::vector<int> my_vec{0, 1, 2, 3, 4};
  my_vec.at(3) = 88;
  EXPECT_EQ(my_vec.at(3), 88);
}

TEST(Vector, At_3) {
  s21::vector<int> my_vec{0, 1, 2, 3, 4};
  EXPECT_ANY_THROW(my_vec.at(5) = 55);
}

TEST(Vector, Operator_Equal_1) {
  s21::vector<int> my_vec1{0, 1, 2, 3, 4};
  s21::vector<int> my_vec2 = std::move(my_vec1);
  std::vector<int> fact1{0, 1, 2, 3, 4};
  std::vector<int> fact2 = std::move(fact1);
  EXPECT_EQ(my_vec1.size(), fact1.size());
  EXPECT_EQ(my_vec1.capacity(), fact1.capacity());
  EXPECT_EQ(my_vec2.size(), fact2.size());
  EXPECT_EQ(my_vec2.capacity(), fact2.capacity());
  for (size_t i = 0; i < fact1.size(); ++i) {
    EXPECT_EQ(my_vec1[i], fact1[i]);
  }
  for (size_t i = 0; i < fact2.size(); ++i) {
    EXPECT_EQ(my_vec2[i], fact2[i]);
  }
}

TEST(Vector, Swap_1) {
  s21::vector<int> my_vec1{11, 22, 33};
  s21::vector<int> my_vec2;
  std::vector<int> fact1{11, 22, 33};
  std::vector<int> fact2;
  my_vec1.swap(my_vec2);
  fact1.swap(fact2);
  EXPECT_EQ(my_vec1.size(), fact1.size());
  EXPECT_EQ(my_vec1.capacity(), fact1.capacity());
  EXPECT_EQ(my_vec2.size(), fact2.size());
  EXPECT_EQ(my_vec2.capacity(), fact2.capacity());
  for (size_t i = 0; i < fact1.size(); ++i) {
    EXPECT_EQ(my_vec1[i], fact1[i]);
  }
  for (size_t i = 0; i < fact2.size(); ++i) {
    EXPECT_EQ(my_vec2[i], fact2[i]);
  }
}

TEST(Vector, Swap_2) {
  s21::vector<int> my_vec1{11, 22, 33};
  s21::vector<int> my_vec2(3, 7);
  std::vector<int> fact1{11, 22, 33};
  std::vector<int> fact2(3, 7);
  my_vec2.push_back(55);
  fact2.push_back(55);
  my_vec1.swap(my_vec2);
  fact1.swap(fact2);
  EXPECT_EQ(my_vec1.size(), fact1.size());
  EXPECT_EQ(my_vec1.capacity(), fact1.capacity());
  EXPECT_EQ(my_vec2.size(), fact2.size());
  EXPECT_EQ(my_vec2.capacity(), fact2.capacity());
  for (size_t i = 0; i < fact1.size(); ++i) {
    EXPECT_EQ(my_vec1[i], fact1[i]);
  }
  for (size_t i = 0; i < fact2.size(); ++i) {
    EXPECT_EQ(my_vec2[i], fact2[i]);
  }
}

TEST(Vector, VectorIterator_1) {
  s21::vector<int> my_vec(3);
  my_vec.push_back(123);
  my_vec.push_back(7);
  my_vec.push_back(888);
  s21::vector<int>::iterator iter = my_vec.begin();
  std::vector<int> fact{0, 0, 0, 123, 7, 888};
  int i = 0;
  for (; iter != my_vec.end(); ++iter, ++i) EXPECT_EQ(*iter, fact[i]);
}

TEST(Vector, VectorIterator_2) {
  s21::vector<int> my_vec{0, 0, 0, 123, 7, 888};
  s21::vector<int>::iterator iter = my_vec.end();
  std::vector<int> fact{0, 0, 0, 123, 7, 888};
  --iter;
  int i = fact.size() - 1;
  for (; iter != my_vec.begin(); --iter, --i) EXPECT_EQ(*iter, fact[i]);
  EXPECT_EQ(*iter, fact[i]);
}

TEST(Vector, Erase_1) {
  s21::vector<int> my_vec{7, 1, 2, 3, 4};
  std::vector<int> fact{7, 1, 2, 3, 4};
  my_vec.erase(my_vec.begin());
  fact.erase(fact.begin());
  EXPECT_EQ(my_vec.size(), fact.size());
  EXPECT_EQ(my_vec.capacity(), fact.capacity());
  for (size_t i = 0; i < fact.size(); ++i) {
    EXPECT_EQ(my_vec[i], fact[i]);
  }
}

TEST(Vector, Erase_2) {
  s21::vector<int> my_vec{7};
  std::vector<int> fact{7};
  my_vec.erase(my_vec.begin());
  fact.erase(fact.begin());
  EXPECT_EQ(my_vec.size(), fact.size());
  EXPECT_EQ(my_vec.capacity(), fact.capacity());
  for (size_t i = 0; i < fact.size(); ++i) {
    EXPECT_EQ(my_vec[i], fact[i]);
  }
}

TEST(Vector, Insert_1) {
  s21::vector<int> my_vec{3, 4, 5};
  s21::vector<int>::iterator it = my_vec.begin();
  std::vector<int> fact{3, 4, 5};
  std::vector<int>::iterator it_fact = fact.begin();
  it = my_vec.insert(it, 8);
  it_fact = fact.insert(it_fact, 8);
  EXPECT_EQ(my_vec.size(), fact.size());
  EXPECT_EQ(my_vec.capacity(), fact.capacity());
  for (size_t i = 0; i < fact.size(); ++i) {
    EXPECT_EQ(my_vec[i], fact[i]);
  }
}

TEST(Vector, Insert_2) {
  s21::vector<int> my_vec{3, 4, 5};
  my_vec.reserve(4);
  s21::vector<int>::iterator it = my_vec.begin();
  std::vector<int> fact{3, 4, 5};
  fact.reserve(4);
  std::vector<int>::iterator it_fact = fact.begin();
  it = my_vec.insert(it, 8);
  it_fact = fact.insert(it_fact, 8);
  EXPECT_EQ(my_vec.size(), fact.size());
  EXPECT_EQ(my_vec.capacity(), fact.capacity());
  for (size_t i = 0; i < fact.size(); ++i) {
    EXPECT_EQ(my_vec[i], fact[i]);
  }
}

TEST(Vector, Insert_3) {
  s21::vector<int> my_vec{3, 4, 5};
  s21::vector<int>::iterator it = my_vec.begin();
  ++it;
  std::vector<int> fact{3, 4, 5};
  std::vector<int>::iterator it_fact = fact.begin();
  ++it_fact;
  it = my_vec.insert(it, 8);
  it_fact = fact.insert(it_fact, 8);
  EXPECT_EQ(my_vec.size(), fact.size());
  EXPECT_EQ(my_vec.capacity(), fact.capacity());
  for (size_t i = 0; i < fact.size(); ++i) {
    EXPECT_EQ(my_vec[i], fact[i]);
  }
}

TEST(Vector, Insert_4) {
  s21::vector<int> my_vec{3, 4, 5};
  s21::vector<int>::iterator it = my_vec.end();
  std::vector<int> fact{3, 4, 5};
  std::vector<int>::iterator it_fact = fact.end();
  it = my_vec.insert(it, 8);
  it_fact = fact.insert(it_fact, 8);
  EXPECT_EQ(my_vec.size(), fact.size());
  EXPECT_EQ(my_vec.capacity(), fact.capacity());
  for (size_t i = 0; i < fact.size(); ++i) {
    EXPECT_EQ(my_vec[i], fact[i]);
  }
}

TEST(Vector, Insert_5) {
  s21::vector<int> my_vec;
  s21::vector<int>::iterator it = my_vec.begin();
  std::vector<int> fact;
  std::vector<int>::iterator it_fact = fact.begin();
  it = my_vec.insert(it, 8);
  it_fact = fact.insert(it_fact, 8);
  EXPECT_EQ(my_vec.size(), fact.size());
  EXPECT_EQ(my_vec.capacity(), fact.capacity());
  for (size_t i = 0; i < fact.size(); ++i) {
    EXPECT_EQ(my_vec[i], fact[i]);
  }
}

TEST(Vector, Insert_6) {
  s21::vector<int> my_vec;
  s21::vector<int>::iterator it = my_vec.end();
  std::vector<int> fact;
  std::vector<int>::iterator it_fact = fact.end();
  it = my_vec.insert(it, 8);
  it_fact = fact.insert(it_fact, 8);
  EXPECT_EQ(my_vec.size(), fact.size());
  EXPECT_EQ(my_vec.capacity(), fact.capacity());
  for (size_t i = 0; i < fact.size(); ++i) {
    EXPECT_EQ(my_vec[i], fact[i]);
  }
}
