#include <bits/stdc++.h>
using namespace std;

// Source: Me
// Tested on: CF 1575 H
namespace KMP {
  char MIN_CHAR = 'a';
  int ALPHABET = 26;

  // Finds longest prefix of [0..i] such that it is also a suffix of [0..i]
  vector<int> prefix_function(string s) {
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

  // KMP match finding algorithm
  vector<int> find_matches(const string& s, const string& pat) {
    vector<int> p = prefix_function(pat+'\0'+s), res;
    for (int i = (int)p.size() - (int)s.size(); i < p.size(); i++)
      if (p[i] == pat.size())
        res.push_back(i - 2*pat.size());
    return res;
  }

  // Builds KMP automaton aut
  // aut[p][c] = transition from pi when adding character c
  // TODO: Determine whether I should pass aut by reference or it's ok to return
  // Seems to incur tiny penalty, but unclear
  vector<vector<int>> build_automaton(string s) {
    s += '\0';
    int n = s.size();
    vector<int> pi = prefix_function(s);
    vector<vector<int>> aut(n, vector<int>(ALPHABET));
    for (int i = 0; i < n; i++) {
      for (int c = 0; c < ALPHABET; c++) {
        if (i > 0 && MIN_CHAR + c != s[i])
          aut[i][c] = aut[pi[i-1]][c];
        else
          aut[i][c] = i + (MIN_CHAR + c == s[i]);
      }
    }
    return aut;
  }
};
