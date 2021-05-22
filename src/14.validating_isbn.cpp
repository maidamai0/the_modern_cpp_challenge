#include <string_view>

#include "doctest/doctest.h"
#include "fmt/format.h"
#include "utility.hpp"

const auto is_valid_isbn_10(std::string_view isbn) {
  int sum = 0;
  for (int i = 0; i < 10; ++i) {
    const char c = isbn[i];
    int digit = 0;
    if (c == 'X') {
      digit = 10;
    } else {
      digit = c - '0';
    }
    sum += ((10 - i) * digit);
  }

  const auto valid = (sum % 11 == 0);
  fmt::print("{} is a valid isbn:{}\n", isbn, valid);
  return valid;
}

TEST_CASE(util::problem_name().data()) {
  CHECK(is_valid_isbn_10("007462542X") == true);
  CHECK(is_valid_isbn_10("0112112425") == false);
}