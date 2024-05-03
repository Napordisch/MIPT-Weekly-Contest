#include <math.h>
#include <iostream>

template <typename T>
T absolufy(T number) {
  if (number < 0) {
    number *= (-1);
  }
  return number;
}

struct Vector {  // a.k.a. point
  Vector() = default;

  Vector(int new_x, int new_y) {
    x = new_x;
    y = new_y;
  }

  int x = 0;
  int y = 0;

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

  int operator^(const Vector &other) const {
    return (x * other.y) - (y * other.x);
  }

  int operator*(const Vector &other) const {
    return (x * other.x) + (y * other.y);
  }
};

long double VectorBasedTriangleArea(const Vector &first, const Vector &second) {
  return absolufy(static_cast<long double>(first ^ second)) / 2;
}

void Solve() {
  Vector vectors[2];
  for (int i = 0; i < 2; ++i) {
    using std::cin;
    int start_x = 0;
    int start_y = 0;
    cin >> start_x >> start_y;
    int end_x = 0;
    int end_y = 0;
    cin >> end_x >> end_y;
    vectors[i].x = end_x - start_x;
    vectors[i].y = end_y - start_y;
  }
  using std::cout;
  cout << vectors[0].Length() << ' ' << vectors[1].Length() << '\n';
  Vector sum = vectors[0] + vectors[1];
  cout << sum.x << ' ' << sum.y << '\n';
  cout << (vectors[0] * vectors[1]) << ' ' << (vectors[0] ^ vectors[1]) << '\n';
  cout << VectorBasedTriangleArea(vectors[0], vectors[1]) << '\n';
}

int main() { 
  Solve();
}