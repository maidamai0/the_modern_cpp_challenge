#include <algorithm>
#include <cassert>

#include "doctest/doctest.h"
#include "fmt/format.h"

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

TEST_CASE("1,2") {
  CHECK(greatest_common_divisor(1, 2) == 1);
}

TEST_CASE("4,2") {
  CHECK(greatest_common_divisor(4, 2) == 2);
}

TEST_CASE("4,2") {
  CHECK(greatest_common_divisor(47, 3) == 1);
}