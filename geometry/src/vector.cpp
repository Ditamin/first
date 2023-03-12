#include "vector.h"

namespace geometry {
  Vector::Vector(int x, int y) : x_(x), y_(y) {}

  Vector::Vector(const Point& a, const Point& b) {
    x_ = b.GetX() - a.GetX();
    y_ = b.GetY() - a.GetY();
  }

  Vector& Vector::operator+=(const Vector& v) {
    x_ += v.GetX();
    y_ += v.GetY();
    return *this;
  }

  Vector& Vector::operator-=(const Vector& v) {
    x_ -= v.GetX();
    y_ -= v.GetY();
    return *this;
  }

  Vector& Vector::operator*=(const int& k) {
    x_ *= k;
    y_ *= k;
    return *this;
  }

  Vector& Vector::operator/=(const int& k) {
    x_ /= k;
    y_ /= k;
    return *this;
  }

  Vector Vector::operator+(const Vector& v) const {
    Vector res = *this;
    return res += v;
  }

  Vector Vector::operator-(const Vector& v) const {
    Vector res = *this;
    return res -= v;
  }

  Vector Vector::operator+() const {
    return *this;
  }

  Vector Vector::operator-() const {
    return Vector(-x_, -y_);
  }

  Vector Vector::operator*(const int& k) {
    return Vector(x_ * k, y_ * k);
  }

  Vector Vector::operator/(const int& k) {
    return Vector(x_ / k, y_ / k);
  }

  bool Vector::operator==(const Vector& v) const {
    return (x_ == v.x_) && (y_ == v.y_);
  }

  std::string Vector::ToString() const {
    return "Vector(" + std::to_string(x_) + ", " + std::to_string(y_) + ")";
  }

  int Vector::GetX() const {
    return x_;
  }

  int Vector::GetY() const {
    return y_;
  }

  Vector operator-(const Point& a, const Point& b) {
    return Vector(a.GetX() - b.GetX(), a.GetY() - b.GetY());
  }

  int DotProduct(const Vector& first, const Vector& second) {
    return first.GetX() * second.GetX() + first.GetY() * second.GetY();
  }

  int CrossProduct(const Vector& first, const Vector& second) {
    return first.GetX() * second.GetY() - first.GetY() * second.GetX();
  }

  int SquareLen(const Point& first, const Point& second) {
    return pow(first.GetX() - second.GetX(), 2) + pow(first.GetY() - second.GetY(), 2);
  }

  double SquareLen(const Segment& s, const Point& p) {
    Vector AB(s.GetA(), s.GetB()), AO(s.GetA(), p), BO(s.GetB(), p);

    if (DotProduct(AB, AO) <= 0) {
      return SquareLen(s.GetA(), p);
    }

    if (DotProduct(AB, BO) >= 0) {
      return SquareLen(s.GetB(), p);
    }

    return pow(CrossProduct(AB, AO), 2) / SquareLen(s.GetA(), s.GetB());
  }
}