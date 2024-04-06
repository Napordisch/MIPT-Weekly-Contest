void GraphListDisplay(const vector<vector<Edge> > &graph_list) {
  for (unsigned int i = 0; i < graph_list.size(); ++i) {
    cout << "from " << i + 1 << ':' << ' ';
    for (unsigned int j = 0; j < graph_list[i].size(); ++j) {
      cout << graph_list[i][j].to + 1 << ' ';
    }
    cout << '\n';
  }
}