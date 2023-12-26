#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <utility>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <cmath>
#include <utility>
#include <climits>
#include <limits>
#include <cstring>
#include <numeric>
#include <cstdio>

using namespace std;
typedef long long LL;
typedef pair<int, int> PII;
typedef pair<string, string> PSS;

class Assignment {
public:
  // Can optimize this data structure later.
  set<string> nodes;
  map<string, vector<string>> edges;

  void shortestPath(const string &start, const string &end, map<PSS, int> &edgeUsage) {
    queue<string> q;
    q.push(start);
    map<string, int> dist;
    dist[start] = 0;
    while (!q.empty()) {
      string node = q.front();
      q.pop();
      for (auto &otherNode: edges[node]) {
        if (dist.find(otherNode) == dist.end()) {
          dist[otherNode] = dist[node] + 1;
          q.push(otherNode);
        }
      }
    }
    // Mark the edges in the shortest path as used.
    string node = end;
    while (node != start) {
      string prevNode;
      for (auto &otherNode: edges[node]) {
        if (dist.find(otherNode) != dist.end() && dist[otherNode] == dist[node] - 1) {
          prevNode = otherNode;
          break;
        }
      }
      if (node == prevNode) {
        cout << "Error: no prev node found for " << node << endl;
        exit(1);
      }
      // To make sure we don't count edges twice, we always store the edges in the same order.
      if (node < prevNode) {
        edgeUsage[PSS(node, prevNode)]++;
      } else {
        edgeUsage[PSS(prevNode, node)]++;
      }
      node = prevNode;
    }
    // return dist[end];
  }

  void removeEdge(const string &node1, const string &node2) {
    auto it = find(edges[node1].begin(), edges[node1].end(), node2);
    if (it == edges[node1].end()) {
      cout << "Error: edge not found: " << node1 << " " << node2 << endl;
      exit(1);
    }
    edges[node1].erase(it);
    it = find(edges[node2].begin(), edges[node2].end(), node1);
    if (it == edges[node2].end()) {
      cout << "Error: return edge not found: " << node2 << " " << node1 << endl;
      exit(1);
    }
    edges[node2].erase(it);
  }

  void removeThreeHighestEdges() {
    // Naive idea: go over all pairs of nodes and find the shortest paths between all of them.
    // Mark the edges in the shortest paths as used.
    // The three edges that are most used have to be the ones that we want to remove to
    // split the graph into two groups.
    // Since a lot of the nodes are similarly connected, we can skip a lot of the pairs
    // without influencing the result. This was the only optimization needed.
    // The current solution runs in 0.62 seconds on my machine.
    map<PSS, int> edgeUsage;
    vector<string> nodes_vec(nodes.begin(), nodes.end());
    int totalLoops = (int) nodes_vec.size() * ((int) nodes_vec.size() - 1) / 2;
    int skip = nodes_vec.size() > 500 ? 50 : 1; // Only consider 1 in every skip pairs.
    int lastPercentage = 0;
    for (int i = 0; i < nodes_vec.size(); i += skip) {
      for (int j = i + 1; j < nodes_vec.size(); j += skip) {
        // print something at every 10% ish
        int percentage = (((i * ((int) nodes_vec.size() - 1) + j) / 2)) * 100 / totalLoops;
        if (percentage / 10 > lastPercentage / 10) {
          cout << "progress: " << percentage << "%" << endl;
          lastPercentage = percentage;
        }
        shortestPath(nodes_vec[i], nodes_vec[j], edgeUsage);
      }
    }
    // find the three most used edges
    int max1 = 0, max2 = 0, max3 = 0;
    PSS max1_edge, max2_edge, max3_edge;
    for (auto &kv: edgeUsage) {
      if (kv.second > max1) {
        max3 = max2;
        max3_edge = max2_edge;
        max2 = max1;
        max2_edge = max1_edge;
        max1 = kv.second;
        max1_edge = kv.first;
      } else if (kv.second > max2) {
        max3 = max2;
        max3_edge = max2_edge;
        max2 = kv.second;
        max2_edge = kv.first;
      } else if (kv.second > max3) {
        max3 = kv.second;
        max3_edge = kv.first;
      }
    }
    cout << "max1: " << max1 << " " << max1_edge.first << " " << max1_edge.second << endl;
    cout << "max2: " << max2 << " " << max2_edge.first << " " << max2_edge.second << endl;
    cout << "max3: " << max3 << " " << max3_edge.first << " " << max3_edge.second << endl;
    // Remove the three edges from the graph.
    removeEdge(max1_edge.first, max1_edge.second);
    removeEdge(max2_edge.first, max2_edge.second);
    removeEdge(max3_edge.first, max3_edge.second);
  }

  int productOfGraphComponentSizes() {
    vector<string> nodes_vec(nodes.begin(), nodes.end());
    vector<int> color(nodes_vec.size(), 0);
    int colors = 0;
    for (int i = 0; i < nodes_vec.size(); i++) {
      if (color[i]) continue;
      queue<string> q;
      q.push(nodes_vec[i]);
      color[i] = ++colors;
      while (!q.empty()) {
        string node = q.front();
        q.pop();
        for (auto &otherNode: edges[node]) {
          auto it = find(nodes_vec.begin(), nodes_vec.end(), otherNode);
          if (it == nodes_vec.end()) {
            cout << "Error: node not found: " << otherNode << endl;
            exit(1);
          }
          int index = (int) (it - nodes_vec.begin());
          if (!color[index]) {
            color[index] = colors;
            q.push(otherNode);
          }
        }
      }
    }
    cout << "colors: " << colors << endl;
    vector<int> componentSizes(colors, 0);
    for (int i = 0; i < nodes_vec.size(); i++) {
      componentSizes[color[i] - 1]++;
    }
    cout << "component sizes: ";
    for (auto &s: componentSizes) {
      cout << s << " ";
    }
    cout << endl;
    int product = 1;
    for (auto &s: componentSizes) {
      product *= s;
    }
    return product;
  }

  int solution() {
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      // read until the first :
      string node = line.substr(0, line.find(':'));
      nodes.insert(node);
      string edges_str = line.substr(line.find(':') + 2);
      stringstream ss(edges_str);
      string otherNode;
      while (ss >> otherNode) {
        if (nodes.find(otherNode) == nodes.end()) {
          nodes.insert(otherNode);
        }
        // cout << "[" << node << "]-[" << otherNode << "]" << endl;
        edges[node].push_back(otherNode);
        edges[otherNode].push_back(node);
      }
    }
    removeThreeHighestEdges();
    return productOfGraphComponentSizes();
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
  /* outputs something like:
     max1: 13695 bbp dvr
     max2: 9733 jzv qvq
     max3: 7287 gtj tzj
     colors: 2
     component sizes: 707 701
     495607
  */
}
