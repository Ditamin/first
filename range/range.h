#ifndef RANGE_H
#define RANGE_H

#include <iostream>
#define REVERSE_RANGE_IMPLEMENTED

class Range {
 public:
  explicit Range(int end) : end_(end) {
    Check();
  }
  Range(int begin, int end) : begin_(begin), end_(end) {
    Check();
  }
  Range(int begin, int end, int step) : begin_(begin), end_(end), step_(step) {
    Check();
  }

  class Iterator {
   public:
    explicit Iterator(int begin, int end, int step) : it_(begin), end_(end), step_(step) {
    }
    Iterator(const Iterator& other) = default;

    Iterator& operator++() {
      it_ += step_;
      return *this;
    }

    Iterator operator++(int) {
      return Iterator(it_ += step_, end_, step_);
    }

    int operator->() {
      return it_;
    }

    int& operator*() {
      return it_;
    }

    bool operator!=(const Iterator& other) const {
      if (step_ * (it_ - end_) > 0) {
        return false;
      }

      return it_ != other.it_;
    }

   private:
    int it_;
    int end_;
    int step_;
  };

  Iterator begin() const {  // NOLINT
    return Iterator(begin_, end_, step_);
  }

  Iterator end() const {  // NOLINT
    return Iterator(end_, end_, step_);
  }

  class ReverseIterator {
   public:
    explicit ReverseIterator(int begin, int end, int step) : it_(begin), end_(end), step_(step) {
    }

    ReverseIterator(const ReverseIterator& other) = default;

    ReverseIterator& operator++() {
      it_ += step_;
      return *this;
    }

    ReverseIterator operator++(int) {
      return ReverseIterator(it_ += step_, end_, step_);
    }

    int operator->() {
      return it_;
    }

    int& operator*() {
      return it_;
    }

    bool operator!=(const ReverseIterator& other) const {
      if (step_ * (it_ - end_) > 0) {
        return false;
      }

      return it_ != other.it_;
    }

   private:
    int it_;
    int end_;
    int step_;
  };

  ReverseIterator rbegin() const {  // NOLINT
    int reverse = begin_ < end_ ? 1 : -1;
    int begin;

    if ((begin_ == end_) || (step_ == 0)) {
      begin = begin_ - reverse;
    } else {
      begin = begin_ + (end_ - begin_ - reverse) / step_ * step_;
    }

    return ReverseIterator(begin, begin_ - reverse, -step_);
  }

  ReverseIterator rend() const {  // NOLINT
    int reverse = begin_ < end_ ? 1 : -1;
    return ReverseIterator(begin_ - reverse, begin_, step_);
  }

 private:
  int begin_ = 0;
  int end_;
  int step_ = 1;

  void Check() {
    if ((end_ - begin_) * step_ <= 0) {
      begin_ = end_;
    }
  }
};

#endif