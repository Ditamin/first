#include "cstring.h"
#include <iostream>

size_t Strlen(const char* str) {
  size_t i = 0;

  while (str[i] != 0) {
    ++i;
  }

  return i;
}

int Strcmp(const char* first, const char* second) {
  return Strncmp(first, second, std::max(Strlen(first), Strlen(second)));
}

int Strncmp(const char* first, const char* second, size_t count) {
  size_t first_len = std::min(Strlen(first), count);
  size_t second_len = std::min(Strlen(second), count);

  if (first_len > second_len) {
    return 1;
  }

  if (first_len < second_len) {
    return -1;
  }

  for (size_t i = 0; i < first_len; ++i) {
    if (first[i] > second[i]) {
      return 1;
    }

    if (first[i] < second[i]) {
      return -1;
    }
  }

  return 0;
}

char* Strcpy(char* dest, const char* src) {
  return Strncpy(dest, src, Strlen(src) + 1);
}

char* Strncpy(char* dest, const char* src, size_t count) {
  size_t src_len = Strlen(src);

  for (size_t i = 0; i < count; ++i) {
    dest[i] = i < src_len + 1 ? src[i] : 0;
  }

  return dest;
}

char* Strcat(char* dest, const char* src) {
  return Strncat(dest, src, Strlen(src));
}

char* Strncat(char* dest, const char* src, size_t count) {
  count = std::min(Strlen(src), count);
  size_t dest_len = Strlen(dest);

  for (size_t i = 0; i < count; ++i) {
    dest[dest_len + i] = src[i];
  }

  dest[dest_len + count] = 0;
  return dest;
}

const char* Strchr(const char* str, char symbol) {
  size_t len = Strlen(str), i;

  for (i = 0; i <= len; ++i) {
    if (str[i] == symbol) {
      return &str[i];
    }
  }

  return nullptr;
}

const char* Strrchr(const char* str, char symbol) {
  int i;
  size_t len = Strlen(str);

  for (i = len; i >= 0; --i) {
    if (str[i] == symbol) {
      return &str[i];
    }
  }

  return nullptr;
}

size_t Strspn(const char* dest, const char* src) {
  size_t i = 0, len = Strlen(dest);

  while ((Strchr(src, dest[i]) != nullptr) && (i < len)) {
    ++i;
  }

  return i;
}

size_t Strcspn(const char* dest, const char* src) {
  size_t i = 0, len = Strlen(dest);

  while ((Strchr(src, dest[i]) == nullptr) && (i < len)) {
    ++i;
  }

  return i;
}

const char* Strpbrk(const char* dest, const char* breakset) {
  size_t len = Strlen(dest);

  for (size_t i = 0; i < len; ++i) {
    if (Strchr(breakset, dest[i])) {
      return &dest[i];
    }
  }

  return nullptr;
}

const char* Strstr(const char* str, const char* pattern) {
  int len_str = Strlen(str);
  int len_pattern = Strlen(pattern);

  for (int i = 0; i <= len_str - len_pattern; ++i) {
    bool equal = true;

    for (int j = 0; j < len_pattern; ++j) {
      if (pattern[j] != str[i + j]) {
        equal = false;
        break;
      }
    }

    if (equal) {
      return &str[i];
    }
  }

  return nullptr;
}