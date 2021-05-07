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

// find pat in s
vector<int> kmp(const string& s, const string& pat) {
  vector<int> p = prefix_func(pat+'\0'+s), res;
  for (int i = (int)p.size() - (int)s.size(); i < p.size(); i++)
    if (p[i] == pat.size())
      res.push_back(i - 2*pat.size());
  return res;
}
