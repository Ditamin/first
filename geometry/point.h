#ifndef POINT_H
#define POINT_H

namespace geometry {
  class Point : public IShape {
  public:
    Point(int x, int y);
    Point(const Point&);
    int GetX() const;
    int GetY() const;

    Point& Move(const Vector& v) override;
    bool ContainsPoint(const Point& p) const override;
    bool CrossesSegment(const Segment& s) const override;
    Point* Clone() const override;
    std::string ToString() const override;

  private:
    int x_;
    int y_;
  };
}

#endif