#include <bits/stdc++.h>
using namespace std;

// Source: Me(?)
// Tested on:
// Root is state 0, -1 if there is no transition on a character
template<char START = 'a', int ALPHABET=26>
struct SuffixAutomaton {
  struct State {
    int len;
    int link;
    int next[ALPHABET];

    State() {
      memset(next,-1,sizeof(next));
    }
  };

  vector<State> states;
  int last;
  string s;

  SuffixAutomaton() {
    init();
  }

  SuffixAutomaton(string _s):s(_s) {
    init();
    for (char c : s)
      extend(c);
  }
  
  void init() {
    states.push_back(State());
    last = states[0].len = 0;
    states[0].link = -1;
  }

  void extend(char c) {
    assert(c >= START && c < START+ALPHABET);
    int k = states.size(),p;
    states.push_back(State());
    int idx = c-START;
    states[k].len = states[last].len+1;
    for (p = last; p != -1 && states[p].next[idx] < 0; p = states[p].link)
      states[p].next[idx]=k;
    if (p==-1)
      states[k].link = 0;
    else
    {
      int q = states[p].next[idx];
      if (states[p].len+1==states[q].len) {
        states[k].link = q;
      }
      else
      {
        int w = states.size();;
        states.push_back(State());
        states[w].len = states[p].len+1;
        for (int i =0; i < ALPHABET; i++) 
          states[w].next[i] = states[q].next[i];
        states[w].link = states[q].link;
        for (;p!=-1 && states[p].next[idx] == q; p = states[p].link)states[p].next[idx] = w;
        states[q].link = states[k].link = w;
      }
    }
    last = k;
  }
};
