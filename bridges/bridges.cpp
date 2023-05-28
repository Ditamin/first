#include <iostream>
#include <vector>
#include <set>

enum Color { White, Grey, Black };

class Edge {
 public:
  Edge(int begin, int end, int idx) : begin(begin), end(end), idx(idx) {
  }
  
  bool operator<(const Edge& other) const {
    return end < other.end;
  }
  bool operator==(const Edge& other) const {
    return end == other.end;
  }
  
  int begin;
  int end;
  int idx;
  mutable bool multi = false;
};

class Vertex {
 public:
  std::set<Edge> neighbours;
  Color color = White;
  int time_up;
  int time_in;
};

class Graph {
 public:
  std::set<int> FindBridges();
  friend std::istream& operator>>(std::istream& is, Graph& graph);

 private:
  void DFS(std::set<int>& bridges, Vertex& cur, int parent);

  int time_ = 0;
  std::vector<Vertex> vertexs_;
};

std::istream& operator>>(std::istream& is, Graph& graph) {
  int n, m;
  is >> n >> m;
  graph.vertexs_.resize(n);

  for (int i = 0; i < m; ++i) {
    int begin, end;
    is >> begin >> end;
    Edge edge(--begin, --end, i + 1);
    auto it = graph.vertexs_[begin].neighbours.find(edge);

    if (it == graph.vertexs_[begin].neighbours.end()) {
      graph.vertexs_[begin].neighbours.insert(edge);
      graph.vertexs_[end].neighbours.insert(Edge(end, begin, i + 1));
    } else {
      it->multi = true;
      it = graph.vertexs_[end].neighbours.find(Edge(end, begin, i + 1));
      it->multi = true;
    }
  }

  return is;
}

void Graph::DFS(std::set<int>& bridges, Vertex& cur, int parent) {
  cur.color = Grey;
  cur.time_in = cur.time_up = ++time_;

  for (auto v : cur.neighbours) {
    if (v.end != parent) {
      if (vertexs_[v.end].color == Grey) {
        cur.time_up = std::min(cur.time_up, vertexs_[v.end].time_in);
      } else if (vertexs_[v.end].color == White) {
        DFS(bridges, vertexs_[v.end], v.begin);
        cur.time_up = std::min(cur.time_up, vertexs_[v.end].time_up);

        if (!v.multi && (cur.time_in < vertexs_[v.end].time_up)) {
          bridges.insert(v.idx);
        }
      }
    }
  }

  cur.color = Black;
}

std::set<int> Graph::FindBridges() {
  std::set<int> bridges;
  std::vector<Color> color(vertexs_.size());

  for (size_t i = 0; i < vertexs_.size(); ++i) {
    if (vertexs_[i].color == White) {
      DFS(bridges, vertexs_[i], i);
    }
  }

  return bridges;
}

int main() {
  Graph graph;
  std::cin >> graph;
  std::set<int> bridges = graph.FindBridges();
  std::cout << bridges.size() << "\n";

  for (auto i : bridges) {
    std::cout << i << "\n";
  }

  return 0;
}
