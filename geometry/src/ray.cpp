#include "ray.h"

namespace geometry {
  Ray::Ray(const Point& a, const Point& b) : o_(a), v_(a, b) {}

  Ray& Ray::Move(const Vector& v) {
    o_.Move(v);
  }

  bool Ray::ContainsPoint(const Point& p) const {
    Vector OA(o_, p);
    return (CrossProduct(v_, OA) == 0) && (DotProduct(v_, OA) >= 0);
  }

  bool Ray::CrossesSegment(const Segment& s) const {
    Vector AB(s.GetA(), s.GetB()), AO(s.GetA(), o_);
    return CrossProduct(AO, AB) * CrossProduct(v_, AO) <= 0;
  }

  Ray* Ray::Clone() const {
    Ray* copy = new Ray(*this);
    return copy;
  }

  std::string Ray::ToString() const {
    return "Ray(" + o_.ToString() + ", " + v_.ToString() + ")";
  }

  Point Ray::GetPoint() const {
    return o_;
  }

  Vector Ray::GetVector() const {
    return v_;
  }
}