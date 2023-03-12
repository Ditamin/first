#ifndef RAY_H
#define RAY_H

namespace geometry {
  class Ray : public IShape {
  public:
    Ray(const Point& a, const Point& b);
    Ray& Move(const Vector& v) override;
    bool ContainsPoint(const Point& p) const override;
    bool CrossesSegment(const Segment& s) const override;
    Ray* Clone() const override;
    std::string ToString() const override;

    Point GetPoint() const;
    Vector GetVector() const;

  private:
    Point o_;
    Vector v_;
  };
}

#endif