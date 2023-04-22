#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <stdexcept>

class ArrayOutOfRange : public std::out_of_range {
 public:
  ArrayOutOfRange() : std::out_of_range("ArrayOutOfRange") {
  }
};

template <typename T, size_t N>
class Array {
 public:
  T arr[N];

  void Fill(const T& value) {
    std::fill(&arr[0], &arr[N], value);
  }

  void Swap(Array<T, N>& other) {
    std::swap(*this, other);
  }

  size_t Size() const noexcept {
    return N;
  }

  bool Empty() const noexcept {
    return N == 0;
  }

  T* Data() noexcept {
    return &arr[0];
  }

  const T* Data() const noexcept {
    return &arr[0];
  }

  T& Front() {
    return arr[0];
  }

  const T& Front() const {
    return arr[0];
  }

  T& Back() {
    return arr[N - 1];
  }

  const T& Back() const {
    return arr[N - 1];
  }

  T& At(size_t idx) {
    if (idx >= N) {
      throw ArrayOutOfRange();
    }

    return arr[idx];
  }

  const T& At(size_t idx) const {
    if (idx >= N) {
      throw ArrayOutOfRange();
    }

    return arr[idx];
  }

  T& operator[](size_t idx) {
    return arr[idx];
  }

  const T& operator[](size_t idx) const {
    return arr[idx];
  }
};

#endif