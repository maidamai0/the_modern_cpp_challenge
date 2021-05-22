#include <cmath>

#include "doctest/doctest.h"
#include "fmt/format.h"
#include "utility.hpp"

auto sum_proper_divisors(int const number) {
  int result = 1;
  for (int i = 2; i <= std::sqrt(number); i++) {
    if (number % i == 0) {
      result += (i == (number / i)) ? i : (i + number / i);
    }
  }
  return result;
}

void abundance(int const limit) {
  for (int number = 10; number <= limit; ++number) {
    auto sum = sum_proper_divisors(number);
    if (sum > number) {
      fmt::print("{}, abundance = {}\n", number, sum - number);
    }
  }
}

TEST_CASE(util::problem_name().data()) {
  for (int i = 0; i < 10; ++i) {
    abundance(100);
  }
}