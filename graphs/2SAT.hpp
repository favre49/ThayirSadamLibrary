#include "bits/stdc++.h"

using namespace std;

// Source: KACTL
// Tested on: CodeChef SEGDIRS
// n is the number of variables
// if you input x, it means true, if you input ~x, it means false
// either(x,~y) means either x is true or y is false
// setValue() if you want to force something to be true
// solve() returns true if the expression is consistent
// values will store the answer, 1 if true 0 if false
struct TwoSat {
  int n;
  vector<vector<int>> adj;
  vector<int> values;
  vector<int> val, comp, z;
  int time = 0;

  TwoSat(int _n = 0): n(_n), adj(2*_n) {}

  int addVar() {
		adj.emplace_back();
		adj.emplace_back();
		return n++;
	}

  void either(int f, int j) {
    f = max(2*f, -1-2*f);
    j = max(2*j, -1-2*j);
    adj[f].push_back(j^1);
    adj[j].push_back(f^1);
  }
  void setValue(int x) { either(x,x); }

	void atMostOne(const vector<int>& li) {
		if (li.size() <= 1) return;
		int cur = ~li[0];
    for (int i = 2; i < li.size(); i++) {
			int next = addVar();
			either(cur, ~li[i]);
			either(cur, next);
			either(~li[i], next);
			cur = ~next;
		}
		either(cur, ~li[1]);
	}

  int dfs(int i) {
    int low = val[i] = ++time, x;
    z.push_back(i);
    for (int e : adj[i])
      if (!comp[e])
        low = min(low,val[e]?:dfs(e));
    if (low==val[i]) {
      do {
        x = z.back();
        z.pop_back();
        comp[x] = low;
        if (values[x>>1] == -1)
          values[x>>1] = x&1;
      } while(x != i);
    }
    return val[i] = low;
  }

  bool solve() {
    values.assign(n,-1);
    val.assign(2*n,0);
    comp = val;
    for (int i = 0; i < 2*n; i++)
      if (!comp[i])
        dfs(i);
    for (int i = 0; i < n; i++)
      if (comp[2*i] == comp[2*i+1])
        return 0;
    return 1;
  }
};
