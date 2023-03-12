#ifndef ISHAPE_H
#define ISHAPE_H

namespace geometry {
  class IShape {
  public:
    virtual IShape& Move(const Vector&) = 0;
    virtual bool ContainsPoint(const Point&) const = 0;
    virtual bool CrossesSegment(const Segment&) const = 0;
    virtual IShape* Clone() const = 0;
    virtual std::string ToString() const = 0;
  };
}

#endif