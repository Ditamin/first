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

class OrGraph {
 public:
  int Johnson();
  std::vector<int> BellmanFord(int cur);
  std::vector<int> Dijkstra(int cur);
  friend std::istream& operator>>(std::istream& is, OrGraph& graph);

 private:
  void Relax(std::vector<int>& dist, Edge& edge);
  std::vector<Vertex> vertexs_;
  int limit_ = 2009000999;
};

std::istream& operator>>(std::istream& is, OrGraph& graph) {
  int n, m;
  is >> n >> m;
  graph.vertexs_.resize(n);

  for (int i = 0; i < m; ++i) {
    int begin, end, weight;
    is >> begin >> end >> weight;
    graph.vertexs_[begin].neighbours.emplace_back(Edge(begin, end, weight));
  }

  return is;
}

void OrGraph::Relax(std::vector<int>& dist, Edge& edge) {
  if ((dist[edge.begin] != limit_) && (edge.weight + dist[edge.begin] < dist[edge.end])) {
    dist[edge.end] = edge.weight + dist[edge.begin];
  }
}

std::vector<int> OrGraph::BellmanFord(int cur) {
  std::vector<int> dist(vertexs_.size(), limit_);
  dist[cur] = 0;

  for (size_t i = 0; i < vertexs_.size(); ++i) {
    for (size_t j = 0; j < vertexs_.size(); ++j) {
      for (size_t k = 0; k < vertexs_[j].neighbours.size(); ++k) {
        Relax(dist, vertexs_[j].neighbours[k]);
      }
    }
  }

  return dist;
}

std::vector<int> OrGraph::Dijkstra(int cur) {
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

int OrGraph::Johnson() {
  Vertex s;

  for (size_t i = 0; i < vertexs_.size(); ++i) {
    s.neighbours.emplace_back(Edge(vertexs_.size(), i, 0));
  }

  vertexs_.emplace_back(s);
  std::vector<int> dist = BellmanFord(vertexs_.size() - 1);
  vertexs_.pop_back();

  for (size_t i = 0; i < vertexs_.size(); ++i) {
    for (size_t j = 0; j < vertexs_[i].neighbours.size(); ++j) {
      vertexs_[i].neighbours[j].weight += dist[i] - dist[vertexs_[i].neighbours[j].end];
    }
  }

  int max = 0;

  for (size_t i = 0; i < vertexs_.size(); ++i) {
    std::vector<int> res = Dijkstra(i);

    for (size_t j = 0; j < res.size(); ++j) {
      if (res[j] != 2009000999) {
        max = std::max(max, res[j] - dist[i] + dist[j]);
      }
    }
  }

  return max;
}

int main() {
  OrGraph graph;
  std::cin >> graph;
  std::cout << graph.Johnson();
  return 0;
}
