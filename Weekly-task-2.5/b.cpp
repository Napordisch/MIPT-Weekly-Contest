#include <cstdint>
#include <climits>
#include <iostream>

using std::cin;
using std::cout;
using std::min;

template <typename T>
void DeleteTwoDimensionalArray(T array, int16_t size) {
  for (int16_t i = 0; i < size; ++i) {
    delete[] array[i];
  }
  delete[] array;
}

class Graph {
 public:
  explicit Graph(int16_t vertexes_amount) {
    vertexes_amount_ = vertexes_amount;
    graph_ = new int16_t *[vertexes_amount_];
    for (int16_t i = 0; i < vertexes_amount_; ++i) {
      graph_[i] = new int16_t[vertexes_amount_];
      for (int16_t j = 0; j < vertexes_amount_; ++j) {
        if (i == j) {
          graph_[i][j] = 0;
          continue;
        }
        graph_[i][j] = -1;
      }
    }
  }

  ~Graph() {
    DeleteTwoDimensionalArray(graph_, vertexes_amount_);
  }

  void Fill(int16_t i, int16_t j, int16_t value) {
    graph_[i][j] = value;
  }

  void Display() {
    for (int16_t i = 0; i < vertexes_amount_; ++i) {
      for (int16_t j = 0; j < vertexes_amount_; ++j) {
        cout << graph_[i][j] << " ";
      }
      cout << "\n";
    }
  }

  void Dijkstra(int16_t start, int16_t destination) {
    auto *dist = new int16_t[vertexes_amount_];
    auto *used = new bool[vertexes_amount_]{};
    for (int16_t i = 0; i < vertexes_amount_; ++i) {
      used[i] = false;
      dist[i] = SHRT_MAX;
    }

    dist[start] = 0;
    for (int16_t i = 0; i < vertexes_amount_; ++i) {
      int16_t chosen_vertex = -1;
      // looking for min vertex
      for (int16_t j = 0; j < vertexes_amount_; ++j) {
        if (!used[j] && (chosen_vertex == -1 || dist[j] < dist[chosen_vertex])) {
          chosen_vertex = j;
        }
      }

      if (dist[chosen_vertex] == SHRT_MAX) {
        break;
      }

      used[chosen_vertex] = true;

      // assigning new distances
      for (int16_t child = 0; child < vertexes_amount_; ++child) {
        if (graph_[chosen_vertex][child] == -1 || chosen_vertex == child) {
          continue;
        }
        if (dist[chosen_vertex] + graph_[chosen_vertex][child] < dist[child]) {
          dist[child] = static_cast<int16_t>(dist[chosen_vertex] + graph_[chosen_vertex][child]);
        }
      }
    }

    // result
    int16_t wanted_dist = dist[destination];
    if (wanted_dist != SHRT_MAX) {
      cout << wanted_dist << "\n";
    } else {
      cout << "-1"
           << "\n";
    }
    delete[] dist;
    delete[] used;
  }

 private:
  int16_t **graph_ = nullptr;
  int16_t vertexes_amount_ = 0;
};

int main() {
  int16_t n = 0;
  int16_t m = 0;
  int16_t s = 0;
  int16_t f = 0;
  cin >> n >> m;
  cin >> s >> f;
  Graph g(n);
  for (int16_t i = 0; i < m; ++i) {
    int16_t a = 0;
    int16_t b = 0;
    int16_t t = 0;
    cin >> a >> b >> t;
    g.Fill(static_cast<int16>(a - 1), static_cast<int16_t>(b - 1), t);
  }
  g.Dijkstra(static_cast<int16_t>(s - 1), static_cast<int16_t>(f - 1));

  return 0;
}
