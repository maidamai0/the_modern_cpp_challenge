#include <vector>

#include "doctest/doctest.h"
#include "utility.hpp"

template <typename C = std::vector<int>, typename... Args>
auto add_to_container(C& c) {
}

template <typename C = std::vector<int>, typename... Args>
auto add_to_container(C& c, typename C::value_type a, Args... args) {
  c.push_back(a);
  add_to_container(c, args...);
}

namespace fold_expr {
template <typename C, typename... Args>

auto add_to_container(C& c, Args... args) {
  (c.push_back(args), ...);
}
}  // namespace fold_expr

TEST_CASE(util::problem_name().data()) {
  {
    std::vector<int> a{};
    add_to_container(a, 1, 2, 3);
    CHECK(a.size() == 3);
    CHECK(a[0] == 1);
    CHECK(a[1] == 2);
    CHECK(a[2] == 3);
  }

  {
    std::vector<int> a{};
    fold_expr::add_to_container(a, 1, 2, 3);
    CHECK(a.size() == 3);
    CHECK(a[0] == 1);
    CHECK(a[1] == 2);
    CHECK(a[2] == 3);
  }
}