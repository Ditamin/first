#include "point.h"

namespace geometry {
  Point::Point(int x, int y) : x_(x), y_(y) {}

  int Point::GetX() const {
    return x_;
  }

  int Point::GetY() const {
    return y_;
  }

  Point& Point::Move(const Vector& v) {
    x_ += v.GetX();
    y_ += v.GetY();
  }

  bool Point::ContainsPoint(const Point& p) const {
    return (x_ == p.GetX()) && (y_ == p.GetY());
  }

  bool Point::CrossesSegment(const Segment& s) const {
    Vector AB(s.GetA(), s.GetB()), AO(s.GetA(), *this), BO(s.GetB(), *this);
    return (CrossProduct(AB, AO) == 0) && (DotProduct(AB, AO) >= 0) && (DotProduct(AB, BO) <= 0);
  }

  Point* Point::Clone() const {
    Point* p = new Point(*this);
    return p;
  }

  std::string Point::ToString() const {
    return "Point(" + std::to_string(x_) + ", " + std::to_string(y_) + ")";
  }

  Point Segment::GetA() const {
    return a_;
  }

  Point Segment::GetB() const {
    return b_;
  }
}