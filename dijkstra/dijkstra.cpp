#include <iostream>
#include <vector>
#include <algorithm>

class Edge {
 public:
  Edge(int begin, int end, int weight) : begin(begin), end(end), weight(weight) {
  }
  bool operator<(const Edge& other) const {
    return weight > other.weight;
  }

  int begin;
  int end;
  int weight;
};

class Vertex {
 public:
  std::vector<Edge> neighbours;
};

class Graph {
 public:
  std::vector<int> Dijkstra(int cur);
  friend std::istream& operator>>(std::istream& is, Graph& graph);

 private:
  std::vector<Vertex> vertexs_;
};

std::istream& operator>>(std::istream& is, Graph& graph) {
  size_t n, m;
  is >> n >> m;
  graph.vertexs_.resize(n);

  for (size_t i = 0; i < m; ++i) {
    size_t first, second, weight;
    is >> first >> second >> weight;
    graph.vertexs_[first].neighbours.emplace_back(Edge(first, second, weight));
    graph.vertexs_[second].neighbours.emplace_back(Edge(second, first, weight));
  }

  return is;
}

std::vector<int> Graph::Dijkstra(int cur) {
  int limit = 2009000999;
  std::vector<Edge> edges;
  std::vector<int> dist(vertexs_.size(), limit);
  std::vector<bool> used(vertexs_.size(), false);
  dist[cur] = 0;

  edges.emplace_back(Edge(cur, cur, 0));

  while (!edges.empty()) {
    Edge cur = edges.front();
    std::pop_heap(edges.begin(), edges.end());
    edges.pop_back();

    if (!used[cur.end]) {
      used[cur.end] = true;

      for (auto v : vertexs_[cur.end].neighbours) {
        if (!used[v.end] && (dist[v.end] > (v.weight + dist[v.begin]))) {
          v.weight += dist[v.begin];
          edges.push_back(v);
          std::push_heap(edges.begin(), edges.end());
          dist[v.end] = v.weight;
        }
      }
    }
  }

  return dist;
}

int main() {
  int k;
  std::cin >> k;

  for (int i = 0; i < k; ++i) {
    Graph graph;
    std::cin >> graph;
    int start;
    std::cin >> start;

    for (auto i : graph.Dijkstra(start)) {
      std::cout << i << " ";
    }

    std::cout << "\n";
  }
}
