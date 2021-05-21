#include <algorithm>
#include <cassert>
#include <numeric>

#include "doctest/doctest.h"
#include "fmt/format.h"
#include "utility.hpp"

auto greatest_common_divisor(size_t a, size_t b) {
  // Euclid's algorithm,
  // https://en.wikipedia.org/wiki/Greatest_common_divisor#:~:text=Overview-,Definition,gcd(a%2C%20b).
  assert(a > 0 && b > 0);

  fmt::print("greatest common divisor between {} and {} is ", a, b);
  while (a != b) {
    if (a < b) {
      std::swap(a, b);
    }
    a = a - b;
  }
  fmt::print("{}\n", a);

  return a;
}

TEST_CASE(util::problem_name().data()) {
  for (int i = 0; i < 10; i++) {
    const auto a = util::random_integer();
    const auto b = util::random_integer();
    CHECK(greatest_common_divisor(a, b) == std::gcd(a, b));
  }
}