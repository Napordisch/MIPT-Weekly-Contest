#include <vector>
#include <iostream>

using std::cin;
using std::cout;
using std::vector;

struct Point {
  Point() = default;
  Point(int new_x, int new_y) {
    x = new_x;
    y = new_y;
  }
  int x = 0;
  int y = 0;
};

struct Segment {
  Segment(Point a, Point b) {
    a_point = a;
    b_point = b;
  }
  Point a_point;
  Point b_point;
};

struct Ray {
  Ray(Point s, Point new_end) {
    end = new_end;
    start = s;
  }
  Point end;
  Point start;
  Point Direction() {
    return Point(end.x - start.x, end.y - start.y);
  }
};

struct Polygon {
  vector<Point> points;
};

Point SegmentToVector(Segment s) {
  Point the_vector(s.b_point.x - s.a_point.x, s.b_point.y - s.a_point.y);
  return the_vector;
}

int operator^(Point a, Point b);

bool RaySegmentIntersection(Ray the_ray, Segment the_segment) {
  Segment aux_segment(the_segment.a_point, the_ray.start); // connects a_point of segment to the start of the ray
  Point segment_vector = SegmentToVector(the_segment); // vector of the same direction as the segment

  int first = (SegmentToVector(aux_segment) ^ segment_vector);
  int second = (the_ray.Direction() ^ segment_vector);

  return (first < 0 && second > 0) || (first > 0 && second < 0);
}

int operator^(Point a, Point b) {
  return a.x * b.y - a.y * b.x;
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
}


int main() {
  Point ray_start(0, 3);
  Point ray_direction(3, 3);
  Ray r(ray_start, ray_direction);
  Point seg_start(3, 5);
  Point seg_end(4, 0);
  Segment s(seg_start, seg_end);
  cout << RaySegmentIntersection(r, s) << '\n';
  return 0;
}
