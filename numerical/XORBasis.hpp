#include <bits/stdc++.h>
using namespace std;

// Source: Me
// Tested On:
// finds the xor basis of the given space
// O(nd)
vector<int> xorbasis(vector<int>& space) {
  vector<int> base, elim;
  for (int x : space) {
    int y = x;
    for (int b : elim)
      y = min(y,y^b);
    if (y) {
      base.push_back(x);
      elim.push_back(y);
    }
  }
  return base;
}
