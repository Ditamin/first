#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H

#include <iostream>

template <typename T>
class UniquePtr {
 public:
  UniquePtr() = default;

  explicit UniquePtr(T* ptr) : ptr_(ptr) {
  }

  UniquePtr(const UniquePtr&) = delete;

  UniquePtr(UniquePtr<T>&& other) noexcept {
    ptr_ = other.ptr_;
    other.ptr_ = nullptr;
  }

  ~UniquePtr() {
    Reset();
  }

  T* Release() {
    T* copy = ptr_;
    ptr_ = nullptr;
    return copy;
  }

  void Reset(T* ptr = nullptr) {
    if (ptr_ != ptr) {
      delete ptr_;
    }

    ptr_ = ptr;
  }

  void Swap(UniquePtr<T>& other) {
    std::swap(other.ptr_, ptr_);
  }

  T* Get() const {
    return ptr_;
  }

  UniquePtr& operator=(const UniquePtr&) = delete;

  UniquePtr& operator=(UniquePtr&& other) noexcept {
    Reset(other.ptr_);
    other.ptr_ = nullptr;
    return *this;
  }

  T& operator*() const {
    return *ptr_;
  }

  T* operator->() const {
    return ptr_;
  }

  explicit operator bool() const {
    return ptr_ != nullptr;
  }

 private:
  T* ptr_ = nullptr;
};

#endif