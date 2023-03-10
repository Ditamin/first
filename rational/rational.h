#ifndef RATIONAL_H
#define RATIONAL_H

int GCD(int a, int b);

class RationalDivisionByZero : public std::exception {};

class Rational {
public:
  Rational(int p = 0, int q = 1);  //  NOLINT
  Rational(const Rational& other);
  int GetNumerator() const;
  int GetDenominator() const;
  void SetNumerator(int p);
  void SetDenominator(int q);

private:
  int p_;
  int q_;
  void Reduce();
};

Rational& operator+=(Rational& first, const Rational& second);
Rational& operator-=(Rational& first, const Rational& second);
Rational& operator*=(Rational& first, const Rational& second);
Rational& operator/=(Rational& first, const Rational& second);

Rational& operator++(Rational& a);
Rational& operator--(Rational& a);
Rational operator++(Rational& a, int);
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
