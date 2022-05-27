#include <bits/stdc++.h>
using namespace std;

// Source: neal
// Tested on:
// Works in O(mk) time, where m is total string size and k is the size of the
// alphabet Given a set of pattern strings P and a text T, can find all matches
// of P in T To use AC automaton, the following steps for a given character:
// 1. If there is no edge, follow suffix link. If you are at root, stop
// 2. If there is an edge, take it
// 3. If this is a terminal state, output that pattern
// 4. Output all words in the chain of output links from this node.
struct Aho {
  static const int ALPHABET = 26;

  struct Node {
    // suff points to the node of the longest strict suffix of the node in the
    // tree (suffix link)
    // dict points to the node of the longest strict suffix of the node in the
    // dictionary (output link). If we reach any node, we need to output every
    // word reachable by output links.
    // depth is the depth in the trie
    // word_index is the index of the first word ending at this node. -1 if
    // none.
    // word_count is the total number of words ending at this node
    // link = the trie connections and/or suffix connections
    int suff = -1, dict = -1, depth = 0;
    int word_index = -1;
    int word_count = 0;
    int link[ALPHABET];

    Node() { fill(link, link + ALPHABET, -1); }

    int& operator[](char c) { return link[c - 'a']; }
  };

  vector<Node> nodes;
  int W;                              // size of dictionary
  vector<int> word_location;          // The ending node of the word
  vector<int> word_indices_by_depth;  // List of word indices in decreasing
                                      // order of depth
  vector<int> defer;  // Stores the index of the word which ends at the same
                      // position as this.

  Aho(const vector<string>& words = {}) {
    if (!words.empty()) build(words);
  }

  // Builds adjacency list based on suffix parents
  vector<vector<int>> build_suffix_adj() const {
    vector<vector<int>> adj(nodes.size());
    for (int i = 1; i < (int)nodes.size(); i++) adj[nodes[i].suff].push_back(i);
    return adj;
  }

  int get_or_add_child(int current, char c) {
    if (nodes[current][c] >= 0)  // exists
      return nodes[current][c];
    int index = nodes.size();
    nodes[current][c] = index;
    nodes.emplace_back();
    nodes.back().depth = nodes[current].depth + 1;
    return index;
  }

  int add_word(const string& word, int word_index) {
    assert(!nodes.empty());
    int curr = 0;
    for (char c : word) curr = get_or_add_child(curr, c);
    if (nodes[curr].word_index < 0) nodes[curr].word_index = word_index;
    nodes[curr].word_count++;
    return curr;
  }

  // Transition from location with c (Rename?)
  int get_suffix_link(int location, char c) const {
    if (location >= 0) location = nodes[location].link[c - 'a'];
    return max(location, 0);
  }

  void build(const vector<string>& words) {
    nodes = {Node()};
    W = words.size();
    word_location.resize(W);
    defer.resize(W);
    int max_depth = 0;
    for (int i = 0; i < W; i++) {
      word_location[i] = add_word(words[i], i);
      max_depth = max(max_depth, int(words[i].size()));
      defer[i] = nodes[word_location[i]].word_index;
    }
    // Create list of word indexes in decreasing order of depth, by counting
    // sort
    word_indices_by_depth.resize(W);
    vector<int> depth_freq(max_depth + 1, 0);
    for (int i = 0; i < W; i++) depth_freq[words[i].size()]++;
    for (int i = max_depth - 1; i >= 0; i--) depth_freq[i] += depth_freq[i + 1];
    for (int i = 0; i < W; i++)
      word_indices_by_depth[--depth_freq[words[i].size()]] = i;

    // Solve suffix parents by traversing in the order of depth (BFS order)
    vector<int> q = {0};
    for (int i = 0; i < (int)q.size(); i++) {
      int curr = q[i];
      for (char c = 'a'; c < 'a' + ALPHABET; c++) {
        int& index = nodes[curr][c];
        if (index >= 0) {
          // Find index's suffix parent by traversing suffix parents of curr
          // until one has a child c
          int suffix_parent = get_suffix_link(nodes[curr].suff, c);
          nodes[index].suff = suffix_parent;
          nodes[index].word_count += nodes[suffix_parent].word_count;
          nodes[index].dict = nodes[suffix_parent].word_index < 0
                                  ? nodes[suffix_parent].dict
                                  : suffix_parent;
          q.push_back(index);
        } else
          index = get_suffix_link(nodes[curr].suff, c);
      }
    }
  }

  // Counts the number of matches of each word in O(text length + num words).
  vector<int> count_matches(const string& text) const {
    vector<int> matches(W, 0);
    int curr = 0;
    for (char c : text) {
      curr = get_suffix_link(curr, c);
      int dict_node = nodes[curr].word_index < 0 ? nodes[curr].dict : curr;
      if (dict_node >= 0) matches[nodes[dict_node].word_index]++;
    }
    for (int word_index : word_indices_by_depth) {
      int location = word_location[word_index];
      int dict_node = nodes[location].dict;
      if (dict_node >= 0)
        matches[nodes[dict_node].word_index] += matches[word_index];
    }
    for (int i = 0; i < W; i++) matches[i] = matches[defer[i]];
    return matches;
  }

  vector<int> count_matches_by_position(const string& text) const {
    vector<int> matches(text.size());
    int curr = 0;
    for (int i = 0; i < text.size(); i++) {
      curr = get_suffix_link(curr, text[i]);
      matches[i] = nodes[curr].word_count;
    }
    return matches;
  }

  int64_t count_total_matches(const string& text) const {
    int64_t matches = 0;
    int curr = 0;
    for (char c : text) {
      curr = get_suffix_link(curr, c);
      matches += nodes[curr].word_count;
    }
    return matches;
  }
};
