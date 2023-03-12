#ifndef SEGMENT_H
#define SEGMENT_H

namespace geometry {
  class Segment : public IShape {
  public:
    Segment(const Point& a, const Point& b);
    Segment& Move(const Vector& v) override;
    bool ContainsPoint(const Point& p) const override;
    bool CrossesSegment(const Segment& s) const override;
    Segment* Clone() const override;
    std::string ToString() const override;

    Point GetA() const;
    Point GetB() const;

  private:
    Point a_;
    Point b_;
  };
}

#endif