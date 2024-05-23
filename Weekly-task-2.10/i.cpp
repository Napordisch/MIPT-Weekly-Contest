#include <iostream>
#include <vector>
#include <cmath>

using std::cin;
using std::cout;

struct Point {  // a.k.a. vector
  Point() = default;

  Point(double new_x, double new_y) {
    x = new_x;
    y = new_y;
  }

  double x = 0;
  double y = 0;

  bool operator==(const Point &another_point) const {
    bool x_equality = (x == another_point.x);
    bool y_equality = (y == another_point.y);
    return x_equality && y_equality;
  }

  Point operator+(const Point &other) const {
    return Point(x + other.x, y + other.y);
  }

  long double Length() const { return sqrtl((x * x) + (y * y)); }

  long double LengthSquared() const { return (x * x) + (y * y); }

  int operator^(const Point &other) const {
    return (x * other.y) - (y * other.x);
  }

  int operator*(const Point &other) const {
    return x * other.x + y * other.y;
  }
};

struct Segment {
  Point a;
  Point b;
};

struct Ray {
  Point start;
  Point end;
  Point Direction() const {  // vector
    return Point(end.x - start.x, end.y - start.y);
  }
};

bool PointOnLine(const Point &p, const Point &line_start, const Point &line_end) {

  Point to_indenependent_point            {p.x - line_start.x,        p.y - line_start.y};
  Point along_the_line             {line_end.x - line_start.x, line_end.y - line_start.y};

  return (to_indenependent_point ^ along_the_line) == 0;
}

bool PointOnRay(const Point &p, const Ray &r) {
  Ray aux_ray {r.start, p};
  bool on_line = ((r.Direction() ^ aux_ray.Direction()) == 0);
  bool sharp_angle = ((r.Direction() * aux_ray.Direction()) >= 0);
  return on_line && sharp_angle;
}

bool PointOnSegment(const Point &p, const Segment &s) {

  Point along_segment           {s.b.x - s.a.x, s.b.y - s.a.y};
  Point reversed_along_segment  {s.a.x - s.b.x, s.a.y - s.b.y};
  Point start_to_point            {p.x - s.a.x,   p.y - s.a.y};
  Point end_to_point              {p.x - s.b.x,   p.y - s.b.y};

  bool on_line =                             ((along_segment ^ start_to_point) == 0);
  bool sharp_angle_from_start =              ((along_segment * start_to_point) >= 0);
  bool sharp_angle_from_end =       ((reversed_along_segment * end_to_point) >= 0);

  return on_line && sharp_angle_from_start && sharp_angle_from_end;
}

void SayIfPointIsOnRay(const Point &p, const Point &a, const Point &b) {
  Ray ab {a, b};
  if (PointOnRay(p, ab)) {
    cout << "YES\n";
    return;
  }
  cout << "NO\n";
}

void SayIfPointIsOnLine(const Point &p, const Point &line_start, const Point &line_end) {
  if (PointOnLine(p, line_start, line_end)) {
    cout << "YES\n";
    return;
  }
  cout << "NO\n";
}

void SayIfPointIsOnSegment(const Point &p, const Point &a, const Point &b) {
  Segment ab {a, b};
  if (PointOnSegment(p, ab)) {
    cout << "YES\n";
    return;
  }
  cout << "NO\n";
}

void Solve() {
  Point c;
  cin >> c.x >> c.y;
  Point a;
  cin >> a.x >> a.y;
  Point b;
  cin >> b.x >> b.y;
  SayIfPointIsOnLine   (c, a, b);
  SayIfPointIsOnRay    (c, a, b);
  SayIfPointIsOnSegment(c, a, b);
}

int main() {
  Solve();
}