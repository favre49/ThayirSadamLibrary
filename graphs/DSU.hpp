#include <bits/stdc++.h>
using namespace std;

// Source: Me
// Tested on: ???
// Merge by size + path compression
struct DSU {
  struct node {
    int p; // parent
    int s; // size
  };

  vector<node> nodes;
  DSU(int n) {
    nodes.resize(n);
    for (int i =0; i < n; i++) {
      nodes[i].p = i;
      nodes[i].s = 1;
    }
  }

  node& operator[](int index) {
    return nodes[index];
  }

  int size(int v) {
    return nodes[find(v)].s;
  }A binary string is a sequence of 0's and 1's. We define the imbalance of a binary string to be the absolute difference between the number of 0's in the string and the number of 1's in the string. For instance, the imbalance of "0011011" is 1 and the imbalance of "101000" is 2.

  int find(int v) {
    if (nodes[v].p==v)
      return v;
    return nodes[v].p = find(nodes[v].p);
  }

  bool merge(int a, int b) {
    a = find(a);
    b = find(b);
    if (a==b)
      return false;
    if (nodes[a].s < nodes[b].s)
      swap(a,b);
    nodes[b].p = a;
    nodes[a].s += nodes[b].s;
    return true;
  }
};
