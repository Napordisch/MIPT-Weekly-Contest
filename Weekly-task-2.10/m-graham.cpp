
#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <math.h>
#include <algorithm>

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

  bool points_connected = false;
  Point anchor;

  int min_x = std::numeric_limits<int>::max();
  int max_x = std::numeric_limits<int>::min();
  int min_y = std::numeric_limits<int>::max();
  int max_y = std::numeric_limits<int>::min();

  vector<Point> points;
  vector<Segment> segments;
  bool fixed_points_amount = false;

  void PrintPoints() {
    for (Point p : points) {
      std::cout << p.x << ' ' << p.y << '\n';
    }
  }

  long double CalculateArea() {
    unsigned int points_amount = points.size();
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

void FindConvexHullByGraham(vector<Point> &points,
                            vector<Point> &Hull,
                            const Point& starting_point = {std::numeric_limits<int>::max(), std::numeric_limits<int>::max()})
{
  auto compare = [&starting_point] (Point first, Point second) {
    return ((Vector(starting_point, first) ^ Vector(starting_point, second)) < 0);
  };
  std::sort(points.begin(), points.end(), compare);
  for (Point p : points) {

    while (Hull.size() >= 2) {
      Vector new_vector(Hull[Hull.size() - 1], p);
      Vector last_vector(Hull[Hull.size() - 2], Hull[Hull.size() - 1]);
      if ((new_vector ^ last_vector) < 0) {
        Hull.pop_back();
      } else {
        break;
      }
    }

    Hull.push_back(p);
  }
}

void FindConvexHullAndItsArea(vector<Point> &points,
                              Point starting_point = {std::numeric_limits<int>::max(), std::numeric_limits<int>::max()})
{
  Polygon hull;
  FindConvexHullByGraham(points, hull.points, starting_point);
  cout << hull.points.size() << '\n';
  hull.PrintPoints();
  std::cout.precision(1);
  cout << std::fixed << hull.CalculateArea() << '\n';
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