#include <cmath>

#include "doctest/doctest.h"
#include "fmt/format.h"
#include "utility.hpp"

auto is_prime(size_t n) {
  if (n == 2 || n == 3) {
    return true;
  } else if (n <= 1 || (n % 2) == 0 || (n % 3) == 0) {
    return false;
  }

  int i = 5;
  while (i * i <= n) {
    if ((n % i) == 0 || (n % (i + 2)) == 0) {
      return false;
    }
    i += 6;
  }

  return true;
}

auto largest_prime(size_t n) {
  for (size_t p = n; p > 1; p--) {
    if (is_prime(p)) {
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