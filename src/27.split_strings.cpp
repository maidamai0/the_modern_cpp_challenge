#include <string>
#include <string_view>
#include <vector>

#include "doctest/doctest.h"
#include "fmt/format.h"
#include "fmt/ranges.h"
#include "utility.hpp"

auto split(std::string_view str, std::string_view delimeters) {
  std::vector<std::string> result;
  size_t start = 0;
  size_t current = 0;
  for (; current < str.size(); ++current) {
    if (delimeters.find(str[current]) != std::string_view::npos) {
      if (current - start > 0) {
        result.emplace_back(str.substr(start, current - start));
        start = current + 1;
      }
    }
  }

  if ((current > start) &&
      delimeters.find(str[current - 1]) == std::string_view::npos) {
    result.emplace_back(str.substr(start, current - start));
  }

  fmt::print("[{}]\n", fmt::join(result, ","));

  return result;
}

TEST_CASE(util::problem_name().data()) {
  CHECK(split("this,is.a sample!!", ",.! ") ==
        std::vector<std::string>{"this", "is", "a", "sample"});
  CHECK(split("this,is.a sample", ",.! ") ==
        std::vector<std::string>{"this", "is", "a", "sample"});
}