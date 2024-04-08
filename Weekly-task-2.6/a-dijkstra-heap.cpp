#include <climits>
#include <iostream>
#include <queue>
#include <vector>
#include <set>

using std::cin;
using std::cout;
using std::min;

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

  void Dijkstra(int start, int destination) {
    auto *dist = new int[vertexes_amount_];
    auto *used = new bool[vertexes_amount_]{};
    for (int i = 0; i < vertexes_amount_; ++i) {
      used[i] = false;
      dist[i] = INT_MAX;
    }
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> q;
    q.emplace(0, start);

    dist[start] = 0;
    while (!q.empty()) {

      // looking for min vertex
      std::pair<int, int> min_vertex = q.top();
      int chosen_vertex = min_vertex.second;
      q.pop();

      if (chosen_vertex == destination) {
        break;
      }

      if (used[chosen_vertex]) {
        continue;
      }

      if (dist[chosen_vertex] == INT_MAX) {
        break;
      }

      used[chosen_vertex] = true;

      // assigning new distances
      for (int child = 0; child < vertexes_amount_; ++child) {
        if (graph_[chosen_vertex][child] == -1 || chosen_vertex == child) {
          continue;
        }
        if (dist[chosen_vertex] + graph_[chosen_vertex][child] < dist[child]) {
          dist[child] = dist[chosen_vertex] + graph_[chosen_vertex][child];
          q.emplace(dist[child], child);
        }
      }
    }

    // result
    int wanted_dist = dist[destination];
    if (wanted_dist != INT_MAX) {
      cout << wanted_dist << "\n";
    } else {
      cout << "-1"
           << "\n";
    }
    delete[] dist;
    delete[] used;
  }

 private:
  int **graph_ = nullptr;
  int vertexes_amount_ = 0;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
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
  g.Dijkstra(s - 1, f - 1);

  return 0;
}
