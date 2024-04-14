#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

template <typename T>
void Swap(T object_a, T object_b) {
  T buffer_object = object_a;
  object_a = object_b;
  object_b = buffer_object;
}

struct DisjointSetUnion {
  DisjointSetUnion() = default;

  explicit DisjointSetUnion(int size) {
    parents.resize(size);
    heights.resize(size, 0);
    for (int i = 0; i < size; ++i) {
      parents[i] = i;
    }
  }

  vector<int> parents;
  vector<int> heights;

  int Leader(int element) {
    if (parents[element] == element) {
      return element;
    }
    parents[element] = Leader(parents[element]);
    return parents[element];
  }

  void Unite(int element_a, int element_b) {
    int a = Leader(element_a);
    int b = Leader(element_b);
    if (heights[a] > heights[b]) {  // parent — the element with < height
      Swap(a, b);
    }
    heights[b] = std::max(heights[b], heights[a] + 1);
    parents[a] = b;
  }
};

struct Edge {
  Edge() = default;
  Edge(int one, int two) {
    v1 = one;
    v2 = two;
  }
  int v1 = 0;
  int v2 = 0;
};

struct Graph {
  Graph() = default;

  explicit Graph(int vertexes_amount, int edges_amount) {
    amount_of_edges = edges_amount;
    amount_of_vertexes = vertexes_amount;
    edges.resize(amount_of_edges);
    vertexes_DSU = DisjointSetUnion(amount_of_vertexes);
  }

  void DisplayEdges() {
    for (unsigned int i = 0; i < edges.size(); ++i) {
      cout << edges[i].v1 + 1 << ' ';
      cout << edges[i].v2 + 1 << ' ';
    }
  }

  int amount_of_edges = 0;
  int amount_of_vertexes = 0;
  vector<Edge> edges;
  DisjointSetUnion vertexes_DSU;
  unsigned int last_taken_edge = 0;

  unsigned int FirstNEdges() {
    for (unsigned int i = 0; i < edges.size(); ++i) {
      Edge the_edge = edges[i];
      if (vertexes_DSU.Leader(the_edge.v1) != vertexes_DSU.Leader(the_edge.v2)) {
        vertexes_DSU.Unite(the_edge.v1, the_edge.v2);
        last_taken_edge = i + 1;
      }
    }
    return last_taken_edge;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n = 0;
  int m = 0;
  cin >> n >> m;
  Graph g(n, m);
  for (int i = 0; i < m; ++i) {
    int v1 = 0;
    int v2 = 0;
    cin >> v1;
    cin >> v2;
    g.edges[i] = Edge(v1, v2);
  }

  cout << g.FirstNEdges() << '\n';
}