#include <string_view>

#include "doctest/doctest.h"
#include "fmt/format.h"
#include "utility.hpp"


TEST_CASE(util::problem_name().data()) {
  fmt::print("name is {}\n", util::problem_name());
}