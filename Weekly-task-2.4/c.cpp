#include <cstdint>
#include <iostream>
#include <list>

using std::cin;
using std::cout;
using std::list;

class Graph {
 public:
  void Euler(uint32_t vertex) {
    for (uint32_t p = 0; p < vertexes_amount_; ++p) {
      while (table_[vertex][p] > 0) {
        table_[vertex][p]--;
        Euler(p);
      }
    }
    euler_path_.push_front(vertex);
  }

  uint32_t AmountOfVertexes() {
    return vertexes_amount_;
  }

  explicit Graph(uint32_t vertexes_amount) {
    vertexes_amount_ = vertexes_amount;
    table_ = new uint32_t *[vertexes_amount_];
    for (uint32_t i = 0; i < vertexes_amount_; ++i) {
      table_[i] = new uint32_t[vertexes_amount_];
    }
  }

  ~Graph() {
    for (uint32_t i = 0; i < vertexes_amount_; ++i) {
      delete[] table_[i];
    }
    delete[] table_;
  }

  void IncreaseEdge(uint32_t from, uint32_t to) {
    if (table_[from - 1][to - 1] == 0) {
      edges_amount_++;
    }
    table_[from - 1][to - 1]++;
  }

  void DisplayTable() {
    for (uint32_t i = 0; i < vertexes_amount_; ++i) {
      for (uint32_t j = 0; j < vertexes_amount_; ++j) {
        cout << table_[i][j] << " ";
      }
      cout << "\n";
    }
  }

  void DisplayEdges() {
    cout << vertexes_amount_ << " " << edges_amount_ << "\n";
    for (uint32_t i = 0; i < vertexes_amount_; ++i) {
      for (uint32_t j = 0; j < vertexes_amount_; ++j) {
        if (table_[i][j] > 0) {
          cout << i + 1 << " " << j + 1 << " " << table_[i][j] << "\n";
        }
      }
    }
  }

  void DisplayEulerPath() {
    while (!euler_path_.empty()) {
      cout << euler_path_.front() + 1 << " ";
      euler_path_.pop_front();
    }
  }

  void ShowEulerPath() {
    if (!euler_path_.empty()) {
      euler_path_.clear();
    }
    Euler(0);
    cout << euler_path_.size() << " ";
    DisplayEulerPath();
  }

 private:
  list<uint32_t> euler_path_;
  uint32_t **table_ = nullptr;
  uint32_t vertexes_amount_ = 0;
  uint32_t edges_amount_ = 0;
};

int main() {
  uint32_t n = 0;
  uint32_t m = 0;
  cin >> n >> m;

  Graph city(m);
  for (uint32_t i = 0; i < n; ++i) {
    uint32_t route_elements_amount = 0;
    cin >> route_elements_amount;
    list<uint32_t> points;
    for (uint32_t j = 0; j < route_elements_amount + 1; ++j) {
      uint32_t point = 0;
      cin >> point;
      points.push_back(point);
      if (points.size() == 2) {
        city.IncreaseEdge(points.front(), points.back());
        points.pop_front();
      }
    }
  }
  city.ShowEulerPath();
}
