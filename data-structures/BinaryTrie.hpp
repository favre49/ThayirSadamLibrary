#include <bits/stdc++.h>

using namespace std;

// Source: Me
// Tested on: Yosupo Set Xor-Min
// Binary Trie
template<int L = 24>
struct BinaryTrie {
  struct Node {
    int cnt,dep;
    int c[2];
    Node() {
      cnt = dep = 0;
      c[0] = c[1] = -1;
    }
  };
  int root = 0, sz =0;
  vector<Node> nodes{Node()};
  BinaryTrie(){}
  int create_node() {
    nodes.push_back(Node());
    return ++sz;
  }
  void insert(int x, int amt=1) {
    int v = root;
    for (int i = L; i >= 0; i--)  {
      nodes[v].cnt += amt;
      int b = (x>>i)&1;
      if (nodes[v].c[b] == -1) {
        nodes[v].c[b] = create_node();
        nodes[nodes[v].c[b]].dep = nodes[v].dep+1;
      }
      v = nodes[v].c[b];
    }
    nodes[v].cnt += amt;
  }
  // Assumes element exists
  void remove(int x, int amt = 1) {
    int v = root;
    for (int i = L; i >= 0; i--) {
      nodes[v].cnt -= amt;
      v = nodes[v].c[(x>>i)&1];
    }
    nodes[v].cnt -= amt;
  }
  int minxor(int x) {
    int ans = 0;
    int v = root;
    for (int i = L; i >= 0; i--) {
      int b = (x>>i)&1;
      if (nodes[v].c[b] != -1 && nodes[nodes[v].c[b]].cnt)
        v = nodes[v].c[b];
      else {
        ans |= 1<<i;
        v = nodes[v].c[b^1];
      }
    }
    return ans;
  }
};

