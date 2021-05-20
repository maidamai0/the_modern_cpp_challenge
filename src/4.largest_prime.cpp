#include <cmath>

#include "doctest/doctest.h"

auto largest_prime(size_t n) {
  // TODO (tonghao): 2021-05-20
  // complete this
  return n;
}

TEST_CASE("largest prime") {
  CHECK(largest_prime(1) == 1);
  CHECK(largest_prime(2) == 1);
  CHECK(largest_prime(3) == 3);
  CHECK(largest_prime(4) == 3);
  CHECK(largest_prime(5) == 5);
  CHECK(largest_prime(6) == 5);
  CHECK(largest_prime(7) == 7);
  CHECK(largest_prime(8) == 7);
  CHECK(largest_prime(9) == 7);
  CHECK(largest_prime(10) == 7);
  CHECK(largest_prime(10) == 11);
  CHECK(largest_prime(11) == 11);
  CHECK(largest_prime(12) == 11);
  CHECK(largest_prime(13) == 13);
  CHECK(largest_prime(14) == 13);
  CHECK(largest_prime(15) == 13);
}