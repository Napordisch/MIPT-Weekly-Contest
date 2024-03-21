#include <climits>
#include <iostream>

using std::cin;
using std::cout;
using std::min;

template <typename T>
void DeleteTwoDimensionalArray(T array, size_t size) {
  for (size_t i = 0; i < size; ++i) {
    delete[] array[size];
  }
  delete[] array;
}

class Graph {
 public:
  explicit Graph(int vertexes_amount) {
    vertexes_amount_ = vertexes_amount;
    graph_ = new int *[vertexes_amount_];
    for (int i = 0; i < vertexes_amount_; ++i) {
      graph_[i] = new int[vertexes_amount_];
    }
  }

  ~Graph() {
    DeleteTwoDimensionalArray(graph_, vertexes_amount_);
  }

  void Fill(int i, int j, int value) { graph_[i][j] = value; }

  void Display() {
    for (int i = 0; i < vertexes_amount_; ++i) {
      for (int j = 0; j < vertexes_amount_; ++j) {
        cout << graph_[i][j] << " ";
      }
      cout << "\n";
    }
  }

  void Dijkstra(int start, int destination) {
    auto *dist = new int[vertexes_amount_];
    for (int i = 0; i < vertexes_amount_; ++i) {
      dist[i] = INT_MAX;
    }
    auto *used = new bool[vertexes_amount_]{};
    dist[start] = 0;
    int current_vertex = start;
    for (int i = 0; i < vertexes_amount_ ++i) {

    cout << dist[destination] << "\n";
    cout << "Distances:" << "\n";
    for (int i = 0; i < vertexes_amount_; ++i) {
      cout << dist[i] << " ";
    }

    delete[] dist;
    delete[] used;
  }

 private:
  int **graph_ = nullptr;
  int vertexes_amount_ = 0;
};

int main() {
  int n = 0;
  int s = 0;
  int f = 0;
  cin >> n >> s >> f;
  Graph g(n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      int value;
      cin >> value;
      g.Fill(i, j, value);
    }
  }
  g.Display();
  g.Dijkstra(s -1, f - 1);

  return 0;
}
