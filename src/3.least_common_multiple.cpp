#include <vector>
#include <numeric>

#include "doctest/doctest.h"
#include "fmt/format.h"
#include "utility.hpp"

auto gcd(size_t a, size_t b) {
  while (a != b) {
    if (a < b) {
      std::swap(a, b);
    }

    a = a - b;
  }

  return a;
}

// TODO (tonghao): 2021-05-20
// support multiple nums
auto least_common_multiple(size_t a, size_t b) {
  const auto ret = (a * b) / std::gcd(a, b);
  fmt::print("least common multiple between {} and {} is {}\n", a, b, ret);
  return ret;
}

TEST_CASE(util::problem_name().data()) {
  for (int i = 0; i < 10; i++) {
    const auto a = util::random_integer();
    const auto b = util::random_integer();
    CHECK(least_common_multiple(a, b) == std::lcm(a, b));
  }
}