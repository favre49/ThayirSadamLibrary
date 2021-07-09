#include <bits/stdc++.h>
using namespace std;

// Source: ???
// Tested on: 
// Find the lexicographically minimal rotation in O(n)
// rotate(v.begin(),v.begin()+val,v.end());
// type needs to implement a < compare
template<typename T>
int least_rotation(vector<T> v) {
  int n = v.size();
  for (int i = 0; i < n; i++)
    v.push_back(v[i]);
  int len = v.size(), i = 0, j = 1, k = 0;
  while(i+k < len && j+k < len) {
    if (v[i+k] == v[j+k]) k++;
    else if (v[j+k] < v[i+k]) i = i+k+1, k = 0;
    else j = j+k+1, k=0;
    if (i==j) j++;
  }
  return min(i,j);
}
