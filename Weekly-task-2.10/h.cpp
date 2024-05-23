#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

struct Point {
  Point() = default;

  long int x = 0;
  long int y = 0;

  bool operator==(const Point &another) const {
    bool x_equality = (x == another.x);
    bool y_equality = (y == another.y);
    return x_equality && y_equality;
  }
};

struct Vector {
  Vector() = default;

  long int x = 0;
  long int y = 0;

  bool operator==(const Vector &another) const {
    bool x_equality = (x == another.x);
    bool y_equality = (y == another.y);
    return x_equality && y_equality;
  }

  long double LengthSquared() const { return (x * x) + (y * y); }

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
  Vector vectorize() {
    return {b.x - a.x, b.y - a.y};
  }
};

int main() {
  unsigned long int n = 0;
  cin >> n;
  vector<Segment> polygon;

  {
    Point start;
    Point first;
    Point second;
    cin >> first.x >> first.y;
    start = first;
    for (unsigned long int i = 1; i < n; ++i) {
      cin >> second.x >> second.y;
      if (second == first) {
        continue;
      }
      polygon.push_back({first, second});
      first = second;
    }
    polygon.push_back({second, start});
  }

  long int initial_cross_product = 0;
  for (unsigned long int i = 0; i < polygon.size(); ++i) {
    unsigned long int j = (i + 1) % polygon.size();
    long int current_cross_product = (polygon[i].vectorize() ^ polygon[j].vectorize());

    if (initial_cross_product == 0 && current_cross_product != 0) {
      initial_cross_product = current_cross_product;
      continue;
    }

    if ((polygon[i].vectorize() ^ polygon[j].vectorize()) < 0 && initial_cross_product > 0 ||
        (polygon[i].vectorize() ^ polygon[j].vectorize()) > 0 && initial_cross_product < 0) {
      cout << "NO" << '\n';
      return 0;
    }
  }

  cout << "YES" << '\n';
  return 0;
}