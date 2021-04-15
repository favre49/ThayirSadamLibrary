#include <bits/stdc++.h>
using namespace std;

// Finds longest prefix of [0..i] such that it is also a suffix of [0..i]
vector<int> prefix_func(string s)
{
  int n = (int)s.length();
  vector<int> pi(n);
  for (int i = 1; i < n; i++)
  {
    int j = pi[i-1];
    while (j > 0 && s[i] != s[j])
      j = pi[j-1];
    if (s[i] == s[j])
      j++;
    pi[i] = j;
  }
  return pi;
}
