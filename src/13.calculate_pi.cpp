#include <random>

#include "doctest/doctest.h"
#include "fmt/format.h"
#include "utility.hpp"

/**
 * @brief calculate the PI
 * area of square a_s = std::pow(2r, 2);
 * area of circle a_c = pi* std::pow(r, 2);
 * pi = 4 * a_s / a_c;
 * @return auto
 */
auto calculate_pi() {
  std::random_device dev;
  std::mt19937 gen(dev());
  std::uniform_real_distribution<> dis(-1.0, 1.0);
  const int total = 10000000;
  auto in_circle = 0;
  for (int i = 0; i < total; ++i) {
    const auto x = dis(gen);
    const auto y = dis(gen);
    if (std::pow(x, 2) + std::pow(y, 2) < 1.0) {
      ++in_circle;
    }
  }

  return static_cast<float>(4 * in_circle) / total;
}

TEST_CASE(util::problem_name().data()) {
  const auto pi = calculate_pi();
  fmt::print("pi is {}\n", pi);
  CHECK(pi > 3.13);
  CHECK(pi < 3.15);
}