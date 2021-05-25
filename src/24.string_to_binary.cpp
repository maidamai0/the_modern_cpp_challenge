#include <array>
#include <cassert>
#include <string_view>
#include <vector>

#include "doctest/doctest.h"
#include "fmt/format.h"
#include "fmt/ranges.h"
#include "utility.hpp"

auto char_to_integer(const unsigned char c) {
  if ('0' <= c && c <= '9') {
    return c - '0';
  } else if ('a' <= c && c <= 'f') {
    return c - 'a' + 10;
  } else if ('A' <= c && c <= 'F') {
    return c - 'A' + 10;
  }
  assert(false && "invalid character");
  return 0;
}

auto str_2_bin(std::string_view str) {
  assert((str.size() & 0x01) == 0);
  unsigned char c;
  std::vector<unsigned char> chars;

  for (size_t i = 0; i < str.size(); i += 2) {
    unsigned char h = char_to_integer(str[i]) << 4;
    unsigned char l = char_to_integer(str[i + 1]);
    chars.push_back(h | l);
  }

  fmt::print("chars is [{}]\n", fmt::join(chars, ","));
  return chars;
}

TEST_CASE(util::problem_name().data()) {
  CHECK(str_2_bin("BAADF00D") == std::vector<unsigned char>{186, 173, 240, 13});
  CHECK(str_2_bin("010203040506") ==
        std::vector<unsigned char>{1, 2, 3, 4, 5, 6});
}