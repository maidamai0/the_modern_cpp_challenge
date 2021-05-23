#include <cstdlib>
#include <limits>

#include "doctest/doctest.h"
#include "utility.hpp"

namespace temperature {
class Temperature;
namespace literals {
struct quatity {
  friend Temperature;
  double value = 0.0;
};
class celsius : public quatity {};
class kelvin : public quatity {};
class fahrenheit : public quatity {};

constexpr auto operator"" _cel(long double n) {
  return celsius{static_cast<double>(n)};
}

auto operator"" _k(long double n) {
  return kelvin{static_cast<double>(n)};
}

auto operator"" _f(long double n) {
  return fahrenheit{static_cast<double>(n)};
}
}  // namespace literals

class Temperature {
 public:
  explicit constexpr Temperature(literals::celsius&& celsius)
      : celsius_(celsius.value) {}
  explicit constexpr Temperature(literals::fahrenheit&& fahrenheit)
      : celsius_{(fahrenheit.value - 32) * 5 / 9} {}
  explicit constexpr Temperature(literals::kelvin&& k)
      : celsius_(k.value - 273.15) {}

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
  Temperature() = default;

 private:
  double celsius_ = 0.0;
};

}  // namespace temperature

TEST_CASE(util::problem_name().data()) {
  {
    using namespace temperature;
    using namespace temperature::literals;
    const auto temp = Temperature(32.0_cel);
    const auto temp_k = Temperature::from_kelvin(temp.kelvin());
    const auto temp_f = Temperature::from_fahrenheit(temp.fahrenheit());
    CHECK(temp == temp_k);
    CHECK(temp == temp_f);
    CHECK(temp_k == temp_f);
  }
}