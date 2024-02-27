#include <gtest/gtest.h>

#include <list>

#include "s21_containers.h"

TEST(List, Constructor_1) {
  s21::list<int> my_list;
  std::list<int> fact;
  EXPECT_EQ(my_list.size(), fact.size());
}

TEST(List, Constructor_2) {
  s21::list<int> my_list{1, 2, 3, 4, 5, 6, 7, 8};
  EXPECT_EQ(my_list.size(), 8);
  int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
  s21::list<int>::iterator iter = my_list.begin();
  s21::list<int>::iterator iter_end = my_list.end();
  for (int *ptr_arr = arr; iter != iter_end; ++iter, ++ptr_arr) {
    EXPECT_EQ(*iter, *ptr_arr);
  }
}

TEST(List, Constructor_3) {
  s21::list<int> my_list(8);
  std::list<int> fact(8);
  EXPECT_EQ(my_list.size(), fact.size());
}

TEST(List, Copy_Constructor_1) {
  s21::list<int> ls{101, 5, 6, 6, 3, 3, 444};
  s21::list<int> ls2(ls);
  auto it_src = ls.begin();
  auto it_res = ls2.begin();
  auto it_res_end = ls2.end();
  for (; it_res != it_res_end; ++it_src, ++it_res) {
    EXPECT_EQ(*it_src, *it_res);
  }
  EXPECT_EQ(ls2.size(), 7);
}

TEST(List, Copy_Constructor_2) {
  s21::list<int> ls{101, 5, 6, 6, 3, 3, 444};
  s21::list<int> ls2(ls);
  auto it_src = ls.begin();
  auto it_res = ls2.begin();
  auto it_res_end = ls2.end();
  for (; it_res != it_res_end; ++it_src, ++it_res) {
    EXPECT_EQ(*it_src, *it_res);
  }
  EXPECT_EQ(ls2.size(), 7);
}

TEST(List, Move_Constructor_1) {
  s21::list<int> ls{10, 15, 3, 2, 1, 11, 5};
  s21::list<int> ls2 = std::move(ls);
  s21::list<int> ls3{10, 15, 3, 2, 1, 11, 5};
  auto it_src = ls3.begin();
  auto it_res = ls2.begin();
  auto it_res_end = ls2.end();
  for (; it_res != it_res_end; ++it_src, ++it_res) {
    EXPECT_EQ(*it_src, *it_res);
  }
  EXPECT_EQ(ls2.size(), 7);
  EXPECT_EQ(ls.size(), 0);
}

TEST(List, push_front_1) {
  s21::list<int> my_list;
  std::list<int> fact;
  my_list.push_front(5);
  my_list.push_front(8);
  my_list.push_front(9);
  fact.push_front(2);
  fact.push_front(7);
  fact.push_front(55);
  EXPECT_EQ(my_list.size(), fact.size());
}

TEST(List, push_front_2) {
  s21::list<int> my_list(8);
  std::list<int> fact(8);
  my_list.push_front(123);
  fact.push_front(321);
  EXPECT_EQ(my_list.size(), fact.size());
}

TEST(List, push_back_1) {
  s21::list<int> my_list;
  std::list<int> fact;
  my_list.push_back(5);
  my_list.push_back(8);
  my_list.push_back(9);
  fact.push_back(2);
  fact.push_back(7);
  fact.push_back(55);
  EXPECT_EQ(my_list.size(), fact.size());
}

TEST(List, push_back_2) {
  s21::list<int> my_list(8);
  std::list<int> fact(8);
  my_list.push_back(123);
  my_list.push_back(13);
  fact.push_back(321);
  fact.push_back(31);
  EXPECT_EQ(my_list.size(), fact.size());
}

TEST(List, back_1) {
  s21::list<int> my_list;
  my_list.push_back(5);
  my_list.push_back(8);
  my_list.push_back(88);
  my_list.push_front(123);
  EXPECT_EQ(my_list.back(), 88);
}

TEST(List, back_2) {
  s21::list<int> my_list(8);
  my_list.push_back(123);
  my_list.push_back(13);
  my_list.push_front(123);
  EXPECT_EQ(my_list.back(), 13);
}

TEST(List, front_1) {
  s21::list<int> my_list;
  my_list.push_front(5);
  my_list.push_back(8);
  my_list.push_back(88);
  my_list.push_front(123);
  EXPECT_EQ(my_list.front(), 123);
}

TEST(List, front_2) {
  s21::list<int> my_list(8);
  my_list.push_front(123);
  my_list.push_front(13);
  my_list.push_back(123);
  EXPECT_EQ(my_list.front(), 13);
}

TEST(List, pop_back_1) {
  s21::list<int> my_list(3);
  my_list.push_front(10);
  my_list.push_front(13);
  my_list.push_back(1234);
  EXPECT_EQ(my_list.back(), 1234);
  my_list.pop_back();
  EXPECT_EQ(my_list.back(), 0);
  my_list.pop_back();
  EXPECT_EQ(my_list.back(), 0);
  my_list.pop_back();
  EXPECT_EQ(my_list.back(), 0);
  my_list.pop_back();
  EXPECT_EQ(my_list.back(), 10);
  my_list.pop_back();
  EXPECT_EQ(my_list.back(), 13);
  my_list.pop_back();
  EXPECT_EQ(my_list.size(), 0);
}

TEST(List, pop_front_1) {
  s21::list<int> my_list(1);
  my_list.push_front(10);
  my_list.push_front(13);
  EXPECT_EQ(my_list.front(), 13);
  EXPECT_EQ(my_list.size(), 3);
  my_list.pop_front();
  EXPECT_EQ(my_list.front(), 10);
  my_list.pop_front();
  EXPECT_EQ(my_list.front(), 0);
  my_list.pop_front();
  EXPECT_EQ(my_list.size(), 0);
}

TEST(List, ListIterator_1) {
  s21::list<int> my_list(8);
  my_list.push_front(123);
  my_list.push_front(7);
  my_list.push_front(888);
  s21::list<int>::iterator iter = my_list.begin();
  EXPECT_EQ(*iter, 888);
  ++iter;
  EXPECT_EQ(*iter, 7);
  ++iter;
  EXPECT_EQ(*iter, 123);
  --iter;
  EXPECT_EQ(*iter, 7);
}

TEST(List, ListIterator_2) {
  s21::list<int> my_list(3);
  my_list.push_back(5);
  my_list.push_front(4);
  my_list.push_front(3);
  s21::list<int>::iterator iter = my_list.end();
  --iter;
  EXPECT_EQ(*iter, 5);
}

TEST(List, ListIterator_3) {
  s21::list<int> my_list;
  my_list.push_front(5);
  my_list.push_front(4);
  my_list.push_front(3);
  s21::list<int>::iterator end_iter = my_list.end();
  s21::list<int>::iterator begin_iter = my_list.begin();
  --end_iter;
  ++begin_iter;
  ++begin_iter;
  EXPECT_TRUE(end_iter == begin_iter);
  --end_iter;
  EXPECT_TRUE(end_iter != begin_iter);
}

TEST(List, ListIterator_4) {
  s21::list<int> my_list;
  my_list.push_front(5);
  my_list.push_front(4);
  my_list.push_front(3);
  s21::list<int>::iterator end_iter = my_list.end();
  --end_iter;
  *end_iter = 7;
  EXPECT_EQ(*end_iter, 7);
  --end_iter;
  --end_iter;
  EXPECT_EQ(*end_iter, 3);
}

TEST(List, ListConstIterator_1) {
  s21::list<int> my_list{3, 4, 5};
  s21::list<int>::const_iterator iter = my_list.cend();
  --iter;
  --iter;
  --iter;
  EXPECT_EQ(*iter, 3);
}

TEST(List, Empty_1) {
  s21::list<int> my_list(8);
  std::list<int> fact(8);
  EXPECT_EQ(my_list.empty(), fact.empty());
}

TEST(List, Empty_2) {
  s21::list<int> my_list;
  std::list<int> fact;
  EXPECT_EQ(my_list.empty(), fact.empty());
}

TEST(List, Erase_1) {
  s21::list<int> my_list{9, 1, 8, 5, 7, 4, 0, 6};
  s21::list<int>::iterator my_it = my_list.begin();
  ++my_it;
  my_list.erase(my_it);
  std::list<int> orig_list{9, 8, 5, 7, 4, 0, 6};
  std::list<int>::iterator orig_it = orig_list.begin();
  my_it = my_list.begin();
  for (; orig_it != orig_list.end(); ++orig_it, ++my_it)
    EXPECT_EQ(*my_it, *orig_it);
}

TEST(List, Erase_2) {
  s21::list<int> my_list{9, 1, 8, 5, 7, 4, 0, 6};
  s21::list<int>::iterator my_it = my_list.begin();
  my_list.erase(my_it);
  std::list<int> orig_list{1, 8, 5, 7, 4, 0, 6};
  std::list<int>::iterator orig_it = orig_list.begin();
  my_it = my_list.begin();
  for (; orig_it != orig_list.end(); ++orig_it, ++my_it)
    EXPECT_EQ(*my_it, *orig_it);
}

TEST(List, Erase_3) {
  s21::list<int> my_list{9, 1, 8, 5, 7, 4, 0, 6};
  s21::list<int>::iterator my_it = my_list.end();
  --my_it;
  my_list.erase(my_it);
  std::list<int> orig_list{9, 1, 8, 5, 7, 4, 0};
  std::list<int>::iterator orig_it = orig_list.begin();
  my_it = my_list.begin();
  for (; orig_it != orig_list.end(); ++orig_it, ++my_it)
    EXPECT_EQ(*my_it, *orig_it);
}

TEST(List, Erase_4) {
  s21::list<int> my_list{9};
  s21::list<int>::iterator my_it = my_list.begin();
  my_list.erase(my_it);
  EXPECT_EQ(my_list.size(), 0);
}

TEST(List, Insert_1) {
  s21::list<int> my_list;
  s21::list<int>::iterator my_it = my_list.begin();
  s21::list<int>::iterator res_it = my_list.insert(my_it, 666);
  EXPECT_TRUE(res_it == my_list.begin());
  std::list<int> orig_list{666};
  std::list<int>::iterator orig_it = orig_list.begin();
  my_it = my_list.begin();
  for (; orig_it != orig_list.end(); ++orig_it, ++my_it)
    EXPECT_EQ(*my_it, *orig_it);
}

TEST(List, Insert_2) {
  s21::list<int> my_list{5};
  s21::list<int>::iterator my_it = my_list.begin();
  s21::list<int>::iterator res_it = my_list.insert(my_it, 77);
  EXPECT_TRUE(res_it == my_list.begin());
  std::list<int> orig_list{77, 5};
  std::list<int>::iterator orig_it = orig_list.begin();
  my_it = my_list.begin();
  for (; orig_it != orig_list.end(); ++orig_it, ++my_it)
    EXPECT_EQ(*my_it, *orig_it);
}

TEST(List, Insert_3) {
  s21::list<int> my_list{5};
  s21::list<int>::iterator my_it = my_list.end();
  s21::list<int>::iterator res_it = my_list.insert(my_it, 77);
  --my_it;
  EXPECT_TRUE(res_it == my_it);
  std::list<int> orig_list{5, 77};
  std::list<int>::iterator orig_it = orig_list.begin();
  my_it = my_list.begin();
  for (; orig_it != orig_list.end(); ++orig_it, ++my_it)
    EXPECT_EQ(*my_it, *orig_it);
}

TEST(List, Insert_4) {
  s21::list<int> my_list{4, 18, 5};
  s21::list<int>::iterator my_it = my_list.begin();
  ++my_it;
  s21::list<int>::iterator res_it = my_list.insert(my_it, 77);
  --my_it;
  EXPECT_TRUE(res_it == my_it);
  std::list<int> orig_list{4, 77, 18, 5};
  std::list<int>::iterator orig_it = orig_list.begin();
  my_it = my_list.begin();
  for (; orig_it != orig_list.end(); ++orig_it, ++my_it)
    EXPECT_EQ(*my_it, *orig_it);
}

TEST(List, Insert_5) {
  s21::list<int> my_list{4, 18, 5};
  s21::list<int>::iterator my_it = my_list.end();
  s21::list<int>::iterator res_it = my_list.insert(my_it, 33);
  --my_it;
  EXPECT_TRUE(res_it == my_it);
  std::list<int> orig_list{4, 18, 5, 33};
  std::list<int>::iterator orig_it = orig_list.begin();
  my_it = my_list.begin();
  for (; orig_it != orig_list.end(); ++orig_it, ++my_it)
    EXPECT_EQ(*my_it, *orig_it);
}

TEST(List, Merge_1) {
  s21::list<int> first_list{-7, 4, 5, 9, 78};
  s21::list<int> second_list{4, 5, 18};
  std::list<int> first_list_result{-7, 4, 4, 5, 5, 9, 18, 78};
  std::list<int> second_list_result;

  first_list.merge(second_list);
  auto it_first = first_list.begin();
  auto it_first_res = first_list_result.begin();
  auto it_first_res_end = first_list_result.end();
  for (; it_first_res != it_first_res_end; ++it_first_res, ++it_first) {
    EXPECT_EQ(*it_first, *it_first_res);
  }
  auto it_second = second_list.begin();
  auto it_second_res = second_list_result.begin();
  auto it_second_res_end = second_list_result.end();
  for (; it_second_res != it_second_res_end; ++it_second_res, ++it_second) {
    EXPECT_EQ(*it_second, *it_second_res);
  }
}

TEST(List, Merge_2) {
  s21::list<int> first_list;
  s21::list<int> second_list{4, 5, 18};
  std::list<int> first_list_result{4, 5, 18};
  std::list<int> second_list_result;

  first_list.merge(second_list);
  auto it_first = first_list.begin();
  auto it_first_res = first_list_result.begin();
  auto it_first_res_end = first_list_result.end();
  for (; it_first_res != it_first_res_end; ++it_first_res, ++it_first) {
    EXPECT_EQ(*it_first, *it_first_res);
  }
  auto it_second = second_list.begin();
  auto it_second_res = second_list_result.begin();
  auto it_second_res_end = second_list_result.end();
  for (; it_second_res != it_second_res_end; ++it_second_res, ++it_second) {
    EXPECT_EQ(*it_second, *it_second_res);
  }
}

TEST(List, Merge_3) {
  s21::list<int> first_list{-65, 78, 99};
  s21::list<int> second_list{-66};
  std::list<int> first_list_result{-66, -65, 78, 99};
  std::list<int> second_list_result;

  first_list.merge(second_list);
  auto it_first = first_list.begin();
  auto it_first_res = first_list_result.begin();
  auto it_first_res_end = first_list_result.end();
  for (; it_first_res != it_first_res_end; ++it_first_res, ++it_first) {
    EXPECT_EQ(*it_first, *it_first_res);
  }
  auto it_second = second_list.begin();
  auto it_second_res = second_list_result.begin();
  auto it_second_res_end = second_list_result.end();
  for (; it_second_res != it_second_res_end; ++it_second_res, ++it_second) {
    EXPECT_EQ(*it_second, *it_second_res);
  }
}
TEST(List, Merge_4) {
  s21::list<int> first_list{-65, 78, 99};
  s21::list<int> second_list;
  std::list<int> first_list_result{-65, 78, 99};
  std::list<int> second_list_result;

  first_list.merge(second_list);
  auto it_first = first_list.begin();
  auto it_first_res = first_list_result.begin();
  auto it_first_res_end = first_list_result.end();
  for (; it_first_res != it_first_res_end; ++it_first_res, ++it_first) {
    EXPECT_EQ(*it_first, *it_first_res);
  }
  auto it_second = second_list.begin();
  auto it_second_res = second_list_result.begin();
  auto it_second_res_end = second_list_result.end();
  for (; it_second_res != it_second_res_end; ++it_second_res, ++it_second) {
    EXPECT_EQ(*it_second, *it_second_res);
  }
}

TEST(List, Merge_5) {
  s21::list<int> first_list{-3};
  s21::list<int> second_list{8};
  std::list<int> first_list_result{-3, 8};
  std::list<int> second_list_result;

  first_list.merge(second_list);
  auto it_first = first_list.begin();
  auto it_first_res = first_list_result.begin();
  auto it_first_res_end = first_list_result.end();
  for (; it_first_res != it_first_res_end; ++it_first_res, ++it_first) {
    EXPECT_EQ(*it_first, *it_first_res);
  }
  auto it_second = second_list.begin();
  auto it_second_res = second_list_result.begin();
  auto it_second_res_end = second_list_result.end();
  for (; it_second_res != it_second_res_end; ++it_second_res, ++it_second) {
    EXPECT_EQ(*it_second, *it_second_res);
  }
}

TEST(List, Splice_1) {
  s21::list<int> first_list{78, -7, 9, 4, 0, 5, 78};
  s21::list<int> second_list{4, 5, 4, 4, 18};
  std::list<int> first_list_result{4, 5, 4, 4, 18, 78, -7, 9, 4, 0, 5, 78};
  std::list<int> second_list_result;

  auto it_first_const = first_list.cbegin();
  first_list.splice(it_first_const, second_list);

  auto it_first_res = first_list_result.begin();
  auto it_first_res_end = first_list_result.end();
  auto it_first = first_list.begin();
  for (; it_first_res != it_first_res_end; ++it_first, ++it_first_res) {
    EXPECT_EQ(*it_first, *it_first_res);
  }
  auto it_second = second_list.begin();
  auto it_second_res = second_list_result.begin();
  auto it_second_res_end = second_list_result.end();
  for (; it_second_res != it_second_res_end; ++it_second, ++it_second_res) {
    EXPECT_EQ(*it_second, *it_second_res);
  }
}

TEST(List, Splice_2) {
  s21::list<int> first_list{78, -7, 9, 4, 0, 5, 78};
  s21::list<int> second_list{4, 5, 4, 4, 18};
  std::list<int> first_list_result{78, -7, 9, 4, 0, 5, 78, 4, 5, 4, 4, 18};
  std::list<int> second_list_result;

  auto it_first_const = first_list.cend();
  first_list.splice(it_first_const, second_list);

  auto it_first_res = first_list_result.begin();
  auto it_first_res_end = first_list_result.end();
  auto it_first = first_list.begin();
  for (; it_first_res != it_first_res_end; ++it_first, ++it_first_res) {
    EXPECT_EQ(*it_first, *it_first_res);
  }
  auto it_second = second_list.begin();
  auto it_second_res = second_list_result.begin();
  auto it_second_res_end = second_list_result.end();
  for (; it_second_res != it_second_res_end; ++it_second, ++it_second_res) {
    EXPECT_EQ(*it_second, *it_second_res);
  }
}

TEST(List, Splice_3) {
  s21::list<int> first_list{78, -7, 9, 4, 0, 5, 78};
  s21::list<int> second_list{4, 5, 4, 4, 18};
  std::list<int> first_list_result{78, -7, 9, 4, 5, 4, 4, 18, 4, 0, 5, 78};
  std::list<int> second_list_result;

  auto it_first_const = first_list.cbegin();
  ++it_first_const;
  ++it_first_const;
  ++it_first_const;
  first_list.splice(it_first_const, second_list);

  auto it_first_res = first_list_result.begin();
  auto it_first_res_end = first_list_result.end();
  auto it_first = first_list.begin();
  for (; it_first_res != it_first_res_end; ++it_first, ++it_first_res) {
    EXPECT_EQ(*it_first, *it_first_res);
  }
  auto it_second = second_list.begin();
  auto it_second_res = second_list_result.begin();
  auto it_second_res_end = second_list_result.end();
  for (; it_second_res != it_second_res_end; ++it_second, ++it_second_res) {
    EXPECT_EQ(*it_second, *it_second_res);
  }
}

TEST(List, Splice_4) {
  s21::list<int> first_list{};
  s21::list<int> second_list{4, 5, 4, 4, 18};
  std::list<int> first_list_result{4, 5, 4, 4, 18};
  std::list<int> second_list_result;

  auto it_first_const = first_list.cbegin();
  first_list.splice(it_first_const, second_list);

  auto it_first_res = first_list_result.begin();
  auto it_first_res_end = first_list_result.end();
  auto it_first = first_list.begin();
  for (; it_first_res != it_first_res_end; ++it_first, ++it_first_res) {
    EXPECT_EQ(*it_first, *it_first_res);
  }
  auto it_second = second_list.begin();
  auto it_second_res = second_list_result.begin();
  auto it_second_res_end = second_list_result.end();
  for (; it_second_res != it_second_res_end; ++it_second, ++it_second_res) {
    EXPECT_EQ(*it_second, *it_second_res);
  }
}

TEST(List, Splice_5) {
  s21::list<int> first_list{4, 5, 4, 4, 18};
  s21::list<int> second_list;
  std::list<int> first_list_result{4, 5, 4, 4, 18};
  std::list<int> second_list_result;

  auto it_first_const = first_list.cbegin();
  first_list.splice(it_first_const, second_list);

  auto it_first_res = first_list_result.begin();
  auto it_first_res_end = first_list_result.end();
  auto it_first = first_list.begin();
  for (; it_first_res != it_first_res_end; ++it_first, ++it_first_res) {
    EXPECT_EQ(*it_first, *it_first_res);
  }
  auto it_second = second_list.begin();
  auto it_second_res = second_list_result.begin();
  auto it_second_res_end = second_list_result.end();
  for (; it_second_res != it_second_res_end; ++it_second, ++it_second_res) {
    EXPECT_EQ(*it_second, *it_second_res);
  }
}

TEST(List, Insert_front_1) {
  s21::list<int> my_list(8);
  my_list.push_front(123);  // 3
  my_list.push_front(7);    // 2
  my_list.push_front(888);  // 1
  s21::list<int>::iterator iter = my_list.begin();
  my_list.insert(iter, 777);
  EXPECT_EQ(my_list.size(), 12);
  EXPECT_EQ(my_list.front(), 777);
}

TEST(List, Insert_back_1) {
  s21::list<int> my_list(8);
  my_list.push_front(123);  // 2
  my_list.push_front(7);    // 1
  my_list.push_front(888);  // 0
  s21::list<int>::iterator iter = my_list.end();
  my_list.insert(iter, 444);
  EXPECT_EQ(my_list.size(), 12);
  EXPECT_EQ(my_list.back(), 444);
}

TEST(List, Swap_1) {
  s21::list<int> my_list{11, 22, 33};
  s21::list<int> swap_list{99, 88, 77, 66};
  swap_list.swap(my_list);
  auto iter = my_list.begin();
  EXPECT_EQ(*iter, 99);
  ++iter;
  EXPECT_EQ(*iter, 88);
  ++iter;
  EXPECT_EQ(*iter, 77);
  ++iter;
  EXPECT_EQ(*iter, 66);
  ++iter;
  EXPECT_EQ(*iter, 4);
  ++iter;
  EXPECT_EQ(*iter, 99);
  EXPECT_EQ(my_list.size(), 4);
  iter = swap_list.begin();
  EXPECT_EQ(*iter, 11);
  ++iter;
  EXPECT_EQ(*iter, 22);
  ++iter;
  EXPECT_EQ(*iter, 33);
  ++iter;
  EXPECT_EQ(*iter, 3);
  ++iter;
  EXPECT_EQ(*iter, 11);
  EXPECT_EQ(swap_list.size(), 3);
}

TEST(List, Swap_2) {
  s21::list<int> my_list;
  s21::list<int> swap_list{99, 88, 77};
  swap_list.swap(my_list);
  auto iter = my_list.begin();
  EXPECT_EQ(*iter, 99);
  ++iter;
  EXPECT_EQ(*iter, 88);
  ++iter;
  EXPECT_EQ(*iter, 77);
  ++iter;
  EXPECT_EQ(*iter, 3);
  ++iter;
  EXPECT_EQ(*iter, 99);
  EXPECT_EQ(my_list.size(), 3);
  iter = swap_list.begin();
  EXPECT_EQ(*iter, 0);
  ++iter;
  EXPECT_EQ(*iter, 0);
  EXPECT_EQ(swap_list.size(), 0);
}

TEST(List, Reverse_1) {
  s21::list<int> my_list{11, 22, 33, 44};
  my_list.reverse();
  std::list<int> res_list{44, 33, 22, 11};
  auto it = my_list.begin();
  auto it_res = res_list.begin();
  auto it_res_end = res_list.end();
  for (; it_res != it_res_end; ++it, ++it_res) {
    EXPECT_EQ(*it, *it_res);
  }
}

TEST(List, Unique_1) {
  s21::list<int> my_list{11, 22, 22, 22, 44, 33, 33, 44,
                         11, 11, 22, 33, 22, 22, 22};
  my_list.unique();
  std::list<int> res_list{11, 22, 44, 33, 44, 11, 22, 33, 22};
  auto it = my_list.begin();
  auto it_res = res_list.begin();
  auto it_res_end = res_list.end();
  for (; it_res != it_res_end; ++it, ++it_res) {
    EXPECT_EQ(*it, *it_res);
  }
}

TEST(List, Sort_1) {
  s21::list<int> my_list{12, 10, 15, 3, 2, 1, 11, 5, 12, 12, 12, 4, 6, 9, 8};
  std::list<int> res_list{12, 10, 15, 3, 2, 1, 11, 5, 12, 12, 12, 4, 6, 9, 8};
  my_list.sort();
  res_list.sort();
  auto it_my = my_list.begin();
  auto it_res = res_list.begin();
  auto it_res_end = res_list.end();
  for (; it_res != it_res_end; ++it_my, ++it_res) {
    EXPECT_EQ(*it_my, *it_res);
  }
}

TEST(List, Max_size_1) {
  s21::list<int> my_list{12, 10, 15, 3, 2, 1, 11, 5, 12, 12, 12, 4, 6, 9, 8};
  std::list<int> res_list{12, 10, 15, 3, 2, 1, 11, 5, 12, 12, 12, 4, 6, 9, 8};
  EXPECT_EQ(my_list.max_size(), res_list.max_size());
}

TEST(List, Emplace_1) {
  s21::list<int> my_list1{12, 10, 15, 3, 2, 1, 11, 5, 12, 12, 12, 4, 6, 9, 8};
  s21::list<int> my_list2{99, 100, 102, 89, 12, 10, 15, 3, 2, 1,
                          11, 5,   12,  12, 12, 4,  6,  9, 8};
  s21::list<int>::const_iterator it = my_list1.cbegin();
  my_list1.emplace(it, 99, 100, 102, 89);

  auto it_my = my_list1.begin();
  auto it_res = my_list2.begin();
  auto it_res_end = my_list2.end();

  for (; it_res != it_res_end; ++it_my, ++it_res) {
    EXPECT_EQ(*it_my, *it_res);
  }
  EXPECT_EQ(my_list1.size(), my_list2.size());
}

TEST(List, Emplace_2) {
  s21::list<int> my_list1{12, 10, 15, 3, 2, 1, 11, 5, 12, 12, 12, 4, 6, 9, 8};
  s21::list<int> my_list2{12, 10, 99, 100, 102, 89, 15, 3, 2, 1,
                          11, 5,  12, 12,  12,  4,  6,  9, 8};
  s21::list<int>::const_iterator it = my_list1.cbegin();
  ++it;
  ++it;
  my_list1.emplace(it, 99, 100, 102, 89);

  auto it_my = my_list1.begin();
  auto it_res = my_list2.begin();
  auto it_res_end = my_list2.end();

  for (; it_res != it_res_end; ++it_my, ++it_res) {
    EXPECT_EQ(*it_my, *it_res);
  }
  EXPECT_EQ(my_list1.size(), my_list2.size());
}

TEST(List, EmplaceBack_1) {
  s21::list<int> my_list1{12, 10, 15, 3, 2, 1, 11, 5, 12, 12, 12, 4, 6, 9, 8};
  s21::list<int> my_list2{12, 10, 15, 3, 2, 1,  11,  5,   12, 12,
                          12, 4,  6,  9, 8, 99, 100, 102, 89};
  my_list1.emplace_back(99, 100, 102, 89);

  auto it_my = my_list1.begin();
  auto it_res = my_list2.begin();
  auto it_res_end = my_list2.end();

  for (; it_res != it_res_end; ++it_my, ++it_res) {
    EXPECT_EQ(*it_my, *it_res);
  }
  EXPECT_EQ(my_list1.size(), my_list2.size());
}

TEST(List, EmplaceFront_1) {
  s21::list<int> my_list1{12, 10, 15, 3, 2, 1, 11, 5, 12, 12, 12, 4, 6, 9, 8};
  s21::list<int> my_list2{89, 102, 100, 99, 12, 10, 15, 3, 2, 1,
                          11, 5,   12,  12, 12, 4,  6,  9, 8};
  my_list1.emplace_front(99, 100, 102, 89);

  auto it_my = my_list1.begin();
  auto it_res = my_list2.begin();
  auto it_res_end = my_list2.end();

  for (; it_res != it_res_end; ++it_my, ++it_res) {
    EXPECT_EQ(*it_my, *it_res);
  }
  EXPECT_EQ(my_list1.size(), my_list2.size());
}
