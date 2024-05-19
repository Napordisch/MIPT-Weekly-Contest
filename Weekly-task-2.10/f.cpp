#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;

template <typename T>
T Absolute(const T &number) {
  if (number < 0) {
    return -number;
  }
  return number;
}


template <typename T>
T Square(T number) {
  return number * number;
}

struct Line {
  Line(long double a, long double b, long double c) {
    a_index = a;
    b_index = b;
    c_index = c;
  }
  long double a_index = 0;
  long double b_index = 0;
  long double c_index = 0;
};

struct Vector {  // a.k.a. point
  Vector() = default;

  Vector(long double new_x, long double new_y) {
    x = new_x;
    y = new_y;
  }

  long double x = 0;
  long double y = 0;

  bool operator==(const Vector &another_point) const {
    bool x_equality = (x == another_point.x);
    bool y_equality = (y == another_point.y);
    return x_equality && y_equality;
  }

  Vector operator+(const Vector &other) const {
    return Vector(x + other.x, y + other.y);
  }

  long double Length() const { return sqrtl((x * x) + (y * y)); }

  long double LengthSquared() const { return (x * x) + (y * y); }

  long double operator^(const Vector &other) const {
    return (x * other.y) - (y * other.x);
  }

  long double operator*(const Vector &other) const {
    return (x * other.x) + (y * other.y);
  }
};

long double Distance(const Vector &first, const Vector &second) {
  long double distance = sqrtl(Square(second.x - first.x)  + Square(second.y - first.y));

  if (distance == -0) {
    distance = 0;
  }

  return distance;
}


Vector ConvertLineToVector(Line l) {
  Vector normal(l.a_index, l.b_index);
  Vector result = Vector(-normal.y, normal.x);
  if (result.x == -0) {
    result.x = 0;
  }

  if (result.y == -0) {
    result.y = 0;
  }
  return result;
}

long double Determinant(const Line &first, const Line &second) {
  return (first.a_index * second.b_index - second.a_index * first.b_index);
}

long double DistanceBetweenParallelLines(const Line &first, const Line &second) {
  long double distance =  Absolute((second.c_index - first.c_index)) /
                   sqrtl(first.a_index * first.a_index + first.b_index * first.b_index);
  if (distance == -0) {
    distance = 0;
  }
  return distance;
}

Line MakePerpendicularLine(const Line &source_line) {
  Line perpendicular_line(source_line.b_index, -source_line.a_index, 0);
  return perpendicular_line;
}


Vector FindIntersection(const Line &first, const Line &second) {
  long double determinant = Determinant(first, second);
  long double x = (second.b_index * first.c_index - first.b_index * second.c_index) / determinant;
  long double y = (first.a_index * second.c_index - second.a_index * first.c_index) / determinant;
  if (x == -0) {
    x = 0;
  }
  if (y == -0) {
    y = 0;
  }
  Vector intersection(x, y);
  return intersection;
}

long double AlternativeDistanceBetweenParallelLines(const Line &first, const Line &second) {
  Line perpendicular_line = MakePerpendicularLine(first);
  Vector first_intersection = FindIntersection(perpendicular_line, first);
  Vector second_intersection = FindIntersection(perpendicular_line, second);
  return Distance(first_intersection, second_intersection);
}

void IntersectionOrDistance(const Line &first, const Line &second) {
  long double determinant = Determinant(first, second);
  if (determinant == 0) {
    // cout << std::setprecision(6) << DistanceBetweenParallelLines(first, second) << '\n';
    cout << std::setprecision(6) << AlternativeDistanceBetweenParallelLines(first, second) << '\n';
    return;
  }
  long double x = (second.b_index * first.c_index - first.b_index * second.c_index) / determinant;
  long double y = (first.a_index * second.c_index - second.a_index * first.c_index) / determinant;
  if (x == -0) {
    x = 0;
  }
  if (y == -0) {
    y = 0;
  }
  cout << std::setprecision(6) << x << ' ' << y << '\n';
}

void Solve() {
  long double a1 = 0;
  long double b1 = 0;
  long double c1 = 0;
  long double a2 = 0;
  long double b2 = 0;
  long double c2 = 0;
  cin >> a1 >> b1 >> c1;
  cin >> a2 >> b2 >> c2;
  c1 = -c1;
  c2 = -c2;
  Line first(a1, b1, c1);
  Line second(a2, b2, c2);
  Vector first_v = ConvertLineToVector(first);
  Vector second_v = ConvertLineToVector(second);
  cout << std::setprecision(6) << first_v.x << ' ' << first_v.y << '\n';
  cout << std::setprecision(6) << second_v.x << ' ' << second_v.y << '\n';
  IntersectionOrDistance(first, second);
}

void Test1() {
  long double a1 = 1;
  long double b1 = 2;
  long double c1 = 19;
  long double a2 = 1;
  long double b2 = 3;
  long double c2 = 0;
  Line first(a1, b1, c1);
  Line second(a2, b2, c2);
  IntersectionOrDistance(first, second);
}

int main() { Solve(); }