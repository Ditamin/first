#include <iostream>
#include <vector>
#include <set>

enum Color { White, Grey, Black };

class Vertex {
 public:
  Vertex() = default;
  explicit Vertex(size_t idx) : idx(idx) {
  }
  bool operator<(const Vertex& other) const {
    return idx < other.idx;
  }

  size_t idx;
  Color color = White;
  size_t time_in;
  size_t time_up;
};

class Graph {
 public:
  std::set<Vertex> FindArticulationPoints();
  friend std::istream& operator>>(std::istream& is, Graph& graph);

 private:
  void DFS(std::set<Vertex>& articulation_points, Vertex& cur, Vertex& parent, bool is_root);

  std::vector<std::vector<size_t>> neighbours_;
  std::vector<Vertex> vertexs_;
  size_t time_ = 0;
};

std::istream& operator>>(std::istream& is, Graph& graph) {
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
    graph.neighbours_[en].push_back(st);
  }

  return is;
}

void Graph::DFS(std::set<Vertex>& articulation_points, Vertex& cur, Vertex& parent, bool is_root) {
  cur.color = Grey;
  cur.time_in = cur.time_up = ++time_;
  size_t n_childs = 0;

  for (auto v : neighbours_[cur.idx]) {
    if (v != parent.idx) {
      if (vertexs_[v].color == Grey) {
        cur.time_up = std::min(cur.time_up, vertexs_[v].time_in);
      } else if (vertexs_[v].color == White) {
        DFS(articulation_points, vertexs_[v], cur, false);
        ++n_childs;
        cur.time_up = std::min(cur.time_up, vertexs_[v].time_up);

        if ((!is_root) && (cur.time_in <= vertexs_[v].time_up)) {
          articulation_points.insert(cur);
        }
      }
    }
  }
  
  if (is_root && (n_childs > 1)) {
    articulation_points.insert(cur);
  }

  cur.color = Black;
}

std::set<Vertex> Graph::FindArticulationPoints() {
  std::set<Vertex> articulation_points;
  std::vector<Color> color(vertexs_.size());

  for (size_t i = 0; i < vertexs_.size(); ++i) {
    if (vertexs_[i].color == White) {
      DFS(articulation_points, vertexs_[i], vertexs_[i], true);
    }
  }

  return articulation_points;
}

int main() {
  Graph graph;
  std::cin >> graph;
  std::set<Vertex> articulation_points = std::move(graph.FindArticulationPoints());
  std::cout << articulation_points.size() << "\n";

  for (auto i : articulation_points) {
    std::cout << i.idx + 1 << "\n";
  }
}
