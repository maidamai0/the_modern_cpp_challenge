#include <filesystem>

#include "doctest/doctest.h"
#include "fmt/format.h"
#include "utility.hpp"

auto directory_size() {
  size_t size = 0;
  for (const auto& fs : std::filesystem::recursive_directory_iterator(std::filesystem::current_path())) {
    size += fs.file_size();
  }

  fmt::print("size of {} is ", std::filesystem::current_path().string());
  if (size > 1000000000) {
    fmt::print("{:.2f}G\n", static_cast<double>(size) / 1000000000.0);
  } else if (size > 1000000) {
    fmt::print("{:.2f}M\n", static_cast<double>(size) / 1000000.0);
  } else if (size > 1000) {
    fmt::print("{:.2f}K\n", static_cast<double>(size) / 1000.0);
  } else {
    fmt::print("{}B\n", size);
  }
}

TEST_CASE(util::problem_name().data()) {
  directory_size();
}