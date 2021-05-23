#include <cstdlib>
#include <limits>

#include "doctest/doctest.h"
#include "utility.hpp"

class Temperature {
 public:
  constexpr Temperature() = default;
  explicit constexpr Temperature(const double celsius) : celsius_(celsius) {}

  static Temperature from_fahrenheit(const double fahrenheit) {
    Temperature t;
    t.celsius_ = (fahrenheit - 32) * 5 / 9;
    return t;
  }

  static Temperature from_kelvin(const double k) {
    Temperature t;
    t.celsius_ = k - 273.15;
    return t;
  }

  auto celsius() const { return celsius_; }
  auto fahrenheit() const { return celsius_ * 9 / 5 + 32; }
  auto kelvin() const { return celsius_ + 273.15; }

  auto operator==(const Temperature& other) const {
    return std::abs(celsius_ - other.celsius_) <=
           std::numeric_limits<double>::epsilon();
  }

  Temperature& operator++(const int inc) {
    celsius_ += static_cast<double>(inc);
    return *this;
  }

 private:
  double celsius_ = 0.0;
};

constexpr auto operator"" _cel(long double n) {
  return Temperature(n);
}

auto operator"" _f(long double n) {
  return Temperature::from_fahrenheit(n);
}

auto operator"" _k(long double n) {
  return Temperature::from_kelvin(n);
}

TEST_CASE(util::problem_name().data()) {
  {
    const auto temp = 32.0_cel;
    const auto temp_k = Temperature::from_kelvin(temp.kelvin());
    const auto temp_f = Temperature::from_fahrenheit(temp.fahrenheit());
    CHECK(temp == temp_k);
    CHECK(temp == temp_f);
    CHECK(temp_k == temp_f);
  }
}