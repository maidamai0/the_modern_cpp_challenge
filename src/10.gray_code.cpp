#include <bitset>
#include <string>

#include "doctest/doctest.h"
#include "fmt/format.h"
#include "utility.hpp"

unsigned int gray_encode(unsigned int const num) {
  return num ^ (num >> 1);
}
unsigned int gray_decode(unsigned int gray) {
  for (unsigned int bit = 1U << 31; bit > 1; bit >>= 1) {
    if (gray & bit) gray ^= bit >> 1;
  }
  return gray;
}

std::string to_binary(unsigned int value, int const digits) {
  const auto ret =
      std::bitset<32>(value).to_string().substr(32 - digits, digits);
  fmt::print("{} of {} is {}\n", value, digits, ret);
  return ret;
}

TEST_CASE(util::problem_name().data()) {
  CHECK(to_binary(12, 4) == std::string("1100"));
}