#include <iostream>
#include <utility>
#include <vector>

#include "doctest/doctest.h"
#include "fmt/format.h"
#include "fmt/ranges.h"
#include "utility.hpp"

const auto digits(size_t n) {
  int w = 0;
  while (n) {
    n /= 10;
    w++;
  }

  return w;
}

auto pascal_triangle(size_t n) {
  std::vector<std::vector<size_t>> numbers(n);

  // level 1
  size_t max = 0;
  numbers[0] = std::move(std::vector<size_t>(1));
  for (size_t level = 2; level <= n; level++) {
    std::vector<size_t> sub_numbers(level);
    sub_numbers[0] = 1;
    sub_numbers[level - 1] = 1;
    for (size_t i = 1; i < level - 1; i++) {
      const auto x = numbers[level - 2][i - 1] + numbers[level - 2][i];
      sub_numbers[i] = x;
      max = std::max(max, x);
    }
    numbers[level - 1] = std::move(std::move(sub_numbers));
  }
  const auto max_width = digits(max) * 2;

  const auto len = (n | 0x01) * max_width;
  for (size_t l = 0; l < n; ++l) {
    std::cout << std::string((n - l - 1) * max_width / 2, ' ');
    for (const auto& c : numbers[l]) {
      std::cout << c << std::string(max_width - digits(c), ' ');
    }
    std::cout << '\n';
  }
}

TEST_CASE(util::problem_name().data()) {
  pascal_triangle(10);
}