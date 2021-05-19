#include <iostream>

#include "doctest/doctest.h"
#include "fmt/format.h"

auto sum_of_natuals(size_t limit) {
  size_t sum = 0;
  for (size_t i = 0; i <= limit; ++i) {
    if ((i % 3 == 0) || (i % 5 == 0)) {
      sum += i;
    }
  }

  fmt::print("sum is {}\n", sum);
  std::flush(std::cout);
  return sum;
}

TEST_CASE("1") {
  CHECK(sum_of_natuals(1) == 0);
}

TEST_CASE("3") {
  CHECK(sum_of_natuals(3) == 3);
}

TEST_CASE("5") {
  CHECK(sum_of_natuals(5) == (3 + 5));
}

TEST_CASE("15") {
  CHECK(sum_of_natuals(15) == (3 + 5 + 6 + 9 + 10 + 12 + 15));
}