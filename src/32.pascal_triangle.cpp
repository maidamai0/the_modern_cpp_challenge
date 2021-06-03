#include <iomanip>
#include <iostream>
#include <utility>
#include <vector>

#include "doctest/doctest.h"
#include "fmt/format.h"
#include "fmt/ranges.h"
#include "utility.hpp"

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

  const auto len = n | 0x01;
  for (size_t l = 0; l < n; ++l) {
    std::cout << std::string(len - l, ' ');
    for (const auto& c : numbers[l]) {
      std::cout << c << " ";
    }
    std::cout << '\n';
  }
}

TEST_CASE(util::problem_name().data()) {
  pascal_triangle(10);
}