#ifndef STRING_VIEW_H
#define STRING_VIEW_H

#include <iostream>

class StringViewOutOfRange : public std::out_of_range {
 public:
  StringViewOutOfRange() : std::out_of_range("StringViewOutOfRange") {
  }
};

class StringView {
 public:
  StringView() = default;
  StringView(const char*);  // NOLINT
  StringView(const char*, size_t);
  const char& operator[](size_t) const;
  const char& At(size_t) const;
  const char& Front() const;
  const char& Back() const;
  size_t Size() const;
  size_t Length() const;
  bool Empty() const;
  const char* Data() const;
  void Swap(StringView&);
  void RemovePrefix(size_t);
  void RemoveSuffix(size_t);
  StringView Substr(size_t, size_t);

 private:
  const char* sv_ = nullptr;
  size_t size_ = 0;
};

#endif