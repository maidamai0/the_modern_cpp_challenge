#include <regex>
#include <string_view>
#include <tuple>

#include "doctest/doctest.h"
#include "fmt/format.h"
#include "utility.hpp"

auto is_plate(std::string&& plate) {
  std::regex plate_pattern{R"(^[A-Z]{3}-[A-Z]{2} (\d{3,4})$)"};
  std::smatch match;
  if (std::regex_search(plate, match, plate_pattern)) {
    fmt::print("number is {}\n", match[1].str());
    return std::make_pair(true, match[1].str());
  }

  return std::make_pair(false, std::string{});
}

TEST_CASE(util::problem_name().data()) {
  CHECK(is_plate("ABC-DE 123").first);
  CHECK(is_plate("ABC-DE 1234").first);
  CHECK(!is_plate("ABC-DEF 1234").first);
  CHECK(!is_plate("ABC-DE 12").first);
  CHECK(!is_plate("AB-DEF 234").first);
}