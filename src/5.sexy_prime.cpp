#include "doctest/doctest.h"
#include "fmt/format.h"
#include "utility.hpp"

auto sexy_prime(size_t n) {
  for (size_t i = 0; i < n; ++i) {
    if (util::is_prime(i) && util::is_prime(n + 6)) {
      fmt::print("{},{}\n", n, n + 6);
    }
  }
}

TEST_CASE(util::problem_name().data()) {
  for (int i = 0; i < 10; ++i) {
    sexy_prime(util::random_integer());
  }
}