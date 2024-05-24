
#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <math.h>

using std::cin;
using std::cout;
using std::vector;
using std::queue;

template <typename T>
T Absolufy(const T &value) {
  if (value < 0) {
    return -value;
  }
  return value;
}


struct Point {
  Point() = default;
  Point(int new_x, int new_y) {
    x = new_x;
    y = new_y;
  }
  int x = 0;
  int y = 0;
  
  bool operator==(const Point &another) const {
    bool x_equality = (x == another.x);
    bool y_equality = (y == another.y);
    return x_equality && y_equality;
  }
};

struct Vector{
  Vector() = default;
  Vector(int new_x, int new_y) {
    x = new_x;
    y = new_y;
  }
  Vector(Point from, Point to) {
    x = to.x - from.x;
    y = to.y - from.y;
  }
  int x = 0;
  int y = 0;
  
  bool operator==(const Vector &another) const {
    bool x_equality = (x == another.x);
    bool y_equality = (y == another.y);
    return x_equality && y_equality;
  }

  unsigned long int LengthSquared() const { return (x * x) + (y * y); }
  long double Length() const {
    return sqrtl(LengthSquared());
  }

  long int operator^(const Vector &other) const {
    return (x * other.y) - (y * other.x);
  }

  long int operator*(const Vector &other) const {
    return x * other.x + y * other.y;
  }
};

struct Segment {
  Point a;
  Point b;
};

struct Polygon {
  Polygon() = default;
  Polygon(int amount_of_points) {
    points_amount = amount_of_points;
    fixed_points_amount = true;
    points.resize(points_amount);
  }
  bool AddPoint(const Point &new_point) {
    if (fixed_points_amount) {
      if (points_added < points_amount) {
        points[points_added] = new_point;
        ++points_added;
        return true;
      }
      return false;
    }
    points.push_back(new_point);
    ++points_amount;
    return true;
  }

  int points_amount = 0;
  int points_added = 0;
  bool points_connected = false;
  Point anchor;

  int min_x = std::numeric_limits<int>::max();
  int max_x = std::numeric_limits<int>::min();
  int min_y = std::numeric_limits<int>::max();
  int max_y = std::numeric_limits<int>::min();

  vector<Point> points;
  vector<Segment> segments;
  bool fixed_points_amount = false;

  void CreateSegments() {
    if (points_connected) {
      return;
    }
    segments.resize(points_amount);
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

  long double CalculateArea() {
    int double_area = 0;
    for (unsigned int i = 0; i < points_amount; ++i) {
      int j = (i + 1) % points_amount;
      Vector to_i{points[i].x - anchor.x, points[i].y - anchor.y};
      Vector to_j{points[j].x - anchor.x, points[j].y - anchor.y};
      double_area += (to_i ^ to_j);
    }
    return Absolufy(double_area / 2.0);
  }
};


void DisplayPoints(std::vector<Point> v) {
  for (unsigned int i = 0; i < v.size(); ++i) {
    std::cout << v[i].x << ',' << v[i].y << ' ';
  }
  std::cout << '\n';
}
void FindConvexHullAndItsArea(const vector<Point> &points,
                              Point starting_point = {std::numeric_limits<int>::max(), std::numeric_limits<int>::max()})
{
  cout << hull.size() << '\n';
  Polygon hull_shape(hull.size());

  while (!hull.empty()) {
    const Point &current_hull_point = hull.front();
    cout << current_hull_point.x << ' ' << current_hull_point.y << '\n';
    hull_shape.AddPoint(current_hull_point);
    hull.pop();
  }

  std::cout.precision(1);
  cout << std::fixed << hull_shape.CalculateArea() << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  unsigned int n = 0;
  cin >> n;
  vector<Point> points(n);
  Point starting_point{std::numeric_limits<int>::max(), std::numeric_limits<int>::max()};
  for (unsigned int i = 0; i < n; ++i) {
    cin >> points[i].x >> points[i].y;

    if (points[i].x < starting_point.x || 
       (points[i].x == starting_point.x && points[i].y < starting_point.y)) {
      starting_point = points[i];
    }
  }

  FindConvexHullAndItsArea(points, starting_point);
};