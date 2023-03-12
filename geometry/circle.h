#ifndef CIRCLE_H
#define CIRCLE_H

namespace geometry {
  class Circle : public IShape {
  public:
    Circle(Point a, int r);
    Circle& Move(const Vector& v) override;
    bool ContainsPoint(const Point& p) const override;
    bool CrossesSegment(const Segment& s) const override;
    Circle* Clone() const override;
    std::string ToString() const override;

  private:
    Point center_;
    int r_;
  };
}

#endif