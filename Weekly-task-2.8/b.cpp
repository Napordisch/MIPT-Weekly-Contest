#include <cmath>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

using std::cin;
using std::cout;

using std::priority_queue;
using std::vector;

float Q_rsqrt(float number)
{
  long i;
  float x2, y;
  const float threehalfs = 1.5F;

  x2 = number * 0.5F;
  y  = number;
  i  = * ( long * ) &y;                       // evil floating point bit level hacking
  i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
  y  = * ( float * ) &i;
  y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
  // y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

  return y;
}

struct Object {
  Object() = default;
  Object(int new_x, int new_y, int new_v) {
    SetValues(new_x, new_y, new_v);
  }
  void SetValues(int new_x, int new_y, int new_v) {
    x = new_x;
    y = new_y;
    v = new_v;
  }

  int GetSquaredSpeed() {
    return v * v;
  }
  int x = 0;
  int y = 0;
  int v = 0;
};

struct Destination {
  Destination() = default;
  Destination(int new_a, int new_b) {
    SetValues(new_a, new_b);
  }
  void SetValues(int new_a, int new_b) {
    a = new_a;
    b = new_b;
  }
  int a = 0;
  int b = 0;
};

int GetSquaredDistnace(Object from, Destination to) {
  int x_dist = to.a - from.x;
  int y_dist = to.b - from.y;
  return (x_dist * x_dist) + (y_dist * y_dist);
}

double GetTime(Object from, Destination to) {
  return sqrt(GetSquaredDistnace(from, to)) / sqrt(from.GetSquaredSpeed());
}

template <typename T>
void DisplayTable(const vector<vector<T>> &table) {
  cout << '\n';
  cout << "Table:\n";
  for (int i = 0; i < static_cast<int>(table.size()); ++i) {
    for (int j = 0; j < (table[i].size()); ++j) {
      cout << table[i][j] << '\t';
    }
    cout << '\n';
  }
}

double FindMin(const vector<vector<double>> &table, int n, vector<bool> objects_used, vector<bool> destinations_used,
               bool root = true, int from_i = 0, int from_j = 0, double cur_max = 0) {
  if (!root) {
    objects_used[from_i] = true;
    destinations_used[from_j] = true;
    cur_max = std::max(table[from_i][from_j], cur_max);
  }

  bool last = true;
  static double the_min = std::numeric_limits<double>::max();
  for (int i = 0; i < n; ++i) {
    if (objects_used[i]) {
      continue;
    }
    for (int j = 0; j < n; ++j) {
      if (destinations_used[j]) {
        continue;
      }

      double found_min = FindMin(table, n, objects_used, destinations_used, false, i, j, cur_max);
      last = false;
      the_min = std::min(found_min, the_min);
    }
  }

  if (last) {
    return cur_max;
  }

  return the_min;
}

int main() {
  int n = 0;
  cin >> n;
  vector<Object> objects(n);
  vector<Destination> destinations(n);
  for (int i = 0; i < n; ++i) {
    int new_x = 0;
    int new_y = 0;
    int new_v = 0;
    cin >> new_x >> new_y >> new_v;
    objects[i].SetValues(new_x, new_y, new_v);
  }
  for (int i = 0; i < n; ++i) {
    int new_a = 0;
    int new_b = 0;
    cin >> new_a >> new_b;
    destinations[i].SetValues(new_a, new_b);
  }
  vector<vector<double>> table(n, vector<double>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      table[i][j] = GetTime(objects[i], destinations[j]);
    }
  }

  cout << '\n';
  vector<bool> objects_used(n, false);
  vector<bool> destinations_used(n, false);
  cout << FindMin(table, n, objects_used, destinations_used);
}