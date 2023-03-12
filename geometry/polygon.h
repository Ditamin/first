#ifndef POLYGON_H
#define POLYGON_H

namespace geometry {
  class Polygon : public IShape {
  public:
    Polygon(std::vector <Point>&& vector);
    Polygon& Move(const Vector& v) override;
    bool ContainsPoint(const Point&) const override;
    bool CrossesSegment(const Segment&) const override;
    Polygon* Clone() const override;
    std::string ToString() const override;

  private:
    std::vector <Point> points_;
  };
}

#endif