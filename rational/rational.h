#ifndef RATIONAL_H
#define RATIONAL_H
#include <iostream>

int64_t GCD(int64_t a, int64_t b);

class RationalDivisionByZero : public std::exception {};

class Rational {
 private:
  int64_t p_;
  int64_t q_;

 public:
  Rational(int64_t p = 0, int64_t q = 1);  //  NOLINT
  Rational(const Rational& other);
  int64_t GetNumerator() const;
  void SetNumerator(int64_t p);
  int64_t GetDenominator() const;
  void SetDenominator(int64_t q);
  void Reduce();
};

Rational& operator+=(Rational& first, const Rational& second);
Rational& operator-=(Rational& first, const Rational& second);
Rational& operator*=(Rational& first, const Rational& second);
Rational& operator/=(Rational& first, const Rational& second);
Rational& operator++(Rational& a);
Rational operator++(Rational& a, int);
Rational& operator--(Rational& a);
Rational operator--(Rational& a, int);
Rational operator+(Rational a);
Rational operator-(Rational a);
Rational operator+(const Rational& first, const Rational& second);
Rational operator-(const Rational& first, const Rational& second);
Rational operator*(const Rational& first, const Rational& second);
Rational operator/(const Rational& first, const Rational& second);
bool operator<(const Rational& first, const Rational& second);
bool operator>(const Rational& first, const Rational& second);
bool operator==(const Rational& first, const Rational& second);
bool operator!=(const Rational& first, const Rational& second);
bool operator<=(const Rational& first, const Rational& second);
bool operator>=(const Rational& first, const Rational& second);
std::istream& operator>>(std::istream& is, Rational& val);
std::ostream& operator<<(std::ostream& os, const Rational& val);
#endif
