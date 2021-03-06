// Copyright (c) 2017, reginell. All rights reserved.
// Use of this source code is governed by a BSD license that can be
// found in the LICENSE file.

#include <algorithm>  // std::swap, std::min, std::for_each
#include <cstddef>    // usize
#include <functional>
#include <initializer_list>
#include <iomanip>
#include <iostream>

using usize = std::size_t;

class Array {
  friend std::ostream& operator<<(std::ostream& stream, const Array& Array);
  friend std::istream& operator>>(std::istream& stream, Array& Array);

  friend void swap(Array& l, Array& r) noexcept;

 public:
  explicit Array(const usize size = 0) noexcept : size_{size}, data_{new int[size_]} {
    for (usize i{0}; i < size_; ++i) {
      data_[i] = 0;
    }
  }

  // Initializer list constructor (C++11).
  // TODO(reginell): Make explicit or stay the same?
  Array(std::initializer_list<int> items)
      : size_{items.size()}, data_{new int[size_]} {
    usize idx = 0;

    for (const int i : items) {
      data_[idx++] = i;
    }
  }

  // TODO(reginell): Remove code duplication.
  Array(const Array& ob) : size_{ob.size_}, data_{new int[size_]} {
    for (usize i{0}; i < size_; ++i) {
      data_[i] = ob.data_[i];
    }
  }

  // TODO(reginell): Remove code duplication.
  // Move constructor (C++11).
  Array(Array&& ob) noexcept : size_{ob.size_}, data_{ob.data_} {
    ob.data_ = nullptr;
    ob.size_ = 0;
  }

  Array& operator=(Array Array) noexcept {
    swap(*this, Array);
    return *this;
  }

  // Move assignment (C++11).
  Array& operator=(Array&& Array) noexcept {
    swap(*this, Array);
    return *this;
  }

  ~Array() {
    delete[] data_;
    data_ = nullptr;
    size_ = 0;
  }

  usize size() const noexcept { return size_; }

  bool Contains(int value) const noexcept;
  Array Union(const Array& r) const;
  Array Intersect(const Array& r) const;

  const int& operator[](const usize i) const noexcept { return data_[i]; }

  int& operator[](const usize i) noexcept { return data_[i]; }

 private:
  usize size_;
  int* data_;
};

// Range-based for loop support (C++11).
const int* begin(const Array& x) noexcept { return x.size() ? &x[0] : nullptr; }

// Range-based for loop support (C++11).
const int* end(const Array& x) noexcept { 
  const auto b{begin(x)};
  return b != nullptr ? b + x.size() : nullptr; 
}

bool Array::Contains(int value) const {
  const auto end_it = end(*this);
  return end_it != std::find_if(begin(*this), end_it,
                                [=](const auto& v) { return v == value; });
}

void when_do(bool when, std::function<void(void)> then) {
  if (when) then();
}

Array Array::Union(const Array& r) const {
  auto unions = Array(size_ + r.size_);
  usize unions_size{0};

  // If duplicates are in first array, we still store them.
  for (auto&& value : *this) unions[unions_size++] = value;

  // Append new from second array.
  for (auto&& value : r) {
    when_do(!unions.Contains(value), [&]() noexcept {
      unions[unions_size++] = value;
    });
  }

  // Set size to a used one.
  unions.size_ = unions_size;

  return unions;
}

Array Array::Intersect(const Array& r) const {
  auto intersects = Array(std::min(size_, r.size_));
  usize intersects_size{0};

  // Store only same values.
  for (auto&& value : *this) {
    when_do(r.Contains(value), [&]() noexcept { intersects[intersects_size++] = value; });
  }

  // Set size to a used one.
  intersects.size_ = intersects_size;

  return intersects;
}

std::ostream& operator<<(std::ostream& stream, const Array& a) {
  std::for_each(begin(a), end(a),
                [&stream](const auto& v) { stream << v << " "; });

  return stream;
}

std::istream& operator>>(std::istream& stream, Array& a) {
  std::cout << "Size: ";

  usize size;
  if (stream >> size) {
    auto tmp = Array(size);

    for (usize i{0}; i < tmp.size_; ++i) {
      std::cout << "Element[" << i << "]: ";

      if (!(stream >> tmp[i])) {
        break;
      }
    }

    swap(tmp, a);
  }

  return stream;
}

inline void swap(Array& l, Array& r) noexcept {
  std::swap(l.data_, r.data_);
  std::swap(l.size_, r.size_);
}

int main() {
  Array first;

  std::cout << "Input 1st array:" << std::endl;
  std::cin >> first;
  std::cout << "1st array is: " << first << std::endl;

  Array second{first};

  std::cout << "2nd array from copy: " << second << std::endl;
  std::cout << "Input 2nd array:" << std::endl;
  std::cin >> second;

  Array third = {1, 2, 3};
  std::cout << "Predefined third array: " << third << std::endl;

  std::cout << "Union 1st & 2nd: " << first.Union(second) << std::endl;
  std::cout << "Union 2nd & 1st: " << second.Union(first) << std::endl;
  std::cout << "Union 2nd & 3rd: " << second.Union(third) << std::endl;

  std::cout << "Intersect 1st & 2nd: " << first.Intersect(second) << std::endl;
  std::cout << "Intersect 2nd & 1st: " << second.Intersect(first) << std::endl;
  std::cout << "Intersect 2nd & 3rd: " << second.Intersect(third) << std::endl;

  return 0;
}
