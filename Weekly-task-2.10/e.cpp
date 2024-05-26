#include <iostream>
#include <iomanip>

using std::cin;
using std::cout;
using std::vector;

struct Point {
  int x = 0;
  int y = 0;
};

int Square(int value) {
  return value * value;
}

long double Distance(const Point &one, const Point &two) {
  return sqrtl(Square(one.x - two.x) + Square(one.y - two.y));
}

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

long double Distance(const Point &point, const Segment &segment) {
  Point ap = {point.x - segment.a.x, point.y - segment.a.y};
  Point ab = {segment.b.x - segment.a.x, segment.b.y - segment.a.y};
  if ((ap ^ ab) <= 0) {
    return Distance(segment.a, point);
  }

  Point bp = {point.x - segment.b.x, point.y - segment.b.y};
  Point ba = {segment.a.x - segment.b.x, segment.a.y - segment.b.y};
  if ((bp ^ ba) <= 0) {
    return Distance(segment.b, point);
  }

  return (ab ^ ap) / Distance(segment.a, segment.b);
}

long double Distance(const Segment &one, const Segment &two) {
  using std::min;
  long double result = min(min(Distance(one.a, two), Distance(one.b, two)), 
                           min(Distance(two.a, one), Distance(two.b, one)));
  return result;
}

void Solve() {
  Segment first;
  Segment second;
  cin >> first.a.x >> first.a.y >> first.b.x >> first.b.y;
  cin >> second.a.x >> second.a.y >> second.b.x >> second.b.y;
  std::cout << std::setprecision(6) << Distance(first, second) << '\n';
}

int main() {
  Solve();
}