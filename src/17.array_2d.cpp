#include <vcruntime.h>

#include <algorithm>
#include <array>
#include <initializer_list>
#include <iostream>
#include <ostream>
#include <utility>
#include <vector>

#include "doctest/doctest.h"
#include "utility.hpp"

struct Foo {
  int a;
  int b;
  std::string ss;
};

template <size_t row, size_t col, typename T = int>
class Array2D {
  using value_type = T;
  using iterator = value_type*;
  using const_iterator = value_type const*;

 public:
  Array2D() : data_(std::vector<value_type>{col * row}) {}
  explicit Array2D(std::initializer_list<value_type>&& list)
      : data_{std::move(list)} {}

  Array2D(const Array2D& other) {
    if (this != &other) {
      data_ = other.data_;
    }
  }
  Array2D& operator=(const Array2D& other) {
    if (this != &other) {
      data_ = other.data_;
    }

    return *this;
  }

  Array2D(Array2D&& other) {
    if (this != &other) {
      data_ = std::move(other, data_);
    }
  }

  Array2D& operator=(Array2D&& other) {
    if (this != &other) {
      data_ = std::move(other.data_);
    }
  }

  Array2D& swap(Array2D& other) {
    if (this != &other) {
      auto temp = std::move(other.data_);
      other.data_ = std::move(data_);
      data_ = std::move(temp);
    }
  }

  void fill(const value_type v) { std::fill(data_.begin(), data_.end(), v); }
  T& at(size_t r, size_t c) const { return data_[r * col + c]; }
  size_t column_size() const { return col; }
  size_t row_size() const { return row; }

  iterator begin() { return data_.data(); }
  iterator end() { return data_.data() + data_.size(); }

  const_iterator begin() const { return data_.data(); }
  const iterator end() const { return data_.data() + data_.size(); }

  friend std::ostream& operator<<(std::ostream& os, const Array2D& a) {
    size_t index = 0;
    os << "[\n";
    for (size_t r = 0; r < row; ++r) {
      os << "   [ ";
      for (size_t c = 0; c < col; ++c) {
        os << a.data_[index++];
        if (c != col - 1) {
          os << ",";
        }
      }
      os << " ]\n";
    }

    os << "]\n";
    return os;
  }

 private:
  std::vector<value_type> data_;
};

TEST_CASE(util::problem_name().data()) {
  Array2D<2, 3> a{1, 2, 3, 4, 5, 6};
  std::cout << a;
}