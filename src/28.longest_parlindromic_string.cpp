#include <string_view>

#include "doctest/doctest.h"
#include "utility.hpp"

auto is_parlindromic(std::string_view str) {
  size_t left = 0;
  size_t right = str.size() - 1;

  while (left < right) {
    if (str[left] != str[right]) {
      return false;
    }
    ++left;
    --right;
  }

  return true;
}

auto longest_parlindromic_strng(std::string_view str) {
  auto len = str.size();
  while (len > 0) {
    for (auto left = 0; left <= str.size() - len; ++left) {
      if (is_parlindromic(str.substr(left, len))) {
        return str.substr(left, len);
      }
    }
    --len;
  }

  return std::string_view{};
}

TEST_CASE(util::problem_name().data()) {
  CHECK(longest_parlindromic_strng("sahararahnide") == "hararah");
  CHECK(longest_parlindromic_strng("level") == "level");
  CHECK(longest_parlindromic_strng("hello") == "ll");
  CHECK(longest_parlindromic_strng("abcd") == "a");
  CHECK(longest_parlindromic_strng("12345678") == "1");
}