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

template <typename T>
T Absolufy(const T &value) {
  if (value < 0) {
    return -value;
  }
  return value;
}


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
  }

  int points_amount = 0;
  bool points_connected = false;
  Point anchor;

  int min_x = std::numeric_limits<int>::max();
  int max_x = std::numeric_limits<int>::min();
  int min_y = std::numeric_limits<int>::max();
  int max_y = std::numeric_limits<int>::min();

  vector<Point> points;
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
    anchor = {min_x - 1, min_y};
  }

  long double CalculateArea() {
    int double_area = 0;
    for (unsigned int i = 0; i < points_amount; ++i) {
      int j = (i + 1) % points_amount;
      Point to_i = {points[i].x - anchor.x, points[i].y - anchor.y};
      Point to_j = {points[j].x - anchor.x, points[j].y - anchor.y};
      double_area += (to_i ^ to_j);
    }
    return Absolufy(double_area / 2.0);
  }
};

void Solve() {
  int n = 0;
  cin >> n;
  Polygon polygon(n);
  polygon.AddPointsFromStdInput();
  std::cout.precision(15);
  std::cout << std::fixed << polygon.CalculateArea() << '\n';
}

int main() {
  Solve();
}