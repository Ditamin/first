#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

class Edge {
 public:
  Edge(size_t end, size_t weight) : end(end), weight(weight) {
  }
 
  bool operator<(const Edge& other) const {
    return weight > other.weight;
  }

  size_t end;
  size_t weight;
};

class Vertex {
 public:
  std::vector<Edge> neighbours;
};

class Graph {
 public:
  friend std::istream& operator>>(std::istream& is, Graph& graph);
  size_t Prim();

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
    graph.vertexs_[--first].neighbours.emplace_back(Edge(--second, weight));
    graph.vertexs_[second].neighbours.emplace_back(Edge(first, weight));
  }

  return is;
}

size_t Graph::Prim() {
  size_t weight = 0;
  std::vector<Edge> edges;
  std::vector<size_t> dist(vertexs_.size(), std::numeric_limits<size_t>::max());
  std::vector<bool> used(vertexs_.size(), false);
  dist[0] = 0;
  edges.emplace_back(Edge(0, 0));

  while (!edges.empty()) {
    Edge cur = edges.front();
    std::pop_heap(edges.begin(), edges.end());
    edges.pop_back();

    if (!used[cur.end]) {
      used[cur.end] = true;
      weight += cur.weight;

      for (auto v : vertexs_[cur.end].neighbours) {
        if (!used[v.end] && dist[v.end] > v.weight) {
          edges.push_back(v);
          std::push_heap(edges.begin(), edges.end());
          dist[v.end] = v.weight;
        }
      }
    }
  }

  return weight;
}

int main() {
  Graph graph;
  std::cin >> graph;
  std::cout << graph.Prim();
}
