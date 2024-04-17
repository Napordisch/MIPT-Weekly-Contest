#include <climits>
#include <iostream>
#include <queue>
#include <vector>

using std::cin;
using std::cout;
using std::priority_queue;
using std::vector;

struct Edge {
  Edge(int t, int w) {
    to = t;
    weight = w;
  }
  int to;
  int weight;
};

class Graph {
 public:
  explicit Graph(int vertexes_amount) : vertexes_amount_(vertexes_amount) {
    adjacency_.resize(vertexes_amount_);
    used_.resize(vertexes_amount_, false);
  }

  void AddEdge(int vertex_1, int vertex_2, int w) {
    adjacency_[vertex_1 - 1].emplace_back(vertex_2 - 1, w);
    adjacency_[vertex_2 - 1].emplace_back(vertex_1 - 1, w);
  }

  int Prims() {
    vector<int> min_edge(vertexes_amount_, INT_MAX);
    min_edge[0] = 0;

    priority_queue<std::pair<int, int>, vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    pq.emplace(0, 0);

    int sum = 0;

    while (!pq.empty()) {
      int v = pq.top().second;
      int weight = pq.top().first;
      pq.pop();

      if (used_[v]) {
        continue;
      }
      used_[v] = true;
      sum += weight;

      for (const auto& u : adjacency_[v]) {
        if (!used_[u.to] && u.weight < min_edge[u.to]) {
          min_edge[u.to] = u.weight;
          pq.emplace(u.weight, u.to);
        }
      }
    }

    return sum;
  }

 private:
  vector<vector<Edge>> adjacency_;
  int vertexes_amount_;
  vector<bool> used_;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int n = 0;
  int m = 0;
  cin >> n >> m;
  if (m == 0) {
    cout << 0 << '\n';
    return 0;
  }
  Graph g(n);

  for (int i = 0; i < m; ++i) {
    int from = 0;
    int to = 0;
    int weight = 0;
    cin >> from >> to >> weight;
    g.AddEdge(from, to, weight);
  }
  int min_weight = g.Prims();
  cout << min_weight << '\n';
}