#include <iostream>
#include <vector>
#include <climits>

#define INF INT_MAX

class Graph {
 public:
  explicit Graph(const std::vector<std::vector<int>>& matrix) : matrix_(matrix) {
    n_ = static_cast<int>(matrix_.size());
    dists_.resize(n_, std::vector<int>(n_, INF));
    Build();
  }

  const std::vector<std::vector<int>>& GetDist() {
    return dists_;
  }

 private:
  void Build() {
    dists_ = matrix_;
    for (int i = 0; i < n_; i++) {
      for (int u = 0; u < n_; u++) {
        for (int v = 0; v < n_; v++) {
          dists_[u][v] = std::min(dists_[u][v], dists_[u][i] + dists_[i][v]);
        }
      }
    }
  }

  int n_;
  std::vector<std::vector<int>> matrix_;
  std::vector<std::vector<int>> dists_;
};

int main() {
  int n = 0;
  std::cin >> n;
  std::vector<std::vector<int>> matrix(n, std::vector<int>(n));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      std::cin >> matrix[i][j];
    }
  }

  Graph g(matrix);

  for (const std::vector<int>& row : g.GetDist()) {
    for (int i : row) {
      std::cout << i << ' ';
    }
    std::cout << std::endl;
  }

  return 0;
}

