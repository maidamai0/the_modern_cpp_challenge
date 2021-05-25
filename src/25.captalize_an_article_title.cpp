#include <cctype>
#include <string>

#include "doctest/doctest.h"
#include "fmt/format.h"
#include "utility.hpp"

auto captalize_title(std::string&& str) {
  auto leading_space = true;
  for (auto& c : str) {
    if (std::isspace(c)) {
      leading_space = true;
      continue;
    }

    if (leading_space) {
      c = std::toupper(c);
      leading_space = false;
    }
  }
  fmt::print("{}\n", str);

  return str;
}

TEST_CASE(util::problem_name().data()) {
  CHECK(captalize_title("the c++ challenger") ==
        std::string("The C++ Challenger"));
}