#pragma once

#include <random>
#include <string_view>

#include "random"

namespace util {

/**
 * @brief Get problem name from test files, remove prifx number and file
 * extension
 *
 * @param file_name   source file name, such as 1.sum_of_naturals.cpp
 * @return auto       problem name
 */
inline auto problem_name() {
  std::string_view file_name = FILE_NAME;
  auto first_dot = file_name.find_first_of('.');
  if (first_dot == std::string_view::npos) {
    first_dot = 0;
  }
  const auto last_dot = file_name.find_last_of('.');
  return file_name.substr(first_dot, last_dot - first_dot);
}

inline auto random_integer() {
  std::random_device dev;
  std::mt19937 generator(dev());
  std::uniform_int_distribution<> distrib(1, 100000);
  return static_cast<size_t>(distrib(generator));
}

inline auto is_prime(size_t n) {
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

}  // namespace util