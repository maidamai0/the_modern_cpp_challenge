#include <iostream>

#include "doctest/doctest.h"
#include "fmt/format.h"
#include "utility.hpp"

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

TEST_CASE(util::problem_name().data()) {
  CHECK(sum_of_natuals(1) == 0);
  CHECK(sum_of_natuals(3) == 3);
  CHECK(sum_of_natuals(5) == (3 + 5));
  CHECK(sum_of_natuals(15) == (3 + 5 + 6 + 9 + 10 + 12 + 15));
}
