#include <iostream>
#include <cstring>
#include "rational.h"

int GCD(int a, int b) {
  if (a == 0) {
    return b;
  }
  return GCD(b % a, a);
}

Rational::Rational(int p = 0, int q = 1) {  //  NOLINT
    p_ = p;
    q_ = q;
    Reduce();
}

Rational::Rational(const Rational& other) {
    p_ = other.p_;
    q_ = other.q_;
}

int Rational::GetNumerator() const {
    return p_;
}

int Rational::GetDenominator() const {
    return q_;
}

void Rational::SetNumerator(int p) {
    p_ = p;
    Reduce();
}

void Rational::SetDenominator(int q) {
  if (q == 0) {
    throw RationalDivisionByZero();
   }

  q_ = q;
  Reduce();
}

void Rational::Reduce() {
  if (q_ < 0) {
    q_ = -q_;
    p_ = -p_;
  }

  int gcd = abs(GCD(p_, q_));
  p_ /= gcd;
  q_ /= gcd;
}

Rational& operator+=(Rational& first, const Rational& second) {
  first.SetDenominator(1);
  first.SetNumerator(first.GetNumerator() * second.GetDenominator() + first.GetDenominator() * second.GetNumerator());
  first.SetDenominator(first.GetDenominator() * second.GetDenominator());
  return first;
}

Rational& operator-=(Rational& first, const Rational& second) {
  first.SetDenominator(1);
  first.SetNumerator(first.GetNumerator() * second.GetDenominator() - first.GetDenominator() * second.GetNumerator());
  first.SetDenominator(first.GetDenominator() * second.GetDenominator());
  return first;
}

Rational& operator*=(Rational& first, const Rational& second) {
  first.SetDenominator(1);
  first.SetNumerator(first.GetNumerator() * second.GetNumerator());
  first.SetDenominator(first.GetDenominator() * second.GetDenominator());
  return first;
}

Rational& operator/=(Rational& first, const Rational& second) {
  if (second.GetNumerator() == 0) {
    throw RationalDivisionByZero();
  }

  first.SetDenominator(1);
  first.SetNumerator(first.GetNumerator() * second.GetDenominator());
  first.SetDenominator(first.GetDenominator() * second.GetNumerator());
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
  int a = 0, b = 0, len = strlen(s), i;

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
