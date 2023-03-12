#include "circle.h"

namespace geometry {
  Circle::Circle(Point a, int r) : center_(a), r_(r) {}

  Circle& Circle::Move(const Vector& v) {
    center_.Move(v);
  }

  bool Circle::ContainsPoint(const Point& p) const {
    return SquareLen(p, center_) <= pow(r_, 2);
  }

  bool Circle::CrossesSegment(const Segment& s) const {
    return SquareLen(s, center_) <= pow(r_, 2);
  }

  Circle* Circle::Clone() const {
    Circle* copy = new Circle(*this);
    return copy;
  }

  std::string Circle::ToString() const {
    return "Circle(" + center_.ToString() + ", " + std::to_string(r_) + ")";
  }
}