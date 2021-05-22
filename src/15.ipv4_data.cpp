#include <array>
#include <cassert>
#include <ios>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

#include "doctest/doctest.h"
#include "fmt/format.h"
#include "fmt/ranges.h"
#include "utility.hpp"

class IPV4 {
  using data_t = unsigned char;

 public:
  constexpr IPV4() = default;
  constexpr IPV4(data_t a, data_t b, data_t c, data_t d)
      : address_{a, b, c, d} {}

  explicit constexpr IPV4(uint32_t a)
      : address_{static_cast<data_t>((a >> 24) & 0xFF),
                 static_cast<data_t>((a >> 16) & 0xFF),
                 static_cast<data_t>((a >> 8) & 0xFF),
                 static_cast<data_t>(a & 0xFF)} {}

  constexpr IPV4(const IPV4& other) { address_ = other.address_; }
  constexpr IPV4& operator=(const IPV4& other) {
    address_ = other.address_;
    return *this;
  }

  explicit IPV4(std::string a) {
    std::stringstream ss(a);
    ss >> *this;
  }

  auto to_string() const {
    return fmt::format("{}.{}.{}.{}", address_[0], address_[1], address_[2],
                       address_[3]);
  }

  auto to_uint32() const {
    return static_cast<uint32_t>(address_[0] << 24) |
           static_cast<uint32_t>(address_[1] << 16) |
           static_cast<uint32_t>(address_[2] << 8) |
           static_cast<uint32_t>(address_[3]);
  }

  friend std::ostream& operator<<(std::ostream& os, IPV4 ipv4) {
    os << ipv4.to_string();
    return os;
  }

  friend std::istream& operator>>(std::istream& is, IPV4& ipv4) {
    int a = 0;
    data_t dot_a = 0;
    int b = 0;
    data_t dot_b = 0;
    int c = 0;
    data_t dot_c = 0;
    int d = 0;
    is >> a >> dot_a >> b >> dot_b >> c >> dot_c >> d;
    if (dot_a == '.' && dot_b == '.' && dot_c == '.') {
      ipv4 = IPV4(a, b, c, d);
    } else {
      is.setstate(std::ios_base::badbit);
    }
    return is;
  }

 private:
  auto from_string(const std::string& str) {
    size_t start = 0;
    const auto end = std::string::npos;
    std::vector<std::string> ret;
    while (start != end) {
      const auto new_start = str.find('.', start);
      if (new_start == end) {
        break;
      }

      ret.push_back(str.substr(start, new_start - start));
      start = new_start;
    }

    if (start != end) {
      ret.push_back(str.substr(start));
    }

    return ret;
  }

 private:
  std::array<data_t, 4> address_{};
};

TEST_CASE(util::problem_name().data()) {
  for (auto& str : {"127.0.0.1", "1.2.3.4"}) {
    IPV4 ipv4(str);
    CHECK(ipv4.to_string() == str);
  }

  for (int i = 0; i < 300; ++i) {
    IPV4 ipv4(i);
    CHECK(ipv4.to_uint32() == i);
  }
}