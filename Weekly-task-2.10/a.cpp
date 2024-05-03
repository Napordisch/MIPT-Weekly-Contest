#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

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
  Segment(Point a, Point b) {
    a_point = a;
    b_point = b;
  }
  Point a_point;
  Point b_point;

  void Reverse() {
    Point temp = a_point;
    a_point = b_point;
    b_point = temp;
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

struct Polygon {
  Polygon() { points_connected = false; }
  void ConnectPoints() {
    if (!segments.empty()) {
      segments.clear();
    } else {
      segments.resize(points.size());
    }
    unsigned int amount_of_points = points.size();
    for (unsigned int i = 0; i < amount_of_points; ++i) {
      unsigned int from = i;
      unsigned int to = i + 1;
      if (to >= amount_of_points) {
        to = 0;
      }
      segments[i] = {points[from], points[to]};
    }
    points_connected = true;
  }

  vector<Point> points;
  vector<Segment> segments;
  bool points_connected;

  void PrintSegments() {
    for (Segment s : segments) {
      cout << s.a_point.x << ',' << s.a_point.y << ';' << ' ';
      cout << s.b_point.x << ',' << s.b_point.y << ';';
      cout << '\n';
    }
  }
};

Point SegmentToVector(const Segment &s) {  // also to point
  Point the_vector(s.b_point.x - s.a_point.x, s.b_point.y - s.a_point.y);
  return the_vector;
}

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

bool PointOnSegment(const Point &p, const Segment &s) {
  Point segment_start_to_point = Point(p.x - s.a_point.x, p.y - s.a_point.y);
  Point point_to_segment_end = Point(s.b_point.x - p.x, s.b_point.y - p.y);
  bool point_on_line = (segment_start_to_point ^ point_to_segment_end) == 0;
  bool same_direction = (segment_start_to_point * point_to_segment_end) >= 0;
  return point_on_line && same_direction;
}

bool RaySegmentIntersection(const Ray &the_ray, const Segment &the_segment) {
  Point s_a_to_ray_start(the_ray.start.x - the_segment.a_point.x,
                         the_ray.start.y - the_segment.a_point.y);
  Point along_the_segment(the_segment.b_point.x - the_segment.a_point.x,
                          the_segment.b_point.y - the_segment.a_point.y);
  Point along_the_ray(the_ray.Direction());

  int first = (s_a_to_ray_start ^ along_the_segment);
  int second = (the_ray.Direction() ^ along_the_segment);
  bool different_cross_product_signs_by_formula =
      (first < 0 && second > 0) || (first > 0 && second < 0);

  Point ray_start_to_a(the_segment.a_point.x - the_ray.start.x,
                       the_segment.a_point.y - the_ray.start.y);
  Point ray_start_to_b(the_segment.b_point.x - the_ray.start.x,
                       the_segment.b_point.y - the_ray.start.y);
  int ray_to_a_angle = (along_the_ray ^ ray_start_to_a);
  int ray_to_b_angle = (along_the_ray ^ ray_start_to_b);

  bool different_angle_signs = (ray_to_a_angle < 0 && ray_to_b_angle > 0) ||
                               (ray_to_a_angle > 0 && ray_to_b_angle < 0);

  return different_cross_product_signs_by_formula && different_angle_signs;
}

bool RayBetweenPointSegments(const Ray &r, const Point &p,
                             const Segment &left_segment,
                             const Segment &right_segment,
                             bool point_on_ray = false) {
  if (!point_on_ray) {
    point_on_ray = PointOnRay(p, r);
  }
  if (!point_on_ray) {
    return false;
  }

  int left_angle = (r.Direction() ^ SegmentToVector(left_segment));
  int right_angle = (r.Direction() ^ SegmentToVector(right_segment));

  return (left_angle > 0 && right_angle < 0) ||
         (left_angle < 0 && right_angle > 0);
}

bool ParellelSegmentIsABorder(const Ray &r, const vector<Segment> &segs,
                              int segment_index) {
  Point along_the_ray = r.Direction();
  const Segment &current_segment = segs[segment_index];
  if ((!PointOnRay(current_segment.a_point, r)) ||
      (!PointOnRay(current_segment.b_point, r))) {
    return false;
  }
  int left_segment_index = segment_index - 1;
  int right_segment_index = segment_index + 1;
  if (left_segment_index < 0) {
    left_segment_index = segs.size() - 1;
  }
  if (right_segment_index >= segs.size()) {
    right_segment_index = 0;
  }
  Segment left_segment = segs[left_segment_index];
  left_segment.Reverse();
  Segment right_segment = segs[right_segment_index];
  Point left_vector = SegmentToVector(left_segment);
  Point right_vector = SegmentToVector(right_segment);
  int left_angle = (along_the_ray ^ left_vector);
  int right_angle = (along_the_ray ^ right_vector);

  return (right_angle > 0 && left_angle < 0) ||
         (right_angle < 0 && left_angle > 0);
}

bool PointInsidePolygon(const Point &p, Polygon &s) {
  if (!s.points_connected) {
    s.ConnectPoints();
  }
  int amount_of_intersections = 0;

  Ray horizontal_from_point(p, Point(p.x + 1, p.y));

  // segments
  for (size_t i = 0; i < s.segments.size(); ++i) {
    const Segment &current_polygon_segment = s.segments[i];
    if (PointOnSegment(p, current_polygon_segment)) {
      return true;
    }
    if (RaySegmentIntersection(horizontal_from_point,
                               current_polygon_segment) ||
        ParellelSegmentIsABorder(horizontal_from_point, s.segments, i)) {
      ++amount_of_intersections;
    }
  }

  // points
  for (size_t i = 0; i < s.points.size(); ++i) {
    const Point &current_polygon_point = s.points[i];
    if (p == current_polygon_point) {
      return true;
    }
    bool point_on_ray =
        PointOnRay(current_polygon_point, horizontal_from_point);

    if (point_on_ray) {
      const Segment &right_segment = s.segments[i];

      int left_segment_index = i - 1;
      if (i - 1 < 0) {
        left_segment_index = static_cast<int>(s.segments.size());
      }
      Segment left_segment = s.segments[left_segment_index];
      left_segment.Reverse();

      if (RayBetweenPointSegments(horizontal_from_point, current_polygon_point,
                                  left_segment, right_segment, point_on_ray)) {
        ++amount_of_intersections;
      }
    }
  }

  return amount_of_intersections % 2 != 0;
}

void Solve() {
  int n = 0;
  int px = 0;
  int py = 0;
  cin >> n >> px >> py;
  Point pokemon(px, py);
  Polygon court;
  for (int i = 0; i < n; ++i) {
    int x = 0;
    int y = 0;
    cin >> x >> y;
    court.points.emplace_back(x, y);
  }
  court.ConnectPoints();
  if (PointInsidePolygon(pokemon, court)) {
    cout << "YES" << '\n';
  } else {
    cout << "NO" << '\n';
  }
}

void Test1() {
  Polygon shape;
  shape.points.emplace_back(7, 3);
  shape.points.emplace_back(7, 10);
  shape.points.emplace_back(3, 8);
  shape.points.emplace_back(0, 10);
  shape.points.emplace_back(0, 3);
  Point p(7, 7);
  Point p1(2, 4);
  Point p2(-10, -20);
  Point p3(-5, 6);
  Point p4(3, 10);
  cout << PointInsidePolygon(p, shape) << '\n';
  cout << PointInsidePolygon(p1, shape) << '\n';
  cout << PointInsidePolygon(p2, shape) << '\n';
  cout << PointInsidePolygon(p3, shape) << '\n';
  cout << PointInsidePolygon(p4, shape) << '\n';
}

void Test2() {
  Polygon shape;
  shape.points.emplace_back(-1, 4);
  shape.points.emplace_back(2, 11);
  shape.points.emplace_back(-3, 9);
  Point p1(-1, 8);
  Point p2(-1, 11);
  Point p3(-6, 9);
  Point p4(2, 11);
  Point p5(-3, 9);
  cout << PointInsidePolygon(p1, shape) << '\n';
  cout << PointInsidePolygon(p2, shape) << '\n';
  cout << PointInsidePolygon(p3, shape) << '\n';
  cout << PointInsidePolygon(p4, shape) << '\n';
  cout << PointInsidePolygon(p5, shape) << '\n';
}

void Test3() {
  Polygon shape;
  shape.points.emplace_back(4, 4);
  shape.points.emplace_back(6, 5);
  shape.points.emplace_back(4, 7);
  shape.points.emplace_back(6, 8);
  shape.points.emplace_back(8, 7);
  shape.points.emplace_back(9, 8);
  shape.points.emplace_back(11, 6);
  shape.points.emplace_back(12, 7);
  shape.points.emplace_back(12, 7);
  shape.points.emplace_back(12, 4);
  shape.points.emplace_back(8, 5);
  Point p1(8, 6);
  Point p2(4, 4);
  Point p3(8, 4);
  Point p4(4, 6);
  Point p5(5, 6);
  Point p6(6, 5);
  Point p7(9, 7);
  Point p8(8, 7);
  Point p9(3, 7);
  Point p10(11, 7);
  Point p11(11, 6);
  Point p12(11, 4);
  Point p13(6, 8);
  cout << PointInsidePolygon(p1, shape) << '\n';
  cout << PointInsidePolygon(p2, shape) << '\n';
  cout << PointInsidePolygon(p3, shape) << '\n';
  cout << PointInsidePolygon(p4, shape) << '\n';
  cout << PointInsidePolygon(p5, shape) << '\n';
  cout << PointInsidePolygon(p6, shape) << '\n';
  cout << PointInsidePolygon(p7, shape) << '\n';
  cout << PointInsidePolygon(p8, shape) << '\n';
  cout << PointInsidePolygon(p9, shape) << '\n';
  cout << PointInsidePolygon(p10, shape) << '\n';
  cout << PointInsidePolygon(p11, shape) << '\n';
  cout << PointInsidePolygon(p13, shape) << '\n';
}

void Test4() {
  Polygon shape;
  shape.points.emplace_back(4, -4);
  shape.points.emplace_back(6, -5);
  shape.points.emplace_back(4, -7);
  shape.points.emplace_back(6, -8);
  shape.points.emplace_back(8, -7);
  shape.points.emplace_back(9, -8);
  shape.points.emplace_back(11, -6);
  shape.points.emplace_back(12, -7);
  shape.points.emplace_back(12, -7);
  shape.points.emplace_back(12, -4);
  shape.points.emplace_back(8, -5);
  Point p1(8, -6);
  Point p2(4, -4);
  Point p3(8, -4);
  Point p4(4, -6);
  Point p5(5, -6);
  Point p6(6, -5);
  Point p7(9, -7);
  Point p8(8, -7);
  Point p9(3, -7);
  Point p10(11, -7);
  Point p11(11, -6);
  Point p12(11, -4);
  Point p13(6, -8);
  cout << PointInsidePolygon(p1, shape) << '\n';
  cout << PointInsidePolygon(p2, shape) << '\n';
  cout << PointInsidePolygon(p3, shape) << '\n';
  cout << PointInsidePolygon(p4, shape) << '\n';
  cout << PointInsidePolygon(p5, shape) << '\n';
  cout << PointInsidePolygon(p6, shape) << '\n';
  cout << PointInsidePolygon(p7, shape) << '\n';
  cout << PointInsidePolygon(p8, shape) << '\n';
  cout << PointInsidePolygon(p9, shape) << '\n';
  cout << PointInsidePolygon(p10, shape) << '\n';
  cout << PointInsidePolygon(p11, shape) << '\n';
  cout << PointInsidePolygon(p13, shape) << '\n';
}

void Test5() {
  Polygon shape;
  shape.points.emplace_back(0, 0);
  shape.points.emplace_back(0, 10);
  shape.points.emplace_back(5, 7);
  shape.points.emplace_back(2, 7);
  shape.points.emplace_back(2, 3);
  shape.points.emplace_back(5, 3);
  shape.points.emplace_back(5, 3);
  shape.points.emplace_back(5, 0);
  Point p1(5, 5);
  cout << PointInsidePolygon(p1, shape) << '\n';
}

void Test6() {  // buttefly triangles
  Polygon shape;
  shape.points.emplace_back(0, 0);
  shape.points.emplace_back(0, 6);
  shape.points.emplace_back(0, 6);
  shape.points.emplace_back(3, 3);
  shape.points.emplace_back(3, 3);
  shape.points.emplace_back(7, 6);
  shape.points.emplace_back(7, 0);
  shape.points.emplace_back(3, 3);
  shape.points.emplace_back(3, 3);
  shape.points.emplace_back(3, 3);
  Point p1(1, 3);
  Point p2(3, 3);
  Point p3(5, 3);
  Point p4(-1, 3);
  Point p5(8, 3);
  Point p6(8, 5);
  cout << PointInsidePolygon(p1, shape) << '\n';
  cout << PointInsidePolygon(p2, shape) << '\n';
  cout << PointInsidePolygon(p3, shape) << '\n';
  cout << PointInsidePolygon(p4, shape) << '\n';
  cout << PointInsidePolygon(p5, shape) << '\n';
  cout << PointInsidePolygon(p6, shape) << '\n';
}

void Test7() {  // reversed buttefly triangles
  Polygon shape;
  shape.points.emplace_back(3, 3);
  shape.points.emplace_back(3, 3);
  shape.points.emplace_back(3, 3);
  shape.points.emplace_back(7, 0);
  shape.points.emplace_back(7, 6);
  shape.points.emplace_back(3, 3);
  shape.points.emplace_back(3, 3);
  shape.points.emplace_back(0, 6);
  shape.points.emplace_back(0, 6);
  shape.points.emplace_back(0, 0);
  Point p1(1, 3);
  Point p2(3, 3);
  Point p3(5, 3);
  Point p4(-1, 3);
  Point p5(8, 3);
  Point p6(8, 5);
  Point p7(0, 6);
  Point p8(0, 0);
  Point p9(3, 0);
  cout << PointInsidePolygon(p1, shape) << '\n';
  cout << PointInsidePolygon(p2, shape) << '\n';
  cout << PointInsidePolygon(p3, shape) << '\n';
  cout << PointInsidePolygon(p4, shape) << '\n';
  cout << PointInsidePolygon(p5, shape) << '\n';
  cout << PointInsidePolygon(p6, shape) << '\n';
  cout << PointInsidePolygon(p7, shape) << '\n';
  cout << PointInsidePolygon(p8, shape) << '\n';
  cout << PointInsidePolygon(p9, shape) << '\n';
}

void Test8() {  // Ildar's shape
  Polygon shape;
  shape.points.emplace_back(3, 1);
  shape.points.emplace_back(6, 3);
  shape.points.emplace_back(3, 6);
  shape.points.emplace_back(5, 8);
  shape.points.emplace_back(8, 4);
  shape.points.emplace_back(12, 8);
  shape.points.emplace_back(8, 8);
  shape.points.emplace_back(12, 11);
  shape.points.emplace_back(8, 12);
  shape.points.emplace_back(9, 10);
  shape.points.emplace_back(1, 10);
  shape.points.emplace_back(1, 10);
  shape.points.emplace_back(-2, 5);
  shape.points.emplace_back(2, 5);
  Point p1(7, 9);
  Point p2(-1, 8);
  // cout << PointInsidePolygon(p1, shape) << '\n';
  cout << PointInsidePolygon(p2, shape) << '\n';
}

void AdditionalTests() {
  // Test 5: Point on polygon edge
  Polygon shape1;
  shape1.points.emplace_back(0, 0);
  shape1.points.emplace_back(4, 0);
  shape1.points.emplace_back(4, 4);
  shape1.points.emplace_back(0, 4);
  Point p1(2, 0);
  Point p2(4, 2);
  Point p3(0, 2);
  Point p4(2, 4);
  cout << PointInsidePolygon(p1, shape1) << '\n';  // Should output 1 (true)
  cout << PointInsidePolygon(p2, shape1) << '\n';  // Should output 1 (true)
  cout << PointInsidePolygon(p3, shape1) << '\n';  // Should output 1 (true)
  cout << PointInsidePolygon(p4, shape1) << '\n';  // Should output 1 (true)
  cout << '\n';

  // Test 6: Point outside polygon
  Polygon shape2;
  shape2.points.emplace_back(0, 0);
  shape2.points.emplace_back(4, 0);
  shape2.points.emplace_back(4, 4);
  shape2.points.emplace_back(0, 4);
  Point p5(5, 5);
  Point p6(-1, -1);
  cout << PointInsidePolygon(p5, shape2) << '\n';  // Should output 0 (false)
  cout << PointInsidePolygon(p6, shape2) << '\n';  // Should output 0 (false)
  cout << '\n';

  // Test 7: Point on polygon vertex
  Polygon shape3;
  shape3.points.emplace_back(0, 0);
  shape3.points.emplace_back(4, 0);
  shape3.points.emplace_back(4, 4);
  shape3.points.emplace_back(0, 4);
  Point p7(0, 0);
  Point p8(4, 0);
  Point p9(4, 4);
  Point p10(0, 4);
  cout << PointInsidePolygon(p7, shape3) << '\n';   // Should output 1 (true)
  cout << PointInsidePolygon(p8, shape3) << '\n';   // Should output 1 (true)
  cout << PointInsidePolygon(p9, shape3) << '\n';   // Should output 1 (true)
  cout << PointInsidePolygon(p10, shape3) << '\n';  // Should output 1 (true)
  cout << '\n';

  // Test 8: Concave polygon
  Polygon shape4;
  shape4.points.emplace_back(0, 0);
  shape4.points.emplace_back(4, 0);
  shape4.points.emplace_back(2, 2);
  shape4.points.emplace_back(4, 4);
  shape4.points.emplace_back(0, 4);
  Point p11(2, 2);
  Point p12(1, 1);
  Point p13(3, 3);
  cout << PointInsidePolygon(p11, shape4) << '\n';  // Should output 1 (true)
  cout << PointInsidePolygon(p12, shape4) << '\n';  // Should output 1 (true)
  cout << PointInsidePolygon(p13, shape4) << '\n';  // Should output 1 (true)
  cout << '\n';
}

void ComplicatedTests() {
  // Test 9: Complex concave polygon
  Polygon shape5;
  shape5.points.emplace_back(0, 0);
  shape5.points.emplace_back(4, 0);
  shape5.points.emplace_back(5, 1);
  shape5.points.emplace_back(6, 2);
  shape5.points.emplace_back(6, 4);
  shape5.points.emplace_back(4, 6);
  shape5.points.emplace_back(3, 5);
  shape5.points.emplace_back(2, 5);
  shape5.points.emplace_back(1, 4);
  shape5.points.emplace_back(1, 2);
  Point p14(3, 4);
  Point p15(5, 3);
  Point p16(2, 1);
  Point p17(0, 4);
  Point p18(5, 5);
  cout << PointInsidePolygon(p14, shape5) << '\n';  // Should output 1 (true)
  cout << PointInsidePolygon(p15, shape5) << '\n';  // Should output 1 (true)
  cout << PointInsidePolygon(p16, shape5) << '\n';  // Should output 1 (true)
  cout << PointInsidePolygon(p17, shape5) << '\n';  // Should output 1 (true)
  cout << PointInsidePolygon(p18, shape5) << '\n';  // Should output 0 (false)
  cout << '\n';

  // Test 10: Polygon with collinear points
  Polygon shape6;
  shape6.points.emplace_back(0, 0);
  shape6.points.emplace_back(1, 1);
  shape6.points.emplace_back(2, 2);
  shape6.points.emplace_back(3, 3);
  shape6.points.emplace_back(4, 4);
  shape6.points.emplace_back(5, 5);
  shape6.points.emplace_back(6, 6);
  Point p19(3, 3);
  Point p20(7, 7);
  Point p21(0, 0);
  Point p22(6, 6);
  cout << PointInsidePolygon(p19, shape6) << '\n';  // Should output 1 (true)
  cout << PointInsidePolygon(p20, shape6) << '\n';  // Should output 0 (false)
  cout << PointInsidePolygon(p21, shape6) << '\n';  // Should output 1 (true)
  cout << PointInsidePolygon(p22, shape6) << '\n';  // Should output 1 (true)
  cout << '\n';
}

void MoreComplicatedTests() {
  // Test 11: Complex polygon with self-intersections
  Polygon shape7;
  shape7.points.emplace_back(0, 0);
  shape7.points.emplace_back(6, 0);
  shape7.points.emplace_back(8, 4);
  shape7.points.emplace_back(6, 6);
  shape7.points.emplace_back(4, 6);
  shape7.points.emplace_back(2, 4);
  shape7.points.emplace_back(4, 2);
  shape7.points.emplace_back(2, 0);
  Point p23(3, 3);
  Point p24(5, 5);
  Point p25(1, 1);
  Point p26(7, 2);
  Point p27(0, 4);
  Point p28(8, 0);
  Point p29(4, 4);
  cout << PointInsidePolygon(p23, shape7) << '\n';  // Should output 1 (true)
  cout << PointInsidePolygon(p24, shape7) << '\n';  // Should output 0 (false)
  cout << PointInsidePolygon(p25, shape7) << '\n';  // Should output 1 (true)
  cout << PointInsidePolygon(p26, shape7) << '\n';  // Should output 0 (false)
  cout << PointInsidePolygon(p27, shape7) << '\n';  // Should output 1 (true)
  cout << PointInsidePolygon(p28, shape7) << '\n';  // Should output 0 (false)
  cout << PointInsidePolygon(p29, shape7) << '\n';  // Should output 1 (true)
}

int main() {
  Solve();
}