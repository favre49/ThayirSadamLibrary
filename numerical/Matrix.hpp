#include <bits/stdc++.h>
using namespace std;

// Source: Me
// Tested On:
// Matrix library
// Use M^k to raise to a power
template<class T>
struct Mat{
  int n,m;
  vector<vector<T>> d;

  Mat(): n(0), m(0){}

  Mat(int _n, int _m): n(_n), m(_m) {
    d = vector<vector<T>>(n,vector<T>(m));
  }

  Mat(const vector<vector<T>>& v): Mat((int)v.size(),(int)v[0].size()){
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        d[i][j] = v[i][j];
  }

  vector<T>& operator[] (int index) {
    return d[index];
  }

  Mat operator +(Mat other) const {
    assert(n == other.n && m == other.m);
    Mat res = Mat(n,m);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        res.d[i][j] = d[i][j] + other.d[i][j];
    return res;
  }

  Mat operator -(Mat other) const {
    assert(n == other.n && m == other.m);
    Mat res = Mat(n,m);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        res.d[i][j] = d[i][j] - other.d[i][j];
    return res;
  }

  Mat operator *(Mat other) const {
    assert(m == other.n);
    Mat prod = Mat(n,other.m);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        for (int k = 0; k < other.m; k++)
          prod.d[i][k] += d[i][j] * other.d[j][k];
    return prod;
  }

  Mat operator ^(long long p)
  {
    assert(p >= 0);
    Mat res(n,n), base(*this);
    for (int i = 0; i < n; i++)
      res.d[i][i] = 1;
    for (;p; p /= 2) {
      if (p&1) res = res*base;
      base = base*base;
    }
    return res;
  }

  // Get the determinant of the matrix in O(N^3)
  T det() {
    assert(n == m);
    T prod = 1;
    Mat st(n,n);
    st.d = d;
    auto elim = [this](int a, int c){
      T x = d[c][a];
      for (int i = a; i < n; i++)
        d[c][i] -= x*d[a][i];
    };
    for (int i = 0; i < n; i++){
      bool done = false;
      for (int j = i; j < n; j++){
        if (d[j][i] != 0) {
          done = 1;
          if (j != i)
            swap(d[j], d[i]);
          if ((j-i)%2==1)
            prod *= -1;
          prod = prod*d[i][i];
          T x = d[i][i].inv();
          for (int k = i; k < n; k++)
            d[i][k] *= x;
          for (int k = i+1; k < n; k++)
            elim(i,k);
        }
      }
      if (!done) return 0;
    }
    d = st.d;
    return prod;
  }
};
