#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

bool Bipartiteness(vector<uint16_t> *prox_list, uint16_t cur_node, int16_t *colours, int16_t colour) {
  colours[cur_node] = colour;
  vector<uint16_t> &children = prox_list[cur_node];
  uint16_t amount_of_children = children.size();
  for (uint16_t i = 0; i < amount_of_children; ++i) {
    if (colours[children[i]] == 0) {
      bool Bipartited = Bipartiteness(prox_list, children[i], colours, -colour);
      if (Bipartited == false) {
        return Bipartited;
      }
    }
    else if (colours[children[i]] == colour) {
      return false;
    }
  }
  return true;
}

int main() {
  uint16_t n, m;
  cin >> n;
  cin >> m;
  auto* proximity = new vector<uint16_t>[n];
  for (uint16_t i = 0; i < m; ++i) {
    uint16_t student_1, student_2;
    cin >> student_1 >> student_2;
    proximity[student_1 - 1].push_back(student_2 - 1);
    proximity[student_2 - 1].push_back(student_1 - 1);
  }
  int16_t *colours = new int16_t[n]{0};
  for (uint16_t i = 0; i < n; ++i) {
    for (uint16_t j = 0; j < proximity[i].size(); ++j) {
      cout << proximity[i][j] << " ";
    }
    cout << "\n";
  }
  cout << "\n";
  bool bipartited = Bipartiteness(proximity, 0, colours, 1);
  if (bipartited) {
    cout << "YES" << "\n";
  } else {
    cout << "NO" << "\n";
  }
  delete[] proximity;
  delete[] colours
  return 0;
}
