#include <algorithm>   // std::swap, std::min
#include <cstddef>     // std::size_t
#include <iostream>
#include <iomanip>

class Array {
  friend std::ostream& operator <<(std::ostream& stream, const Array& Array);
  friend std::istream& operator >>(std::istream& stream, Array& Array);

  friend void swap(Array& l, Array& r) noexcept;

 public:
  Array(const std::size_t size = 0) : size_{size}, data_{new int[size_]} {
    for (std::size_t i{0}; i < size_; ++i) {
      data_[i] = 0;
    }
  }

  // TODO(reginell): Remove code duplication.
  Array(const Array &ob) : size_{ob.size_}, data_{new int[size_]} {
    for (std::size_t i{0}; i < size_; ++i) {
      data_[i] = ob.data_[i];
    }
  }

  // TODO(reginell): Remove code duplication.
  // Move constructor (C++11).
  Array(Array&& ob) noexcept : size_{ob.size_}, data_{ob.data_} {
    ob.data_ = nullptr;
    ob.size_ = 0;
  }

  Array& operator =(Array Array) {
    swap(*this, Array);
    return *this;
  }

  // Move assignment (C++11).
  Array& operator =(Array&& Array) noexcept {
    swap(*this, Array);
    return *this;
  }

  ~Array() {
    delete[] data_;
    data_ = nullptr;
    size_ = 0;
  }

  bool Contains(int value) const noexcept;
  Array Union(const Array& r) const;
  Array Intersect(const Array& r) const;

  const int operator [](const std::size_t i) const noexcept {
    return data_[i];
  }

  int& operator [](const std::size_t i) noexcept {
    return data_[i];
  }

 private:
  std::size_t size_;
  int*        data_;
};

bool Array::Contains(int value) const noexcept {
  for (std::size_t i{0}; i < size_; ++i) {
    if ((*this)[i] == value) {
      return true;
    }
  }
  
  return false;
}

Array Array::Union(const Array& r) const {
  const std::size_t kMaxUnionSize{size_ + r.size_};
  Array unions{kMaxUnionSize};

  std::size_t unions_size{};

  // If duplicates are in first array, we still store them.
  for (std::size_t i{0}; i < size_; ++i) {
    unions[unions_size++] = (*this)[i];
  }

  for (std::size_t i{0}; i < r.size_; ++i) {
    const auto value{r[i]};
    
    if (!unions.Contains(value)) {
      unions[unions_size++] = value;
    }
  }

  // Set size to a used one.
  unions.size_ = unions_size;

  return unions;
}

Array Array::Intersect(const Array& r) const {
  const std::size_t kMaxIntersectSize{std::min(size_, r.size_)};
  Array intersects{kMaxIntersectSize};

  std::size_t intersects_size{};

  for (std::size_t i{0}; i < size_; ++i) {
    const auto value{(*this)[i]};

    if (r.Contains(value)) {
      intersects[intersects_size++] = value;
    }
  }

  // Set size to a used one.
  intersects.size_ = intersects_size;

  return intersects;
}

std::ostream& operator <<(std::ostream& stream, const Array& a) {
  for (std::size_t i{0}; i < a.size_; ++i) {
    stream << a[i] << " ";
  }

  return stream;
}

std::istream& operator >> (std::istream& stream, Array& a) {
  std::cout << "Size: ";

  std::size_t size;
  stream >> size;

  Array tmp{size};

  for (std::size_t i{0}; i < tmp.size_; ++i) {
    std::cout << "Element[" << i << "]: ";
    stream >> tmp[i];
  }

  swap(tmp, a);

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

  std::cout << "Union 1st & 2nd: " << first.Union(second) << std::endl;
  std::cout << "Union 2nd & 1st: " << second.Union(first) << std::endl;
  
  std::cout << "Intersect 1st & 2nd: " << first.Intersect(second) << std::endl;
  std::cout << "Intersect 2nd & 1st: " << second.Intersect(first) << std::endl;

  return 0;
}
