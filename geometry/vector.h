#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cstring>
#include <vector>
#include <memory>

namespace geometry {
  class Vector {
  public:
    Vector(int, int);
    Vector(const Point&, const Point&);

    Vector& operator+=(const Vector&);
    Vector& operator-=(const Vector&);
    Vector& operator*=(const int&);
    Vector& operator/=(const int&);

    Vector operator+(const Vector&) const;
    Vector operator-(const Vector&) const;
    Vector operator*(const int&);
    Vector operator/(const int&);

    Vector operator+() const;
    Vector operator-() const;

    bool operator==(const Vector&) const;

    std::string ToString() const;

    int GetX() const;
    int GetY() const;

  private:
    int x_;
    int y_;
  };

  Vector operator-(const Point&, const Point&);

  int CrossProduct(const Vector&);
  int DotProduct(const Vector&);

  int SquareLen(const Point&, const Point&);
  double SquareLen(const Segment&, const Point&);
}

#endif
