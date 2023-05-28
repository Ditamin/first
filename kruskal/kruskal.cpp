#include <iostream>
#include <vector>
#include <algorithm>

class SDS {
 public:
  explicit SDS(int n) {
    parent_.resize(n, -1);
    rank_.resize(n, 1);
  }
  int FindSet(int idx);
  void Union(int first, int second);

 private:
  std::vector<int> parent_;
  std::vector<int> rank_;
};

class Edge {
 public:
  Edge(int begin, int end, int weight) : begin(begin), end(end), weight(weight) {
  }
  bool operator<(const Edge& other) const {
    return weight < other.weight;
  }

  int begin;
  int end;
  int weight;
};

int SDS::FindSet(int idx) {
  if (parent_[idx] == -1) {
    return idx;
  }

  return parent_[idx] = FindSet(parent_[idx]);
}

void SDS::Union(int first, int second) {
  int first_parent = FindSet(first);
  int second_parent = FindSet(second);

  if (rank_[first_parent] > rank_[second_parent]) {
    parent_[second_parent] = first_parent;
  } else if (rank_[first_parent] < rank_[second_parent]) {
    parent_[first_parent] = second_parent;
  } else {
    parent_[second_parent] = first_parent;
    ++rank_[first_parent];
  }
}

int Kruskal(int n, std::vector<Edge>& edges) {
  SDS sets(n);
  int weight = 0;

  for (auto edge : edges) {
    if (sets.FindSet(edge.begin) != sets.FindSet(edge.end)) {
      weight += edge.weight;
      sets.Union(edge.begin, edge.end);
    }
  }

  return weight;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n, m;
  std::cin >> n >> m;
  std::vector<Edge> edges;

  for (int i = 0; i < m; ++i) {
    int begin, end, weight;
    std::cin >> begin >> end >> weight;
    edges.emplace_back(Edge(--begin, --end, weight));
  }

  std::cout << Kruskal(n, edges);
  return 0;
}
