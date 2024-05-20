#include <iostream>
#include <vector>
#include <limits>

using std::cin;
using std::cout;
using std::vector;

struct Point {
  int x = 0;
  int y = 0;
};

int operator^(const Point &one, const Point &two) {
  return one.x * two.y - one.y * two.x;
}

int operator*(const Point &one, const Point &two) {
  return one.x * two.x + one.y * two.y;
}

bool operator==(const Point &one, const Point &two) {
  return (one.x == two.x && one.y == two.y);
}

struct Segment {
  Point a;
  Point b;
};

struct Polygon {
  Polygon(int amount_of_points) {
    points_amount = amount_of_points;
    points.resize(points_amount);
    segments.resize(points_amount);
  }

  int points_amount = 0;
  bool points_connected = false;

  int min_x = std::numeric_limits<int>::max();
  int max_x = std::numeric_limits<int>::min();
  int min_y = std::numeric_limits<int>::max();
  int max_y = std::numeric_limits<int>::min();

  vector<Point> points;
  vector<Segment> segments;
  void AddPointsFromStdInput() {
    for (int i = 0; i < points_amount; ++i) {
      int new_x = 0;
      int new_y = 0;
      cin >> new_x >> new_y;
      points[i].x = new_x;
      points[i].y = new_y;
      min_y = std::min(new_y, min_y);
      min_x = std::min(new_x, min_x);
      max_x = std::max(new_x, max_x);
      max_y = std::max(new_y, max_y);
    }
    CreateSegments();
  }

  void CreateSegments() {
    if (points_connected) {
      return;
    }
    for (int i = 0; i < points_amount; ++i) {
      int to = i + 1;
      if (to >= points_amount) {
        to = 0;
      }
      segments[i] = {points[i], points[to]};
    }
    points_connected = true;
  }

  void PrintSegments() {
    for (unsigned int i = 0; i < points_amount; ++i) {
      cout << segments[i].a.x << ',' << segments[i].a.y << ' '
           << segments[i].b.x << ',' << segments[i].b.y << '\n';
    }
  }
};

bool PointOnSegment(const Point &point, const Segment &segment) {
  Point segment_start_to_point = {point.x - segment.a.x, point.y - segment.a.y};
  Point point_to_segment_end = {segment.b.x - point.x, segment.b.y - point.y};
  return (segment_start_to_point ^ point_to_segment_end) == 0 &&
         (segment_start_to_point * point_to_segment_end) >= 0;
}

int PointInsidePolygon(const Point &point, const Polygon &polygon) { // 1 - on edge, 2 - inside
  const int &x = point.x;
  const int &y = point.y;
  int intersections = 0;
  for (unsigned int i = 0; i < polygon.points_amount; ++i) {
    unsigned int j = (i + 1) % polygon.points_amount;

    if (point == polygon.points[i]) {
      return 1;
    }
    if (PointOnSegment(point, polygon.segments[i])) {
      return 1;
    }

    const int &x1 = polygon.points[i].x;
    const int &y1 = polygon.points[i].y;
    const int &x2 = polygon.points[j].x;
    const int &y2 = polygon.points[j].y;
    if ((y < y1) != (y < y2) &&
        x < x1 + ((y - y1) / (y2 - y1)) * (x2 - x1)) {
          ++intersections;
        }
  }
  if (intersections % 2 != 0) {
    return 2;
  }
  return 0;
}

void Solve() {
  int n = 0;
  cin >> n;
  Polygon polygon(n);
  polygon.AddPointsFromStdInput();

  int double_sum = 0;

  for (int x = polygon.min_x; x <= polygon.max_x; ++x) {
    for (int y = polygon.min_y; y <= polygon.max_y; ++y) {
      double_sum += PointInsidePolygon({x, y}, polygon);
    }
  }

  long double area = double_sum / 2.0 - 1;
  std::cout.precision(15);
  std::cout << std::fixed << area << '\n';
}

int main() {
  Solve();
}