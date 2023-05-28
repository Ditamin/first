#include <iostream>
#include <vector>

enum Color { White, Grey, Black };

class Vertex {
 public:
  Vertex() = default;
  explicit Vertex(size_t idx) : idx(idx) {
  }
 
  size_t idx;
  Color color = White;
};

class OrGraph {
 public:
  void FindCycle();
  friend std::istream& operator>>(std::istream& is, OrGraph& graph);

 private:
  void DFS(Vertex& cur);
  void PrintCycle(Vertex& cur);

  std::vector<std::vector<size_t>> neighbours_;
  std::vector<Vertex> vertexs_;
  bool cycle_ = false;
};

std::istream& operator>>(std::istream& is, OrGraph& graph) {
  size_t n, m;
  is >> n >> m;
  graph.neighbours_.resize(n);
  graph.vertexs_.resize(n);

  for (size_t i = 0; i < n; ++i) {
    graph.vertexs_[i].idx = i;
  }

  for (size_t i = 0; i < m; ++i) {
    size_t st, en;
    is >> st >> en;
    graph.neighbours_[--st].push_back(--en);
  }

  return is;
}

void OrGraph::PrintCycle(Vertex& cur) {
  std::cout << cur.idx + 1 << " ";
  cur.color = Black;

  for (auto v : neighbours_[cur.idx]) {
    if (vertexs_[v].color == Grey) {
      PrintCycle(vertexs_[v]);
      return;
    }
  }
}

void OrGraph::DFS(Vertex& cur) {
  cur.color = Grey;

  for (auto v : neighbours_[cur.idx]) {
    if (vertexs_[v].color == White) {
      DFS(vertexs_[v]);

      if (cycle_) {
        return;
      }
    } else if (vertexs_[v].color == Grey) {
      std::cout << "YES\n";
      cycle_ = true;
      PrintCycle(vertexs_[v]);
      return;
    }
  }

  cur.color = Black;
}

void OrGraph::FindCycle() {
  for (size_t i = 0; i < vertexs_.size(); ++i) {
    if (vertexs_[i].color == White) {
      DFS(vertexs_[i]);

      if (cycle_) {
        return;
      }
    }
  }

  std::cout << "NO\n";
}

int main() {
  OrGraph graph;
  std::cin >> graph;
  graph.FindCycle();
}
