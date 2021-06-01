#include <regex>
#include <string>
#include <string_view>
#include <tuple>

#include "doctest/doctest.h"
#include "fmt/format.h"
#include "utility.hpp"

// in:  dd.mm.yyyy or dd-mm-yyyy
// out: yyyy-mm-dd
auto date_to_string(std::string&& date_str) {
  const auto dd = date_str.substr(0, 2);
  const auto mm = date_str.substr(3, 2);
  const auto yyyy = date_str.substr(6);

  return fmt::format("{}-{}-{}", yyyy, mm, dd);
}

auto format_date(std::string str) {
  std::regex re(R"((^.*)((\d{2})[.-](\d{2})[.-](\d{4}))(.*)$)");
  return std::regex_replace(str, re, "$1$5-$4-$3$6");
}

TEST_CASE(util::problem_name().data()) {
  CHECK(date_to_string("01.12.2017") == "2017-12-01");
  CHECK(format_date("sdshfdshfjshfoir84893201-12-2017fdsafds") == "sdshfdshfjshfoir8489322017-12-01fdsafds");
}