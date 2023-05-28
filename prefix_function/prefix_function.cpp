#include <iostream>
#include <cstring>
#include <vector>

void PrefixFunction(const std::string& s) {
  std::vector<int> prefix(s.size(), 0);

  for (size_t i = 1; i < s.size(); ++i) {
    int k = prefix[i - 1];

    while ((k != 0) && (s[i] != s[k])) {
      k = prefix[k - 1];
    }

    if (s[i] == s[k]) {
      ++k;
    }

    prefix[i] = k;
  }

  for (auto i : prefix) {
    std::cout << i << " ";
  }
}

int main() {
  std::string s;
  std::cin >> s;
  PrefixFunction(s);
  return 0;
}
