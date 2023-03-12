#include "segment.h"

namespace geometry {
  Segment::Segment(const Point& a, const Point& b) : a_(a), b_(b) {}

  Segment& Segment::Move(const Vector& v) {
    a_.Move(v);
    b_.Move(v);
    return *this;
  }

  bool Segment::ContainsPoint(const Point& p) const {
    Vector AB(a_, b_), AO(a_, p), BO(b_, p);
    return (CrossProduct(AB, AO) == 0) && (DotProduct(AB, AO) >= 0) && (DotProduct(AB, BO) <= 0);
  }

  bool Segment::CrossesSegment(const Segment& s) const {
    Line a(a_, b_), b(s.GetA(), s.GetB());
    return a.CrossesSegment(s) && b.CrossesSegment(*this) && (s.ContainsPoint(a_) || s.ContainsPoint(b_));
  }

  Segment* Segment::Clone() const {
    Segment* s = new Segment(*this);
    return s;
  }

  std::string Segment::ToString() const {
    return "Segment(" + a_.ToString() + ", " + b_.ToString() + ")";
  }
}