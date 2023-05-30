#include <iostream>
#include <vector>
#include <queue>
#include <stack>

class Graph {
 public:
  Graph(size_t n, size_t m) {
    vertexs_.resize(n);

    for (size_t i = 0; i < m; ++i) {
      size_t first, second;
      std::cin >> first >> second;
      vertexs_[--first].emplace_back(--second);
      vertexs_[second].emplace_back(first);
    }
  }

  std::vector<int> BFS(size_t v) const;

 private:
  std::vector<std::vector<size_t>> vertexs_;

  const std::vector<size_t>& Neighbours(const size_t& v) const {
    return vertexs_[v];
  }
};

std::vector<int> Graph::BFS(size_t v) const {
  std::vector<int> parent(vertexs_.size(), -1);
  parent[v] = v;
  std::queue<size_t> queue;
  queue.push(v);

  while (!queue.empty()) {
    size_t cur = queue.front();
    queue.pop();

    for (auto u : Neighbours(cur)) {
      if (parent[u] == -1) {
        queue.push(u);
        parent[u] = cur;
      }
    }
  }

  return parent;
}

void FindShortestWay(const Graph& graph, size_t st, size_t en) {
  auto parent = graph.BFS(st);

  if (parent[en] != -1) {
    int cur = en;
    std::stack<size_t> way;

    while (parent[cur] != cur) {
      way.push(cur);
      cur = parent[cur];
    }

    std::cout << way.size() << "\n" << st + 1 << " ";
    
    while (!way.empty()) {
      std::cout << way.top() + 1 << " ";
      way.pop();
    }
  } else {
    std::cout << -1;
  }
}

int main() {
  size_t n, m, st, en;
  std::cin >> n >> m >> st >> en;
  Graph graph(n, m);
  FindShortestWay(graph, --st, --en);
}
