#include <math.h>

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>

namespace geometry {
class Vector;

class AbstractShape;
class Point;
class Segment;
class Ray;
class Line;
class Polygon;
class Circle;

class Vector {
 public:
  Vector(const Point& a, const Point& b);
  Vector(int x, int y) : x_(x), y_(y) {}
  int x_ = 0;
  int y_ = 0;

  int operator^(const Vector& other) const {
    return (x_ * other.y_) - (y_ * other.x_);
  }

  int operator*(const Vector& other) const {
    return x_ * other.x_ + y_ * other.y_;
  }
};

class AbstractShape {
 public:
  virtual bool ContainsPoint(const Point& p) const = 0;
  virtual bool CrossSegment(const Segment& s) const = 0;
  virtual AbstractShape* Clone() const = 0;
  virtual AbstractShape* Move(const Vector& v) = 0;
  virtual void Print() const = 0;
};

class Point : public AbstractShape {
 public:
  Point(const int& x, const int& y) : x_(x), y_(y) {}
  bool ContainsPoint(const Point& p) const override {
    return (p.x_ == x_ && p.y_ == y_);
  }
  bool CrossSegment(const Segment& s) const override;

  Point* Clone() const override {
    return new Point(x_, y_);
  }

  Point* Move(const Vector& v) override {
    x_ += v.x_;
    y_ += v.y_;
    return this;
  }
  void Print() const override {
    std::cout << x_ << ' ' << y_ << '\n';
  }
  int x_ = 0;
  int y_ = 0;
};

Vector::Vector(const Point& a, const Point& b) {
  x_ = b.x_ - a.x_;
  y_ = b.y_ - a.y_;
}

class Segment : public AbstractShape {
 public:
  Segment(const Point& a, const Point& b) : a_(a), b_(b) {}
  bool ContainsPoint(const Point& p) const override {}
  bool CrossSegment(const Segment& s) const override {}
  Segment* Clone() const override {}
  Segment* Move(const Vector& v) override {}
  void Print() const override {}

  Point a_;
  Point b_;
};

class Line : public AbstractShape {
 public:
  Line(const Point& a, const Point& b) : a_(a), b_(b) {}
  bool ContainsPoint(const Point& p) const override {}
  bool CrossSegment(const Segment& s) const override {}
  Line* Clone() const override {}
  Line* Move(const Vector& v) override {}
  void Print() const override {}

 private:
  Point a_;
  Point b_;
};

class Ray : public AbstractShape {
 public:
  Ray(const Point& a, const Point& b) : a_(a), b_(b) {}
  bool ContainsPoint(const Point& p) const override {}
  bool CrossSegment(const Segment& s) const override {}
  Ray* Clone() const override {}
  Ray* Move(const Vector& v) override {}
  void Print() const override {}

 private:
  Point a_;
  Point b_;
};

class Polygon : public AbstractShape {
 public:
  Polygon(const std::vector<Point>& points, const size_t& size)
      : points_(points), size_(size) {};

  bool ContainsPoint(const Point& p) const override {}
  bool CrossSegment(const Segment& s) const override {}
  Polygon* Clone() const override {}
  Polygon* Move(const Vector& v) override {}
  void Print() const override {}

 private:
  std::vector<Point> points_;
  size_t size_;
};

class Circle : public AbstractShape {
 public:
  Circle(const Point& center, const int& radius)
      : center_(center), radius_(radius) {}

  bool ContainsPoint(const Point& p) const override {}
  bool CrossSegment(const Segment& s) const override {}
  Circle* Clone() const override {}
  Circle* Move(const Vector& v) override {}
  void Print() const override {}

 private:
  Point center_;
  int radius_;
};

bool Point::CrossSegment(const Segment& s) const {
  Vector along_segment(s.b_.x_ - s.a_.x_, s.b_.y_ - s.a_.y_);
  Vector reversed_along_segment(s.a_.x_ - s.b_.x_, s.a_.y_ - s.b_.y_);
  Vector start_to_point(x_ - s.a_.x_, y_ - s.a_.y_);
  Vector end_to_point(x_ - s.b_.x_, y_ - s.b_.y_);

  bool on_line = ((along_segment ^ start_to_point) == 0);
  bool sharp_angle_from_start = ((along_segment * start_to_point) >= 0);
  bool sharp_angle_from_end = ((reversed_along_segment * end_to_point) >= 0);

  return on_line && sharp_angle_from_start && sharp_angle_from_end;
}

}  // namespace geometry

using geometry::Point;

void CheckFunctions(const geometry::AbstractShape* shape,
                    const geometry::Point& A, const geometry::Point& B) {
  if (shape->ContainsPoint(A)) {
    std::cout << "Given shape contains point A" << std::endl;
  } else {
    std::cout << "Given shape does not contain point A" << std::endl;
  }

  geometry::Segment AB(A, B);
  if (shape->CrossSegment(AB)) {
    std::cout << "Given shape crosses segment AB" << std::endl;
  } else {
    std::cout << "Given shape does not cross segment AB" << std::endl;
  }

  geometry::Vector ab(A, B);
  geometry::AbstractShape* clonedShape = shape->Clone();
  clonedShape->Move(ab)->Print();
  delete clonedShape;
}

int main() {
  geometry::AbstractShape* shape;
  char command[10];
  std::cin >> command;
  if (!strcmp(command, "point")) {
    int x, y;
    std::cin >> x >> y;
    shape = new geometry::Point(x, y);
  } else if (!strcmp(command, "segment")) {
    int x1, y1, x2, y2;
    std::cin >> x1 >> y1 >> x2 >> y2;
    shape =
        new geometry::Segment(geometry::Point(x1, y1), geometry::Point(x2, y2));
  } else if (!strcmp(command, "ray")) {
    int x1, y1, x2, y2;
    std::cin >> x1 >> y1 >> x2 >> y2;
    shape = new geometry::Ray(geometry::Point(x1, y1), geometry::Point(x2, y2));
  } else if (!strcmp(command, "line")) {
    int x1, y1, x2, y2;
    std::cin >> x1 >> y1 >> x2 >> y2;
    shape =
        new geometry::Line(geometry::Point(x1, y1), geometry::Point(x2, y2));
  } else if (!strcmp(command, "polygon")) {
    size_t n_points;
    std::cin >> n_points;
    std::vector<geometry::Point> points;
    points.reserve(n_points);
    for (size_t i = 0; i < n_points; ++i) {
      int x, y;
      std::cin >> x >> y;
      points.push_back(geometry::Point(x, y));
    }
    shape = new geometry::Polygon(points, n_points);
  } else if (!strcmp(command, "circle")) {
    int x, y;
    std::cin >> x >> y;
    Point center(x, y);
    int radius;
    std::cin >> radius;
    shape = new geometry::Circle(center, radius);
  } else {
    std::cerr << "Undefined command" << std::endl;
    return 1;
  }

  int ax, ay, bx, by;
  std::cin >> ax >> ay >> bx >> by;
  geometry::Point A(ax, ay), B(bx, by);

  CheckFunctions(shape, A, B);

  return 0;
}