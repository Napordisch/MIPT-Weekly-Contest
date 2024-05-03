#include <iostream>

using std::cin;
using std::cout;

struct Point {  // a.k.a. Vector
  Point() = default;
  Point(int new_x, int new_y) {
    x = new_x;
    y = new_y;
  }
  int x = 0;
  int y = 0;
  bool operator==(const Point &another_point) const {
    bool x_equality = (x == another_point.x);
    bool y_equality = (y == another_point.y);
    return x_equality && y_equality;
  }
};

struct Segment {
  Segment() = default;
  Segment(Point new_a, Point new_b) {
    a = new_a;
    b = new_b;
  }
  Point a;
  Point b;

  void Reverse() {
    Point temp = a;
    a = b;
    b = temp;
  }
};

struct Ray {
  Ray(Point s, Point new_end) {
    start = s;
    end = new_end;
  }
  Point start;
  Point end;
  Point Direction() const {  // vector
    return Point(end.x - start.x, end.y - start.y);
  }
};

Ray SegmentToRay(const Segment &s) { return Ray(s.a, s.b); }

int operator^(const Point &a, const Point &b) {
  return (a.x * b.y) - (a.y * b.x);
}

int operator*(const Point &a, const Point &b) {
  return (a.x * b.x) + (a.y * b.y);
}

bool PointOnRay(const Point &p, const Ray &r) {
  Ray aux_ray(r.start, p);
  bool on_line = ((r.Direction() ^ aux_ray.Direction()) == 0);
  bool sharp_angle = ((r.Direction() * aux_ray.Direction()) >= 0);
  return on_line && sharp_angle;
}

bool RaySegmentIntersection(const Ray &the_ray, const Segment &the_segment) {
  Point s_a_to_ray_start(the_ray.start.x - the_segment.a.x,
                         the_ray.start.y - the_segment.a.y);
  Point along_the_segment(the_segment.b.x - the_segment.a.x,
                          the_segment.b.y - the_segment.a.y);
  Point along_the_ray = the_ray.Direction();

  int first = (s_a_to_ray_start ^ along_the_segment);
  int second = (the_ray.Direction() ^ along_the_segment);

  bool different_cross_product_signs_by_formula =
      (first < 0 && second > 0) || (first == 0 && second > 0) ||
      (first < 0 && second == 0) || (first > 0 && second < 0) ||
      (first == 0 && second < 0) || (first > 0 && second == 0);

  Point ray_start_to_a(the_segment.a.x - the_ray.start.x,
                       the_segment.a.y - the_ray.start.y);
  Point ray_start_to_b(the_segment.b.x - the_ray.start.x,
                       the_segment.b.y - the_ray.start.y);
  int ray_to_a_angle = (along_the_ray ^ ray_start_to_a);
  int ray_to_b_angle = (along_the_ray ^ ray_start_to_b);

  bool a_on_ray = PointOnRay(the_segment.a, the_ray);
  bool b_on_ray = PointOnRay(the_segment.b, the_ray);

  bool different_angle_signs = (ray_to_a_angle < 0 && ray_to_b_angle > 0) ||
                               (ray_to_a_angle > 0 && ray_to_b_angle < 0);

  return (different_cross_product_signs_by_formula && different_angle_signs) ||
         a_on_ray || b_on_ray;
}

Segment reverse(const Segment &s) {
  Segment to_reverse = s;
  to_reverse.Reverse();
  return to_reverse;
}

bool SegmentsIntersection(const Segment &first, const Segment &second) {
  if (!RaySegmentIntersection(SegmentToRay(first), second)) {
    return false;
  }
  if (!RaySegmentIntersection(SegmentToRay(second), first)) {
    return false;
  }

  Segment first_reversed = reverse(first);

  if (!RaySegmentIntersection(SegmentToRay(first_reversed), second)) {
    return false;
  }
  if (!RaySegmentIntersection(SegmentToRay(second), first_reversed)) {
    return false;
  }

  Segment second_reversed = reverse(second);

  if (!RaySegmentIntersection(SegmentToRay(second_reversed), first)) {
    return false;
  }
  if (!RaySegmentIntersection(SegmentToRay(first), second_reversed)) {
    return false;
  }

  if (!RaySegmentIntersection(SegmentToRay(first_reversed), second_reversed)) {
    return false;
  }
  if (!RaySegmentIntersection(SegmentToRay(second_reversed), first_reversed)) {
    return false;
  }

  return true;
}

void Solve() {
  Segment segments[2];
  for (int i = 0; i < 2; ++i) {
    int x = 0;
    int y = 0;
    cin >> x >> y;
    Point a(x, y);
    cin >> x >> y;
    Point b(x, y);
    segments[i] = Segment(a, b);
  }
  if (SegmentsIntersection(segments[1], segments[0]) &&
      SegmentsIntersection(segments[0], segments[1])) {
    cout << "YES" << '\n';
  } else {
    cout << "NO" << '\n';
  }
}

void Test1() {
  Segment first(Point(0, 11), Point(5, 11));
  Segment second(Point(4, 4), Point(4, 11));
  cout << SegmentsIntersection(first, second) << '\n';
}

void Test2() {
  Segment first(Point(-3, 2), Point(3, 2));
  Segment second(Point(3, 2), Point(11, 2));
  cout << SegmentsIntersection(first, second) << '\n';
}

void Test3() {
  Segment first(Point(-3, 10), Point(7, 10));
  Segment second(Point(2, 10), Point(9, 8));
  cout << SegmentsIntersection(first, second) << '\n';
}

int main() {
  Solve();
}