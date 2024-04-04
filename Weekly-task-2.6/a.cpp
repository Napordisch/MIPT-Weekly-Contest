#include <cstdint>
#include <climits>
#include <iostream>
#include <vector>
#include <queue>

using std::cin;
using std::cout;
using std::min;

struct Vertex {
  Vertex(unsigned int dist, unsigned int i) {
    distance = dist;
    index = i;
  }
  unsigned int distance = 0;
  unsigned int index = 0;
  bool operator< (const Vertex& other) {
    return distance < other.distance;
  }
  bool operator> (const Vertex& other) {
    return distance > other.distance;
  }
};

template <typename T>
void DeleteTwoDimensionalArray(T array, size_t size) {
  for (size_t i = 0; i < size; ++i) {
    delete[] array[i];
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

  void Fill(int i, int j, int value) {
    graph_[i][j] = value;
  }

  void Display() {
    for (int i = 0; i < vertexes_amount_; ++i) {
      for (int j = 0; j < vertexes_amount_; ++j) {
        cout << graph_[i][j] << " ";
      }
      cout << "\n";
    }
  }

  unsigned int Roche(int start, int destination) {
    std::vector<unsigned int> distances(vertexes_amount_, UINT32_MAX);
    distances[start] = 0;
    std::priority_queue<Vertex, std::vector<Vertex>, std::greater<void>> q;
    q.push(Vertex(distances[start], start));
    while (!q.empty()) {
      Vertex top_vertex = q.top();
      q.pop();
      if (top_vertex.distance > distances[top_vertex.index]) {
        continue;
      }

      for (unsigned int u = 0; u < vertexes_amount_; ++u) {
        unsigned int current_edge = graph_[top_vertex.index][u] == -1;
        if (u == top_vertex.index || current_edge == -1) {
          continue;
        }
        if (distances[u] > distances[top_vertex.index] + current_edge) {
          distances[u] = distances[top_vertex.index] + current_edge;
          q.push(Vertex(distances[u], u));
        }
      }

    }

  return distances[destination];
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
      int value = 0;
      cin >> value;
      g.Fill(i, j, value);
    }
  }
  g.Display();
  std::cout << g.Roche(s - 1, f - 1) << '\n';

  return 0;
}