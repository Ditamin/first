#include "line.h"

namespace geometry {
  Line::Line(const Point& a, const Point& b) : p1_(a), p2_(b) {
    Vector v(a, b);
    a_ = v.GetY();
    b_ = -v.GetX();
    c_ = -(a_ * a.GetX() + b_ * a.GetY());
  }

  Line& Line::Move(const Vector& v) {
    c_ -= v.GetX() * a_ + v.GetY() * b_;
  }

  bool Line::ContainsPoint(const Point& p) const {
    Vector AB(p1_, p2_), AO(p1_, p);
    return CrossProduct(AB, AO) == 0;
  }

  bool Line::CrossesSegment(const Segment& s) const {
    Vector AB(p1_, p2_), AC(p1_, s.GetA()), AD(p1_, s.GetB());
    return CrossProduct(AB, AC) * CrossProduct(AB, AD) <= 0;
  }

  Line* Line::Clone() const {
    Line* copy = new Line(*this);
    return copy;
  }

  std::string Line::ToString() const {
    return "Line(" + std::to_string(a_) + ", " + std::to_string(b_) + ", " + std::to_string(c_) + ")";
  }
}