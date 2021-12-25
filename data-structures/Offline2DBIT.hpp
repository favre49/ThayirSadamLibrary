#include <bits/stdc++.h>
using namespace std;

// Source: bqi343
// Tested on: https://atcoder.jp/contests/abc233/tasks/abc233_h
// Point update and rectangle sum with offline 2D BIT
// x \in (0,n), y != 0
// Works in O(n \log2(N)) build and uses O(n \log n) memory
// Use insert to load offline points, update and query work as named
template <typename T>
struct Offline2DBIT {
  public:
    Offline2DBIT(int n) : n(n), mode(0), cnt(n), st(n) {}

    void insert(int x, int y) { 
      assert(!mode);
      offline.push_back({x,y}); 
    }

    void build() {
      assert(!mode);
      mode = 1;
      vector<int> lst(n);
      sort(offline.begin(), offline.end(), [](const pair<int,int>& a, const pair<int,int>& b){
        return a.second < b.second;
      });
      for (auto& [px, py] : offline) {
        for (int x = px; x < n; x += x&-x) {
          if (lst[x] != py) {
            lst[x] = py;
            cnt[x]++;
          }
        }
      }
      int sum = 0;
      for (int i = 0; i < n; i++) {
        lst[i] = 0;
        sum += cnt[i];
        st[i] = sum;
      }
      val.resize(sum); bit.resize(sum);
      reverse(offline.begin(),offline.end());
      for (auto& [px,py] : offline) {
        for (int x = px; x < n; x += x&-x) {
          if (lst[x] != py) {
            lst[x] = py;
            val[--st[x]] = py;
          }
        }
      }
    }

    void update(int x, int y, T t) {
      assert(mode);
      for (; x < n; x += (x&-x))
        row_update(x,y,t);
    }

    T query(int x, int y) {
      assert(mode);
      T res = 0;
      for (; x; x -= x&-x)
        res += row_query(x,y);
      return res;
    }

    T query(int lx, int rx, int ly, int ry) {
      return query(rx,ry) - query(lx-1,ry) - query(rx,ly-1) + query(lx-1,ly-1);
    }

  private:
    size_t n;
    size_t mode;
    vector<pair<int,int>> offline;
    vector<T> bit;
    vector<int> val, cnt, st;

    int rank(int y, int l, int r) {
      return upper_bound(val.begin()+l, val.begin()+r, y) - val.begin() - l;
    }

    void row_update(int x, int y, T t) {
      for (y = rank(y,st[x],st[x]+cnt[x]); y <= cnt[x]; y += y&-y)
        bit[st[x]+y-1] += t;
    }

    int row_query(int x, int y) {
      T res = 0;
      for (y = rank(y,st[x],st[x]+cnt[x]); y ; y -= y&-y)
        res += bit[st[x]+y-1];
      return res;
    }
};

// Source: bqi343
// Tested on: https://atcoder.jp/contests/abc233/tasks/abc233_h
// Point update and rectangle sum with offline 2D BIT
// x \in (0,n), y != 0
// Works in O(n \log2(N)) build and uses O(n \log n) memory
// Use insert to load offline points, update and query work as named
template <typename T>
struct Offline2DBIT {
  public:
    Offline2DBIT(int n) : n(n), mode(0), cnt(n), st(n) {}

    void insert(int x, int y) { 
      assert(!mode);
      offline.push_back({x,y}); 
    }

    void build() {
      assert(!mode);
      mode = 1;
      vector<int> lst(n);
      sort(offline.begin(), offline.end(), [](const pair<int,int>& a, const pair<int,int>& b){
        return a.second < b.second;
      });
      for (auto& [px, py] : offline) {
        for (int x = px; x < n; x += x&-x) {
          if (lst[x] != py) {
            lst[x] = py;
            cnt[x]++;
          }
        }
      }
      int sum = 0;
      for (int i = 0; i < n; i++) {
        lst[i] = 0;
        sum += cnt[i];
        st[i] = sum;
      }
      val.resize(sum); bit.resize(sum);
      reverse(offline.begin(),offline.end());
      for (auto& [px,py] : offline) {
        for (int x = px; x < n; x += x&-x) {
          if (lst[x] != py) {
            lst[x] = py;
            val[--st[x]] = py;
          }
        }
      }
    }

    void update(int x, int y, T t) {
      assert(mode);
      for (; x < n; x += (x&-x))
        row_update(x,y,t);
    }

    T query(int x, int y) {
      assert(mode);
      T res = 0;
      for (; x; x -= x&-x)
        res += row_query(x,y);
      return res;
    }

    T query(int lx, int rx, int ly, int ry) {
      return query(rx,ry) - query(lx-1,ry) - query(rx,ly-1) + query(lx-1,ly-1);
    }

  private:
    size_t n;
    size_t mode;
    vector<pair<int,int>> offline;
    vector<T> bit;
    vector<int> val, cnt, st;

    int rank(int y, int l, int r) {
      return upper_bound(val.begin()+l, val.begin()+r, y) - val.begin() - l;
    }

    void row_update(int x, int y, T t) {
      for (y = rank(y,st[x],st[x]+cnt[x]); y <= cnt[x]; y += y&-y)
        bit[st[x]+y-1] += t;
    }

    int row_query(int x, int y) {
      T res = 0;
      for (y = rank(y,st[x],st[x]+cnt[x]); y ; y -= y&-y)
        res += bit[st[x]+y-1];
      return res;
    }
};


