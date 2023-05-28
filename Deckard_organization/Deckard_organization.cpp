#include <iostream>

struct Node {
  int key;
  int prior;
  Node* left = nullptr;
  Node* right = nullptr;
  Node* parent = nullptr;
};

Node** MakeTreap(int n) {
  auto treap = new Node*[n];
  Node* parent = nullptr;
  Node* son = nullptr;

  for (int i = 0; i < n; ++i) {
    int num, prior;
    std::cin >> num >> prior;
    auto new_elem = new Node{num, prior};
    treap[i] = new_elem;
    new_elem->key = i + 1;

    while ((parent != nullptr) && (prior < parent->prior)) {
      son = parent;
      parent = parent->parent;
    }

    new_elem->left = son;
    new_elem->parent = parent;

    if (son != nullptr) {
      son->parent = new_elem;
      son = nullptr;
    }

    if (parent != nullptr) {
      parent->right = new_elem;
    }

    parent = new_elem;
  }

  return treap;
}

int main() {
  int n;
  std::cin >> n;
  auto treap = MakeTreap(n);
  std::cout << "YES\n";

  for (int i = 0; i < n; ++i) {
    std::cout << (treap[i]->parent != nullptr ? treap[i]->parent->key : 0) << " ";
    std::cout << (treap[i]->left != nullptr ? treap[i]->left->key : 0) << " ";
    std::cout << (treap[i]->right != nullptr ? treap[i]->right->key : 0) << "\n";
  }

  for (int i = 0; i < n; ++i) {
    delete treap[i];
  }

  delete[] treap;
}
