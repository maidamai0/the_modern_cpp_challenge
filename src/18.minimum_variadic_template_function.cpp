#include "doctest/doctest.h"
#include "fmt/format.h"
#include "utility.hpp"

template <typename T>
auto sum(T a) {
  return a;
}

template <typename T, typename... Args>
auto sum(T a, Args... b) {
  return sum(a) + sum(b...);
}

template <typename... Args>
auto sum(Args... args) {
  return sum(args...);
}

TEST_CASE(util::problem_name().data()) {
  CHECK(sum(1) == 1);
  CHECK(sum(1, 2) == 3);
  CHECK(sum(1, 2, 3) == 6);
  CHECK(sum(1, 2, 3, 4) == 10);
  CHECK(sum(1, 2, 3, 4, 5) == 15);
}