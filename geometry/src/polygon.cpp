#include "polygon.h"

namespace geometry {
  Polygon::Polygon(std::vector <Point>&& vector) : points_(vector) {}

  Polygon& Polygon::Move(const Vector& v) {
    for (Point p : points_) {
      p.Move(v);
    }

    return *this;
  }

  bool Polygon::ContainsPoint(const Point& p) const {
    Ray ray(p, Point(p.GetX(), p.GetY() + 1));
    int k = 0;

    for (int i = 0; i < points_.size(); ++i) {
      Point cur = points_[i], prev = points_[i == 0 ? points_.size() - 1 : i - 1];

      if (ray.CrossesSegment(Segment(prev, cur))) {
        k += 1;

        if (ray.ContainsPoint(cur)) {
          Point next = points_[i + 1 == points_.size() ? 0 : i + 1];
          int first = CrossProduct(ray.GetVector(), Vector(ray.GetPoint(), prev));
          int second = CrossProduct(ray.GetVector(), Vector(ray.GetPoint(), next));

          if (((first * second == 0) && (first + second > 0)) || (first * second < 0)) {
            k += 1;
          }
        }
      }
    }

    return k & 1;
  }
  bool Polygon::CrossesSegment(const Segment& s) const {
    for (int i = 0; i < points_.size(); ++i) {
      Point cur = points_[i], prev = points_[i == 0 ? points_.size() - 1 : i - 1];

      if (s.CrossesSegment(Segment(prev, cur))) {
        return true;
      }
    }

    return this->ContainsPoint(s.GetA());
  }

  Polygon* Polygon::Clone() const {
    Polygon* copy = new Polygon(*this);
    return copy;
  }

  std::string Polygon::ToString() const {
    std::string s = "Polygon(";

    for (int i = 0; i < points_.size(); ++i) {
      if (i != 0) {
        s += ", ";
      }

      s += points_[i].ToString();
    }

    return s + ")";
  }
}