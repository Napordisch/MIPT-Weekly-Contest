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
  Line(double a, double b, double c) {
    a_index = a;
    b_index = b;
    c_index = c;
  }
  double a_index = 0;
  double b_index = 0;
  double c_index = 0;
};

struct Vector {  // a.k.a. point
  Vector() = default;

  Vector(double new_x, double new_y) {
    x = new_x;
    y = new_y;
  }

  double x = 0;
  double y = 0;

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


Vector ConvertLineToVector(Line l) {
  Vector normal(l.a_index, l.b_index);

  return Vector(normal.y, -normal.x);
}

double Determinant(const Line &first, const Line &second) {
  return (first.a_index * second.b_index - second.a_index * first.b_index);
}

double DistanceBetweenParallelLines(const Line &first, const Line &second) {
  return Absolute((first.c_index - second.c_index) /
                  sqrtl(first.a_index * first.a_index + first.b_index * first.b_index));
}

void IntersectionOrDistance(const Line &first, const Line &second) {
  double determinant = Determinant(first, second);
  if (determinant == 0) {
    cout << std::setprecision(7) << DistanceBetweenParallelLines(first, second) << '\n';
    return;
  }
  double x = ( - second.b_index * first.c_index + first.b_index * second.c_index) / determinant;
  double y = ( - first.a_index * second.c_index + second.a_index * first.c_index) / determinant;
  cout << std::setprecision(7) << x << ' ' << y << '\n';
}

void Solve() {
  double a1 = 0;
  double b1 = 0;
  double c1 = 0;
  double a2 = 0;
  double b2 = 0;
  double c2 = 0;
  cin >> a1 >> b1 >> c1;
  cin >> a2 >> b2 >> c2;
  Line first(a1, b1, c1);
  Line second(a2, b2, c2);
  Vector first_v = ConvertLineToVector(first);
  Vector second_v = ConvertLineToVector(second);
  cout << std::setprecision(7) << first_v.x << ' ' << first_v.y << '\n';
  cout << std::setprecision(7) << second_v.x << ' ' << second_v.y << '\n';
  IntersectionOrDistance(first, second);
}

void Test1() {
  double a1 = 1;
  double b1 = 2;
  double c1 = 19;
  double a2 = 1;
  double b2 = 3;
  double c2 = 0;
  Line first(a1, b1, c1);
  Line second(a2, b2, c2);
  IntersectionOrDistance(first, second);
}

int main() { Solve(); }