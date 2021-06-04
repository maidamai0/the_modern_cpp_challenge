#include <algorithm>
#include <array>
#include <string>
#include <vector>

#include "doctest/doctest.h"
#include "fmt/format.h"
#include "utility.hpp"

enum class Status { running, suspend };
enum class Platform { bit_32, bit_64 };

struct Process {
  std::string name;
  std::string identifer;
  Status st;
  std::string account;
  size_t size;
  Platform platform;
};

auto print_processes(const std::vector<Process> processes) {
  std::array<size_t, 5> max_len;
  for (const auto p : processes) {
    max_len[0] = std::max(max_len[0], p.name.size());
    max_len[1] = std::max(max_len[1], p.identifer.size());
    max_len[2] = std::max(max_len[2], p.name.size());
    max_len[3] = std::max(max_len[3], p.account.size());
    max_len[4] = std::max(max_len[4], p.name.size());
  }

  for (const auto& p : processes) {
    fmt::print("{:25} {:8} {:12} {:15} {:10} {}\n", p.name, p.identifer,
               p.st == Status::running ? "Running" : "Suspended", p.account, p.size,
               p.platform == Platform::bit_32 ? "32 bit" : "64 bit");
  }
}

TEST_CASE(util::problem_name().data()) {
  print_processes({{"a.exe", "0", Status::running, "Administrator", 123456, Platform::bit_64},
                   {"bfdasjfknoad.exe", "034567", Status::running, "local", 123456, Platform::bit_64}});
}