#include <cmath>

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>

int Square(const int& number) {
  return number * number;
}

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
  Vector(int x, int y) : x_(x), y_(y) {
  }
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
  Point(const int& x, const int& y) : x_(x), y_(y) {
  }
  bool operator==(const Point& other) {
    return ContainsPoint(other);
  }
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

long double Length(const Point& a, const Point& b) {
  return sqrtl((b.x_ - a.x_) * (b.x_ - a.x_) + (b.y_ - a.y_) * (b.y_ - a.y_));
}

int SquaredDistance(const Point& a, const Point& b) {
  return Square(b.x_ - a.x_) + Square(b.y_ - a.y_);
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
  Segment(const Point& a, const Point& b) : a_(a), b_(b) {
  }
  bool ContainsPoint(const Point& p) const override;
  bool CrossSegment(const Segment& s) const override;
  Segment* Clone() const override {
    return new Segment(a_, b_);
  }
  Segment* Move(const Vector& v) override {
    a_.Move(v);
    b_.Move(v);
    return this;
  }
  void Print() const override {
    std::cout << a_.x_ << ' ' << a_.y_ << ' ' << b_.x_ << ' ' << b_.y_ << '\n';
  }

  void Reverse() {
    Point temp(a_);
    a_ = Point(b_);
    b_ = Point(temp);
  }

  Point a_;
  Point b_;
};

class Ray : public AbstractShape {
 public:
  Ray(const Point& a, const Point& b) : a_(a), b_(b) {
  }
  explicit Ray(const Segment& s) {
    a_ = s.a_;
    b_ = s.b_;
  }
  bool ContainsPoint(const Point& p) const override;
  bool CrossSegment(const Segment& s) const override;
  Ray* Clone() const override {
    return new Ray(a_, b_);
  }
  Ray* Move(const Vector& v) override {
    a_.Move(v);
    b_.Move(v);
    return this;
  }
  void Print() const override {
    std::cout << a_.x_ << ' ' << a_.y_ << ' ' << b_.x_ << ' ' << b_.y_ << '\n';
  }

  Vector Direction() const {
    return {b_.x_ - a_.x_, b_.y_ - a_.y_};
  }
  Point a_;
  Point b_;
};

class Line : public AbstractShape {
 public:
  Line(const Point& a, const Point& b) : a_(a), b_(b) {
  }
  explicit Line(const Segment& s) : a_(s.a_), b_(s.b_) {
  }
  bool ContainsPoint(const Point& p) const override;
  bool CrossSegment(const Segment& s) const override;
  Line* Clone() const override {
    return new Line(a_, b_);
  }
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
  Polygon(const std::vector<Point>& points, const size_t& size) : points_(points), size_(size) {
    CreateSegments();
  };

  bool ContainsPoint(const Point& p) const override;
  bool CrossSegment(const Segment& s) const override;
  Polygon* Clone() const override {
    return new Polygon(points_, size_);
  }
  Polygon* Move(const Vector& v) override {
    for (unsigned int i = 0; i < size_; ++i) {
      points_[i].Move(v);
      segments_[i].Move(v);
    }
    return this;
  }
  void Print() const override {
    std::cout << size_ << '\n';
    for (size_t i = 0; i < size_; ++i) {
      const Point& p = points_[i];
      std::cout << p.x_ << ' ' << p.y_;
      if (i != size_ - 1) {
        std::cout << ' ';
      }
    }
    std::cout << '\n';
  }

  std::vector<Point> points_;
  std::vector<Segment> segments_;
  size_t size_;

 private:
  void CreateSegments() {
    segments_.resize(size_);
    for (size_t i = 0; i < size_; ++i) {
      size_t to = (i + 1) % size_;
      segments_[i] = Segment(points_[i], points_[to]);
    }
  }
};

class Circle : public AbstractShape {
 public:
  Circle(const Point& center, const int& radius) : center_(center), radius_(radius) {
  }

  bool ContainsPoint(const Point& p) const override {
    return (SquaredDistance(p, center_) <= Square(radius_));
  }

  bool CrossSegment(const Segment& s) const override {
    long double seg_length = Length(s.a_, s.b_);
    long double seg_a_to_center = Length(s.a_, center_);
    long double seg_b_to_center = Length(s.b_, center_);
    if (seg_a_to_center < radius_ && seg_b_to_center < radius_) {
      return false;
    }
    long double half_perimeter = (seg_length + seg_a_to_center + seg_b_to_center) / 2;
    long double area = sqrtl(half_perimeter * (half_perimeter - seg_length) * (half_perimeter - seg_a_to_center) *
                             (half_perimeter - seg_b_to_center));

    long double dist = (area * 2) / seg_length;
    return seg_a_to_center <= radius_ || seg_b_to_center <= radius_ || dist <= radius_;
  }

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

bool Point::CrossSegment(const Segment& s) const {
  return s.ContainsPoint(*this);
}

bool Segment::ContainsPoint(const Point& p) const {
  Vector start_to_point(p.x_ - a_.x_, p.y_ - a_.y_);
  Vector point_to_end(b_.x_ - p.x_, b_.y_ - p.y_);

  bool on_line = (start_to_point ^ point_to_end) == 0;
  bool between_points = (start_to_point * point_to_end) >= 0;

  return on_line && on_line && between_points;
}

bool Segment::CrossSegment(const Segment& s) const {
  bool when_this_is_line = Line(*this).CrossSegment(s);
  bool when_that_is_line = Line(s).CrossSegment(*this);
  if ((Vector(s.a_, s.b_) ^ Vector(a_, b_)) == 0) {
    if (!(ContainsPoint(s.a_) || ContainsPoint(s.b_) || s.ContainsPoint(a_) || s.ContainsPoint(b_))) {
      return false;
    }
  }
  return when_this_is_line && when_that_is_line;
}

bool Ray::ContainsPoint(const Point& p) const {
  Ray aux_ray(a_, p);
  bool on_line = ((Direction() ^ aux_ray.Direction()) == 0);
  bool sharp_angle = ((Direction() * aux_ray.Direction()) >= 0);
  return on_line && sharp_angle;
}

bool Ray::CrossSegment(const Segment& s) const {
  Vector s_a_to_ray_start(a_.x_ - s.a_.x_, a_.y_ - s.a_.y_);
  Vector along_the_segment(s.b_.x_ - s.a_.x_, s.b_.y_ - s.a_.y_);

  int first = (s_a_to_ray_start ^ along_the_segment);
  int second = (Direction() ^ along_the_segment);

  bool different_cross_product_signs_by_formula = (first > 0 && second < 0) || (first < 0 && second > 0);
  bool crosses_one_end = (ContainsPoint(s.a_) || ContainsPoint(s.b_));

  return different_cross_product_signs_by_formula || crosses_one_end;
}

bool Line::ContainsPoint(const Point& p) const {
  Vector to_indenependent_point(p.x_ - a_.x_, p.y_ - a_.y_);
  Vector along_the_line(b_.x_ - a_.x_, b_.y_ - a_.y_);
  return (to_indenependent_point ^ along_the_line) == 0;
}

bool Line::CrossSegment(const Segment& s) const {
  Vector along_the_line(a_, b_);
  Vector to_a(a_, s.a_);
  Vector to_b(a_, s.b_);
  return (((along_the_line ^ to_a) > 0 && (along_the_line ^ to_b) < 0) ||
          ((along_the_line ^ to_a) < 0 && (along_the_line ^ to_b) > 0) || (along_the_line ^ to_a) == 0 ||
          (along_the_line ^ to_b) == 0);
}

bool Polygon::ContainsPoint(const Point& p) const {
  const int& x = p.x_;
  const int& y = p.y_;
  int intersections = 0;
  for (unsigned int i = 0; i < size_; ++i) {
    unsigned int j = (i + 1) % size_;
    if (p == points_[i] || p == points_[j]) {
      return true;
    }
    const int& x1 = points_[i].x_;
    const int& y1 = points_[i].y_;
    const int& x2 = points_[j].x_;
    const int& y2 = points_[j].y_;
    if ((y < y1) != (y < y2) && x < x1 + ((y - y1) / (y2 - y1)) * (x2 - x1)) {
      ++intersections;
    }
  }
  return (intersections % 2 != 0);
}

bool Polygon::CrossSegment(const Segment& s) const {
  for (unsigned int i = 0; i < size_; ++i) {
    if (s.CrossSegment(segments_[i])) {
      return true;
    }
  }
  return false;
}

}  // namespace geometry

using geometry::Point;

void CheckFunctions(const geometry::AbstractShape* shape, const geometry::Point& a, const geometry::Point& b) {
  if (shape->ContainsPoint(a)) {
    std::cout << "Given shape contains point A" << '\n';
  } else {
    std::cout << "Given shape does not contain point A" << '\n';
  }

  geometry::Segment s_ab(a, b);
  if (shape->CrossSegment(s_ab)) {
    std::cout << "Given shape crosses segment AB" << '\n';
  } else {
    std::cout << "Given shape does not cross segment AB" << '\n';
  }

  geometry::Vector ab(a, b);
  geometry::AbstractShape* cloned_shape = shape->Clone();
  cloned_shape->Move(ab)->Print();
  delete cloned_shape;
}

int main() {
  geometry::AbstractShape* shape = nullptr;
  char command[10];
  std::cin >> command;
  if (!strcmp(command, "point")) {
    int x = 0;
    int y = 0;
    std::cin >> x >> y;
    shape = new geometry::Point(x, y);
  } else if (!strcmp(command, "segment")) {
    int x1 = 0;
    int y1 = 0;
    int x2 = 0;
    int y2 = 0;
    std::cin >> x1 >> y1 >> x2 >> y2;
    shape = new geometry::Segment(geometry::Point(x1, y1), geometry::Point(x2, y2));
  } else if (!strcmp(command, "ray")) {
    int x1 = 0;
    int y1 = 0;
    int x2 = 0;
    int y2 = 0;
    std::cin >> x1 >> y1 >> x2 >> y2;
    shape = new geometry::Ray(geometry::Point(x1, y1), geometry::Point(x2, y2));
  } else if (!strcmp(command, "line")) {
    int x1 = 0;
    int y1 = 0;
    int x2 = 0;
    int y2 = 0;
    std::cin >> x1 >> y1 >> x2 >> y2;
    shape = new geometry::Line(geometry::Point(x1, y1), geometry::Point(x2, y2));
  } else if (!strcmp(command, "polygon")) {
    size_t n_points = 0;
    std::cin >> n_points;
    std::vector<geometry::Point> points;
    points.reserve(n_points);
    for (size_t i = 0; i < n_points; ++i) {
      int x = 0;
      int y = 0;
      std::cin >> x >> y;
      points.emplace_back(x, y);
    }
    shape = new geometry::Polygon(points, n_points);
  } else if (!strcmp(command, "circle")) {
    int x = 0;
    int y = 0;
    std::cin >> x >> y;
    Point center(x, y);
    int radius = 0;
    std::cin >> radius;
    shape = new geometry::Circle(center, radius);
  } else {
    std::cerr << "Undefined command" << '\n';
    return 1;
  }

  int ax = 0;
  int ay = 0;
  int bx = 0;
  int by = 0;
  std::cin >> ax >> ay >> bx >> by;
  geometry::Point a(ax, ay);
  geometry::Point b(bx, by);

  CheckFunctions(shape, a, b);
  delete shape;

  return 0;
}