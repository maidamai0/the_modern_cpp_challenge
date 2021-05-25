#include <string_view>
#include <vector>

#include "doctest/doctest.h"
#include "fmt/format.h"
#include "utility.hpp"

auto join(std::vector<std::string>&& strs, unsigned char const delimiter) {
  std::string result;
  for (const auto& str : strs) {
    result += str;
    result.push_back(delimiter);
  }

  result.pop_back();  // remove last delimiter
  fmt::print("{}\n", result);
  return result;
}

TEST_CASE(util::problem_name().data()) {
  CHECK(join({"this", "is", "an", "example"}, ' ') ==
        std::string("this is an example"));
}