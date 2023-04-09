#include "string_view.h"
#include <stdexcept>

StringView::StringView(const char* ptr) : sv_(ptr) {  // NOLINT
  while (sv_[size_] != 0) {
    ++size_;
  }
}

StringView::StringView(const char* ptr, size_t size) : sv_(ptr), size_(size) {
}

const char& StringView::operator[](size_t idx) const {
  return sv_[idx];
}

const char& StringView::At(size_t idx) const {
  if (idx >= size_) {
    throw StringViewOutOfRange();
  }

  return sv_[idx];
}

const char& StringView::Front() const {
  return sv_[0];
}

const char& StringView::Back() const {
  return sv_[size_ - 1];
}

size_t StringView::Size() const {
  return size_;
}

size_t StringView::Length() const {
  return size_;
}

bool StringView::Empty() const {
  return size_ == 0;
}
const char* StringView::Data() const {
  return sv_;
}

void StringView::Swap(StringView& other) {
  std::swap(*this, other);
}

void StringView::RemovePrefix(size_t prefix_size) {
  sv_ += prefix_size;
  size_ -= prefix_size;
}

void StringView::RemoveSuffix(size_t suffix_size) {
  size_ -= suffix_size;
}

StringView StringView::Substr(size_t pos, size_t count = -1) {
  if (pos >= size_) {
    throw StringViewOutOfRange();
  }

  return StringView(&sv_[pos], std::min(count, Size() - pos));
}