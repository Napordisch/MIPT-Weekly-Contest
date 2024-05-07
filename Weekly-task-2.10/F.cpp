#include <iostream>
#include <vector>
#include <iomanip>

using std::cin;
using std::cout;

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

double GetY(Line l, double x) {
  return ((l.a_index * x) + l.c_index) / ((-1) * l.b_index);
}

Vector ConvertLineToVector(Line l) {
  double x1 = 0;
  double x2 = 1;
  double y1 = GetY(l, x1);
  double y2 = GetY(l, x2);
  return Vector(x2 - x1, y2 - y1);
}

int main() {
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
  Vector second_v= ConvertLineToVector(second);
  cout << std::setprecision(7) << first_v.x << ' ' << first_v.y << '\n';
  cout << std::setprecision(7) << second_v.x << ' ' << second_v.y << '\n';
}