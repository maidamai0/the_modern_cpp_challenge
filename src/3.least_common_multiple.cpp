#include <vector>

#include "doctest/doctest.h"
#include "fmt/format.h"

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
  const auto ret = (a * b) / gcd(a, b);
  fmt::print("least common multiple between {} and {} is {}\n", a, b, ret);
  return ret;
}

TEST_CASE("1,2") {
  CHECK(least_common_multiple(1, 2) == 2);
}

TEST_CASE("2,3") {
  CHECK(least_common_multiple(2, 3) == 6);
}

TEST_CASE("4,6") {
  CHECK(least_common_multiple(4, 6) == 12);
}