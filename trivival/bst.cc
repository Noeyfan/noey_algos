#include <memory>
#include <iostream>
#include <vector>
using namespace std;

struct Node {
  unique_ptr<Node> l, r;
  int data;

  Node(int i)
  : l(nullptr), r(nullptr), data(i) { }
};

class Bst {
  using node_ptr = unique_ptr<Node>;
  node_ptr root;

public:
  Bst()
  : root(nullptr) { }

  void insert(int val)
  { insert(root, val); }

  void erase(int val)
  { root = std::move(erase(root, val)); }

  void print()
  { print(root.get()); }

private:
  int find_min(Node* p) {
    while(p && p->l) {
      p = p->l.get();
    }
    return p->data;
  }

  void insert(node_ptr& root, int val) {
    if(!root) root = std::move(node_ptr(new Node(val)));
    if(root->data < val) insert(root->r, val);
    else if(root->data > val) insert(root->l, val);
  }

  node_ptr& erase(node_ptr& root, int val) {
    if(root->data < val) {
      root->r = std::move(erase(root->r, val));
    }
    else if(root->data > val) {
      root->l = std::move(erase(root->l, val));
    }
    else {
      if(root->l && root->r) {
	root->data = find_min(root->r.get());
	root->r = std::move(erase(root->r, root->data));
      }
      else if(root->l || root->r) {
	return root->l ? root->l : root->r;
      }
      else {
	root.reset(nullptr);
      }
    }
    return root;
  }

  void print(Node* p) {
    if(!p) return;
    print(p->l.get());
    cout << p->data << " ";
    print(p->r.get());
  }
};

int main() {
  Bst b;
  vector<int> inputs = {5, 3, 7, 2, 4, 6, 8};

  for (const auto& ele : inputs) {
    b.insert(ele);
  }

  for (int i = 0; i < (int)inputs.size(); ++i) {
    if (i % 2) b.erase(inputs[i]);
  }

  b.print();
}
