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

struct Node {
  int flowrate;
  int maskIndex;
  vector<string> edges;

  static vector<Node *> nodes;
  static map<string, int> lookup;
  static int count;

  Node(string valveName, int flowrate, vector<string> edges) : flowrate(flowrate), edges(edges) {
    if (flowrate == 0) {
      maskIndex = -1;
    } else {
      maskIndex = count++;
    }
    lookup[valveName] = nodes.size();
    nodes.push_back(this);
  }
};

vector<Node *> Node::nodes;
map<string, int> Node::lookup;
int Node::count = 0;

int mem[30][58][1 << 16];

class Assignment {
public:

  int calculateFlow(int mask) {
    int r = 0;
    for (int i = 0; i < Node::nodes.size(); i++) {
      int maskIndex = Node::nodes[i]->maskIndex;
      if (maskIndex != -1 && (mask & (1 << maskIndex))) r += Node::nodes[i]->flowrate;
    }
    return r;
  }

  // minutesLeft = Minutes left after the current step
  int maxFlow(int minutesLeft, int nodeIdx, int mask) {
    if (minutesLeft < 0) return 0;
    int &r = mem[minutesLeft][nodeIdx][mask];
    if (r != -1) return r;
    // calculate the current flow
    r = calculateFlow(mask);
    int s = 0;
    // if we are on a node that has flowrate and the valve is closed, we can choose to open it
    Node *curNode = Node::nodes[nodeIdx];
    int maskIndex = curNode->maskIndex;
    if (maskIndex != -1 && (!(mask & (1 << maskIndex)))) {
      s = max(s, maxFlow(minutesLeft - 1, nodeIdx, mask | (1 << maskIndex)));
    }
    // we can instead choose to go in any direction
    for (int i = 0; i < curNode->edges.size(); i++) {
      int nextNode = Node::lookup[curNode->edges[i]];
      s = max(s, maxFlow(minutesLeft - 1, nextNode, mask));
    }
    r += s;
    return r;
  }

  int solution() {
    memset(mem, -1, sizeof(mem));
    vector<Node *> nodes;
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      string valveName = line.substr(6, 2);
      int flowrate;
      char buf[100];
      sscanf(line.c_str(), "Valve %s has flow rate=%d; tunnel", buf, &flowrate);
      int edgePos = line.find("valves");
      if (edgePos == string::npos) edgePos = line.find("valve") - 1;
      string edgesStr = line.substr(edgePos + 7);
      stringstream s(edgesStr);
      string edgeName;
      vector<string> edges;
      while (getline(s, edgeName, ',')) {
        edges.push_back(edgeName);
        if (s.peek() == ' ') s.ignore();
      }
      nodes.push_back(new Node(valveName, flowrate, edges));
    }
    return maxFlow(29, Node::lookup["AA"], 0);
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
