#include <cmath>

#include "doctest/doctest.h"
#include "fmt/format.h"
#include "utility.hpp"

auto largest_prime(size_t n) {
  for (size_t p = n; p > 1; p--) {
    if (util::is_prime(p)) {
      fmt::print("largest prime under {} is {}\n", n, p);
      return p;
    }
  }

  return n;
}

TEST_CASE(util::problem_name().data()) {
  CHECK(largest_prime(2) == 2);
  CHECK(largest_prime(3) == 3);
  CHECK(largest_prime(4) == 3);
  CHECK(largest_prime(5) == 5);
  CHECK(largest_prime(6) == 5);
  CHECK(largest_prime(7) == 7);
  CHECK(largest_prime(8) == 7);
  CHECK(largest_prime(9) == 7);
  CHECK(largest_prime(10) == 7);
  CHECK(largest_prime(11) == 11);
  CHECK(largest_prime(12) == 11);
  CHECK(largest_prime(13) == 13);
  CHECK(largest_prime(14) == 13);
  CHECK(largest_prime(15) == 13);
}