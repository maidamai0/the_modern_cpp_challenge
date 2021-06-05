#include <chrono>
#include <iostream>
#include <ostream>
#include <thread>

#include "doctest/doctest.h"
#include "fmt/format.h"
#include "utility.hpp"

class StopWatch {
  using clock = std::chrono::system_clock;

 public:
  StopWatch() : start_{clock::now()} {}
  ~StopWatch() { fmt::print("Elapsed {}\n", *this); }

  auto Elapsed() const { return std::chrono::duration_cast<std::chrono::seconds>(clock::now() - start_).count(); }

 private:
  clock::time_point start_;
};

namespace fmt {
template <>
struct formatter<StopWatch> : formatter<double> {
  template <typename FormatContext>
  auto format(const StopWatch& sw, FormatContext& ctx) -> decltype(ctx.out()) {
    return formatter<double>::format(sw.Elapsed(), ctx);
  }
};
}  // namespace fmt

TEST_CASE(util::problem_name().data()) {
  StopWatch watch;
  fmt::print("Elapsed {}\n", watch);
  std::this_thread::sleep_for(std::chrono::seconds(1));
}