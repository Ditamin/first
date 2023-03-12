#ifndef LINE_H
#define LINE_H

namespace geometry {
  class Line : public IShape {
  public:
    Line(const Point& a, const Point& b);
    Line& Move(const Vector& v) override;
    bool ContainsPoint(const Point& p) const override;
    bool CrossesSegment(const Segment& s) const override;
    Line* Clone() const override;
    std::string ToString() const override;

  private:
    int a_;
    int b_;
    int c_;
    Point p1_;
    Point p2_;
  };
}

#endif