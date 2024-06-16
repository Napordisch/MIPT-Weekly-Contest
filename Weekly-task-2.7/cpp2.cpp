#include <math.h>

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>

int square(const int& number) { return number * number; }

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
  virtual ~AbstractShape() = default;
};

class Point : public AbstractShape {
 public:
  Point() = default;
  Point(const int& x, const int& y) : x_(x), y_(y) {}
  Point(const Point& p) {
    x_ = p.x_;
    y_ = p.y_;
  }
  bool operator==(const Point& other) { return ContainsPoint(other); }
  bool ContainsPoint(const Point& p) const override {
    return (p.x_ == x_ && p.y_ == y_);
  }
  bool CrossSegment(const Segment& s) const override;

  Point* Clone() const override { return new Point(x_, y_); }

  Point* Move(const Vector& v) override {
    x_ += v.x_;
    y_ += v.y_;
    return this;
  }
  void Print() const override { std::cout << x_ << ' ' << y_ << '\n'; }

  int x_ = 0;
  int y_ = 0;
};

int squared_distance(const Point& a, const Point& b) {
  return square(b.x_ - a.x_) + square(b.y_ - a.y_);
}

bool operator==(const Point& one, const Point& two) {
  return (one.x_ == two.x_ && one.y_ == two.y_);
}

Vector::Vector(const Point& a, const Point& b) {
  x_ = b.x_ - a.x_;
  y_ = b.y_ - a.y_;
}

class Segment : public AbstractShape {
 public:
  Segment() = default;
  Segment(const Point& a, const Point& b) : a_(a), b_(b) {}
  bool ContainsPoint(const Point& p) const override;
  bool CrossSegment(const Segment& s) const override;
  Segment* Clone() const override { return new Segment(a_, b_); }
  Segment* Move(const Vector& v) override {
    a_.Move(v);
    b_.Move(v);
    return this;
  }
  void Print() const override {
    std::cout << a_.x_ << ' ' << a_.y_ << ' ' << b_.x_ << ' ' << b_.y_ << '\n';
  }

  void Reverse() {
    Point temp = a_;
    a_ = b_;
    b_ = temp;
  }

  Point a_;
  Point b_;
};

class Ray : public AbstractShape {
 public:
  Ray(const Point& a, const Point& b) : a_(a), b_(b) {}
  Ray(const Segment& s) {
    a_ = s.a_;
    b_ = s.b_;
  }
  bool ContainsPoint(const Point& p) const override;
  bool CrossSegment(const Segment& s) const override;
  Ray* Clone() const override { return new Ray(a_, b_); }
  Ray* Move(const Vector& v) override {
    a_.Move(v);
    b_.Move(v);
    return this;
  }
  void Print() const override {
    std::cout << a_.x_ << ' ' << a_.y_ << ' ' << b_.x_ << ' ' << b_.y_ << '\n';
  }

  Vector Direction() const { return Vector(b_.x_ - a_.x_, b_.y_ - a_.y_); }
  Point a_;
  Point b_;
};

class Line : public AbstractShape {
 public:
  Line(const Point& a, const Point& b) : a_(a), b_(b) {}
  bool ContainsPoint(const Point& p) const override;
  bool CrossSegment(const Segment& s) const override;
  Line* Clone() const override { return new Line(a_, b_); }
  Line* Move(const Vector& v) override {
    a_.Move(v);
    b_.Move(v);
    return this;
  }
  void Print() const override {
    std::cout << a_.x_ << ' ' << a_.y_ << ' ' << b_.x_ << ' ' << b_.y_ << '\n';
  }
  Point a_;
  Point b_;
};

class Polygon : public AbstractShape {
 public:
  Polygon(const std::vector<Point>& points, const size_t& size)
      : points_(points), size_(size) {
    CreateSegments();
  };

  bool ContainsPoint(const Point& p) const override;
  bool CrossSegment(const Segment& s) const override;
  Polygon* Clone() const override { return new Polygon(points_, size_); }
  Polygon* Move(const Vector& v) override {
    for (unsigned int i = 0; i < size_; ++i) {
      points_[i].Move(v);
      segments_[i].Move(v);
    }
    return this;
  }
  void Print() const override {
    std::cout << size_ << '\n';
    for (Point p : points_) {
      std::cout << p.x_ << ' ' << p.y_ << ' ';
    }
    std::cout << '\n';
  }

  std::vector<Point> points_;
  std::vector<Segment> segments_;
  size_t size_;

 private:
  void CreateSegments() {
    segments_.resize(size_);
    for (int i = 0; i < size_; ++i) {
      int to = (i + 1) % size_;
      segments_[i] = Segment(points_[i], points_[to]);
    }
  }
};

class Circle : public AbstractShape {
 public:
  Circle(const Point& center, const int& radius)
      : center_(center), radius_(radius) {}

  bool ContainsPoint(const Point& p) const override {
    return (squared_distance(p, center_) <= square(radius_));
  }
  bool CrossSegment(const Segment& s) const override {}
  Circle* Clone() const override {
    return new Circle(center_, radius_);
  }
  Circle* Move(const Vector& v) override {
    center_.Move(v);
    return this;
  }
  void Print() const override {
    std::cout << center_.x_ << ' ' << center_.y_ << ' ' << radius_ << '\n';
  }

 private:
  Point center_;
  int radius_;
};

bool PointOnSegment(const Point& p, const Segment& s) {
  Vector along_segment(s.b_.x_ - s.a_.x_, s.b_.y_ - s.a_.y_);
  Vector reversed_along_segment(s.a_.x_ - s.b_.x_, s.a_.y_ - s.b_.y_);
  Vector start_to_point(p.x_ - s.a_.x_, p.y_ - s.a_.y_);
  Vector end_to_point(p.x_ - s.b_.x_, p.y_ - s.b_.y_);

  bool on_line = ((along_segment ^ start_to_point) == 0);
  bool sharp_angle_from_start = ((along_segment * start_to_point) >= 0);
  bool sharp_angle_from_end = ((reversed_along_segment * end_to_point) >= 0);

  return on_line && sharp_angle_from_start && sharp_angle_from_end;
}

Segment reverse(const Segment& s) {
  Segment to_reverse = s;
  to_reverse.Reverse();
  return to_reverse;
}

bool PointOnRay(const Point& p, const Ray& r) {
  Ray aux_ray(r.a_, p);
  bool on_line = ((r.Direction() ^ aux_ray.Direction()) == 0);
  bool sharp_angle = ((r.Direction() * aux_ray.Direction()) >= 0);
  return on_line && sharp_angle;
}

bool RaySegmentIntersection(const Ray& the_ray, const Segment& the_segment) {
  Vector s_a_to_ray_start(the_ray.a_.x_ - the_segment.a_.x_,
                          the_ray.a_.y_ - the_segment.a_.y_);
  Vector along_the_segment(the_segment.b_.x_ - the_segment.a_.x_,
                           the_segment.b_.y_ - the_segment.a_.y_);
  Vector along_the_ray = the_ray.Direction();

  int first = (s_a_to_ray_start ^ along_the_segment);
  int second = (the_ray.Direction() ^ along_the_segment);

  bool different_cross_product_signs_by_formula =
      (first < 0 && second > 0) || (first == 0 && second > 0) ||
      (first < 0 && second == 0) || (first > 0 && second < 0) ||
      (first == 0 && second < 0) || (first > 0 && second == 0);

  Vector ray_start_to_a(the_segment.a_.x_ - the_ray.a_.x_,
                        the_segment.a_.y_ - the_ray.a_.y_);
  Vector ray_start_to_b(the_segment.b_.x_ - the_ray.a_.x_,
                        the_segment.b_.y_ - the_ray.a_.y_);
  int ray_to_a_angle = (along_the_ray ^ ray_start_to_a);
  int ray_to_b_angle = (along_the_ray ^ ray_start_to_b);

  bool a_on_ray = PointOnRay(the_segment.a_, the_ray);
  bool b_on_ray = PointOnRay(the_segment.b_, the_ray);

  bool different_angle_signs = (ray_to_a_angle < 0 && ray_to_b_angle > 0) ||
                               (ray_to_a_angle > 0 && ray_to_b_angle < 0);

  return (different_cross_product_signs_by_formula && different_angle_signs) ||
         a_on_ray || b_on_ray;
}

bool PointInsidePolygon(const Point& point, const Polygon& polygon) {
  const int& x = point.x_;
  const int& y = point.y_;
  int intersections = 0;
  for (unsigned int i = 0; i < polygon.size_; ++i) {
    unsigned int j = (i + 1) % polygon.size_;
    if (point == polygon.points_[i] || point == polygon.points_[j]) {
      return true;
    }
    const int& x1 = polygon.points_[i].x_;
    const int& y1 = polygon.points_[i].y_;
    const int& x2 = polygon.points_[j].x_;
    const int& y2 = polygon.points_[j].y_;
    if ((y < y1) != (y < y2) && x < x1 + ((y - y1) / (y2 - y1)) * (x2 - x1)) {
      ++intersections;
    }
  }
  return (intersections % 2 != 0);
}

bool SegmentsIntersection(const Segment& first, const Segment& second) {
  if (!RaySegmentIntersection(Ray(first), second)) {
    return false;
  }
  if (!RaySegmentIntersection(Ray(second), first)) {
    return false;
  }

  Segment first_reversed = reverse(first);

  if (!RaySegmentIntersection(Ray(first_reversed), second)) {
    return false;
  }
  if (!RaySegmentIntersection(Ray(second), first_reversed)) {
    return false;
  }

  Segment second_reversed = reverse(second);

  if (!RaySegmentIntersection(Ray(second_reversed), first)) {
    return false;
  }
  if (!RaySegmentIntersection(Ray(first), second_reversed)) {
    return false;
  }

  if (!RaySegmentIntersection(Ray(first_reversed), second_reversed)) {
    return false;
  }
  if (!RaySegmentIntersection(Ray(second_reversed), first_reversed)) {
    return false;
  }

  return true;
}

bool PointOnLine(const Point& p, const Line& l) {
  const Point& line_start = l.a_;
  const Point& line_end = l.b_;
  Vector to_indenependent_point(p.x_ - line_start.x_, p.y_ - line_start.y_);
  Vector along_the_line(line_end.x_ - line_start.x_,
                        line_end.y_ - line_start.y_);
  return (to_indenependent_point ^ along_the_line) == 0;
}

bool Point::CrossSegment(const Segment& s) const {
  return PointOnSegment(*this, s);
}

bool Segment::ContainsPoint(const Point& p) const {
  return PointOnSegment(p, *this);
}

bool Segment::CrossSegment(const Segment& other) const {
  return SegmentsIntersection(*this, other);
}

bool Ray::ContainsPoint(const Point& p) const { return PointOnRay(p, *this); }

bool Ray::CrossSegment(const Segment& s) const {
  return RaySegmentIntersection(*this, s);
}

bool Line::ContainsPoint(const Point& p) const { return PointOnLine(p, *this); }

bool Line::CrossSegment(const Segment& s) const {
  return (RaySegmentIntersection(Ray(a_, b_), s) ||
          RaySegmentIntersection(Ray(b_, a_), s));
}
bool Polygon::ContainsPoint(const Point& p) const {
  return PointInsidePolygon(p, *this);
}

bool Polygon::CrossSegment(const Segment& s) const {
  for (unsigned int i = 0; i < size_; ++i) {
    if (SegmentsIntersection(segments_[i], s)) {
      return true;
    }
  }
  return false;
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