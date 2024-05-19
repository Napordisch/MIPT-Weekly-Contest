#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

struct Point {
  int x = 0;
  int y = 0;
};

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

  vector<Point> points;
  vector<Segment> segments;
  void AddPointsFromStdInput() {
    for (int i = 0; i < points_amount; ++i) {
      cin >> points[i].x >> points[i].y;
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

bool PointInsidePolygon(const Point &point, const Polygon &polygon) {
  const int &x = point.x;
  const int &y = point.y;
  int intersections = 0;
  for (unsigned int i = 0; i < polygon.points_amount; ++i) {
    unsigned int j = (i + 1) % polygon.points_amount;
    if (point == polygon.points[i] || point == polygon.points[j]) {
      return true;
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
  return (intersections % 2 != 0);
}

void Solve() {
  int n = 0;
  Point pokemon;
  cin >> n >> pokemon.x >> pokemon.y;
  Polygon court(n);
  court.AddPointsFromStdInput();
  if (PointInsidePolygon(pokemon, court)) {
    cout << "YES" << '\n';
  } else {
    cout << "NO" << '\n';
  }
}

int main() { Solve(); }