#include <iostream>
#include <vector>

int FindPrefix(const std::string& s, std::vector<int>& prefix, int k, char a) {
  while ((k != 0) && (a != s[k])) {
    k = prefix[k - 1];
  }

  return k + (a == s[k]);
}

void PrefixFunction(const std::string& s, int& charged, int& discharged) {
  std::vector<int> prefix(s.size(), 0);

  for (size_t i = 1; i < s.size(); ++i) {
    prefix[i] = FindPrefix(s, prefix, prefix[i - 1], s[i]);
  }

  if (prefix.back() == charged - 1) {
    return;
  }

  charged = FindPrefix(s, prefix, prefix.back(), '1');
  discharged = FindPrefix(s, prefix, prefix.back(), '0');
}

int CompareSum(std::string first, std::string second) {
  int res = 0;

  for (size_t i = 0; i < first.size(); ++i) {
    if (first[i] == '1') {
      ++res;
    }

    if (second[i] == '1') {
      --res;
    }
  }

  return res;
}

int main() {
  int n;
  std::cin >> n;
  std::string s1, s2;
  std::cin >> s1 >> s2;
  int res = CompareSum(s1, s2);

  if (res == 0) {
    int charged_left, charged_right, discharged_left, discharged_right;
    charged_left = charged_right = discharged_left = discharged_right = n;
    PrefixFunction(s1 + '#' + s2, charged_left, discharged_left);
    PrefixFunction(s2 + '#' + s1, charged_right, discharged_right);
    bool is_charged = charged_left + charged_right >= n;
    bool is_discharged = discharged_left + discharged_right >= n;
    
    if (is_charged && is_discharged) {
      std::cout << "Random";
    } else {
      std::cout << (is_charged ? "Yes" : "No");
    }
  } else {
    std::cout << (res > 0 ? "Yes" : "No");
  }
  return 0;
}
