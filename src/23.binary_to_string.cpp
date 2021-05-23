#include <algorithm>
#include <array>
#include <iomanip>
#include <ios>
#include <iterator>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

#include "doctest/doctest.h"
#include "fmt/format.h"
#include "utility.hpp"

class CharMap {
  using char_type = unsigned char;
  using map_type = std::array<char_type, 16>;

 public:
  static const auto& GetInstance() {
    const static CharMap instance;
    return instance;
  }

  auto lower(char_type c) const { return get(c, lower_); }
  auto upper(char_type c) { return get(c, upper_); }

 private:
  CharMap() {
    for (size_t i = 0; i < 10; ++i) {
      lower_[i] = '0' + i;
      upper_[i] = lower_[i];
    }

    for (size_t i = 10; i < 16; ++i) {
      lower_[i] = 'a' + i - 10;
      upper_[i] = 'A' + i - 10;
    }
  }

  auto get(const char_type c, const map_type& map) const
      -> std::tuple<char_type, char_type> {
    const char_type index_high = ((c & 0xF0) >> 4);
    const char_type index_low = c & 0x0F;
    return std::make_tuple(map[index_high], map[index_low]);
  }

 private:
  map_type lower_;
  map_type upper_;
};

auto char_to_string(const unsigned char c) {
  const auto [h, l] = CharMap::GetInstance().lower(c);
  fmt::print("{} is 0x{:c}{:c}\n", c, h, l);
}

namespace internal {
void binary_to_string(std::string& str) {
}

template <typename... Bytes>
auto binary_to_string(std::string& str, unsigned char byte, Bytes... bytes) {
  const auto [h, l] = CharMap::GetInstance().lower(byte);
  str.push_back(h);
  str.push_back(l);
  binary_to_string(str, bytes...);
}
}  // namespace internal

template <typename... Bytes>
auto binary_to_string(Bytes... args) {
  std::string str;
  internal::binary_to_string(str, args...);
  fmt::print("{}\n", str);
  return str;
}

namespace ios {
template <typename Iterator>
auto to_hex_str(Iterator begin, Iterator end, const bool upper_case = false) {
  std::ostringstream ss;
  if (upper_case) {
    ss.setf(std::ios_base::uppercase);
  }

  while (begin != end) {
    ss << std::hex << std::setw(2) << std::setfill('0')
       << static_cast<int>(*begin);
    begin++;
  }
  return ss.str();
}

template <typename C>
auto binary_to_hex_str(C&& c, const bool upper_case = false) {
  return to_hex_str(std::begin(c), std::end(c), upper_case);
}
}  // namespace ios

TEST_CASE(util::problem_name().data()) {
  CHECK(binary_to_string(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
                         17) ==
        std::string("0102030405060708090a0b0c0d0e0f1011"));
  CHECK(ios::binary_to_hex_str(std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                                11, 12, 13, 14, 15, 16, 17}) ==
        std::string("0102030405060708090a0b0c0d0e0f1011"));
}