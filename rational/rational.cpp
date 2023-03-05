#include <iostream>
#include <cstring>

int64_t GCD(int64_t a, int64_t b) {
  if (a == 0) {
    return b;
  }
  return GCD(b % a, a);
}

class RationalDivisionByZero : public std::exception {};

class Rational {
 private:
  int64_t p_;
  int64_t q_;

 public:
  Rational(int64_t p = 0, int64_t q = 1) {  //  NOLINT
    p_ = p;
    SetDenominator(q);
  }
  Rational(const Rational& other) {
    p_ = other.p_;
    q_ = other.q_;
  }
  int64_t GetNumerator() const {
    return p_;
  }
  void SetNumerator(int64_t p) {
    p_ = p;
    Reduce();
  }
  int64_t GetDenominator() const {
    return q_;
  }
  void SetDenominator(int64_t q) {
    if (q == 0) {
      throw RationalDivisionByZero();
    }
    q_ = q;
    Reduce();
  }
  void Reduce() {
    if (q_ < 0) {
      q_ = -q_;
      p_ = -p_;
    }
    int gcd = abs(GCD(p_, q_));
    p_ /= gcd;
    q_ /= gcd;
  }
};

Rational& operator+=(Rational& first, const Rational& second) {
  int64_t p = first.GetNumerator(), q = first.GetDenominator();
  first.SetDenominator(1);
  first.SetNumerator(p * second.GetDenominator() + q * second.GetNumerator());
  first.SetDenominator(q * second.GetDenominator());
  return first;
}

Rational& operator-=(Rational& first, const Rational& second) {
  int64_t p = first.GetNumerator(), q = first.GetDenominator();
  first.SetDenominator(1);
  first.SetNumerator(p * second.GetDenominator() - q * second.GetNumerator());
  first.SetDenominator(q * second.GetDenominator());
  return first;
}

Rational& operator*=(Rational& first, const Rational& second) {
  int64_t p = first.GetNumerator(), q = first.GetDenominator();
  first.SetDenominator(1);
  first.SetNumerator(p * second.GetNumerator());
  first.SetDenominator(q * second.GetDenominator());
  return first;
}

Rational& operator/=(Rational& first, const Rational& second) {
  if (second.GetNumerator() == 0) {
    throw RationalDivisionByZero();
  }
  int64_t p = first.GetNumerator(), q = first.GetDenominator();
  first.SetDenominator(1);
  first.SetNumerator(p * second.GetDenominator());
  first.SetDenominator(q * second.GetNumerator());
  return first;
}

Rational& operator++(Rational& a) {
  return a += 1;
}

Rational operator++(Rational& a, int) {
  Rational temp = a;
  a += 1;
  return temp;
}

Rational& operator--(Rational& a) {
  return a -= 1;
}

Rational operator--(Rational& a, int) {
  Rational temp = a;
  a -= 1;
  return temp;
}

Rational operator+(Rational a) {
  return a;
}

Rational operator-(Rational a) {
  a.SetNumerator(-a.GetNumerator());
  return a;
}

Rational operator+(const Rational& first, const Rational& second) {
  Rational res;
  res.SetNumerator(first.GetNumerator() * second.GetDenominator() + first.GetDenominator() * second.GetNumerator());
  res.SetDenominator(first.GetDenominator() * second.GetDenominator());
  return res;
}

Rational operator-(const Rational& first, const Rational& second) {
  Rational res;
  res.SetNumerator(first.GetNumerator() * second.GetDenominator() - first.GetDenominator() * second.GetNumerator());
  res.SetDenominator(first.GetDenominator() * second.GetDenominator());
  return res;
}

Rational operator*(const Rational& first, const Rational& second) {
  Rational res;
  res.SetNumerator(first.GetNumerator() * second.GetNumerator());
  res.SetDenominator(first.GetDenominator() * second.GetDenominator());
  return res;
}

Rational operator/(const Rational& first, const Rational& second) {
  if (second.GetNumerator() == 0) {
    throw RationalDivisionByZero();
  }
  Rational res;
  res.SetNumerator(first.GetNumerator() * second.GetDenominator());
  res.SetDenominator(first.GetDenominator() * second.GetNumerator());
  return res;
}

bool operator<(const Rational& first, const Rational& second) {
  return first.GetNumerator() * second.GetDenominator() < first.GetDenominator() * second.GetNumerator();
}

bool operator>(const Rational& first, const Rational& second) {
  return second < first;
}

bool operator==(const Rational& first, const Rational& second) {
  return first.GetNumerator() * second.GetDenominator() == first.GetDenominator() * second.GetNumerator();
}

bool operator!=(const Rational& first, const Rational& second) {
  return !(first == second);
}

bool operator<=(const Rational& first, const Rational& second) {
  return !(first > second);
}

bool operator>=(const Rational& first, const Rational& second) {
  return !(first < second);
}

std::istream& operator>>(std::istream& is, Rational& val) {
  bool f = false;
  char s[50];
  is >> s;
  int64_t a = 0, b = 0, len = strlen(s), i;
  for (i = 0; i < len; ++i) {
    if (s[i] == '-') {
      f = !f;
    } else if (s[i] == '+') {
      continue;
    } else if (s[i] != '/') {
      a = a * 10 + s[i] - '0';
    } else {
      ++i;
      break;
    }
  }
  if (len == i) {
    b = 1;
  }
  for (; i < len; ++i) {
    if (s[i] == '-') {
      f = !f;
    } else if (s[i] != '+') {
      b = b * 10 + s[i] - '0';
    }
  }
  if (f) {
    a = -a;
  }
  val.SetDenominator(1);
  val.SetNumerator(a);
  val.SetDenominator(b);
  return is;
}

std::ostream& operator<<(std::ostream& os, const Rational& val) {
  if (val.GetDenominator() == 1) {
    os << val.GetNumerator();
  } else {
    os << val.GetNumerator() << "/" << val.GetDenominator();
  }
  return os;
}
