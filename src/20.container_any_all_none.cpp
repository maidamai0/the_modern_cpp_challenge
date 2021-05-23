#include <algorithm>
#include <array>
#include <cassert>
#include <list>
#include <vector>

#include "doctest/doctest.h"
#include "utility.hpp"

namespace internal {
template <typename C, typename T>
auto contains(const C& c, const T v) {
  return std::find(std::cbegin(c), std::cend(c), v) != std::cend(c);
}
}  // namespace internal

template <typename C = std::vector<int>, typename... Args>
auto contains_any(const C& c, Args... args) {
  return (internal::contains(c, args) || ...);
}

template <typename C = std::vector<int>, typename... Args>
auto contains_all(const C& c, Args... args) {
  return (internal::contains(c, args) && ...);
}

template <typename C = std::vector<int>, typename... Args>
auto contains_none(const C& c, Args... args) {
  return (!internal::contains(c, args) && ...);
}

TEST_CASE(util::problem_name().data()) {
  std::vector<int> v{1, 2, 3, 4, 5, 6};
  CHECK(contains_any(v, 0, 3, 30));
  std::array<int, 6> a{{1, 2, 3, 4, 5, 6}};
  CHECK(contains_all(a, 1, 3, 5, 6));
  std::list<int> l{1, 2, 3, 4, 5, 6};
  CHECK(!contains_none(l, 0, 6, 7));
}