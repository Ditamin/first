#include <iostream>
#include <vector>

class OrGraph {
 public:
  int Size() const {
    return edges_.size();
  }
  void Floyd();
  friend std::istream& operator>>(std::istream& is, OrGraph& graph);

 private:
  std::vector<std::vector<int>> edges_;
  std::vector<std::vector<int>> dist_;
};

std::istream& operator>>(std::istream& is, OrGraph& graph) {
  int n;
  is >> n;
  graph.edges_.resize(n);
  graph.dist_.resize(n);

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      int value;
      is >> value;
      graph.edges_[i].emplace_back(value);
      graph.dist_[i].emplace_back(value);
    }
  }

  return is;
}

void OrGraph::Floyd() {
  for (size_t k = 0; k < edges_.size(); ++k) {
    for (size_t x = 0; x < edges_.size(); ++x) {
      for (size_t y = 0; y < edges_.size(); ++y) {
        dist_[x][y] = std::min(dist_[x][y], dist_[x][k] + dist_[k][y]);
      }
    }
  }

  for (size_t x = 0; x < edges_.size(); ++x) {
    for (size_t y = 0; y < edges_.size(); ++y) {
      std::cout << dist_[x][y] << " ";
    }

    std::cout << "\n";
  }
}

int main() {
  OrGraph graph;
  std::cin >> graph;
  graph.Floyd();
  return 0;
}
