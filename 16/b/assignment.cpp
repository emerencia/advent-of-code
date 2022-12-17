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

int mem[30][58][1 << 16][2];

class Assignment {
public:

  // minutesLeft = Minutes left after the current step
  int maxFlow(int minutesLeft, int nodeIdx, int mask, int player) {
    if (minutesLeft < 0) {
      if (player) return maxFlow(25, Node::lookup["AA"], mask, 0);
      return 0;
    }
    int &r = mem[minutesLeft][nodeIdx][mask][player];
    if (r != -1) return r;
    int s = 0;
    // if we are on a node that has flowrate and the valve is closed, we can choose to open it
    Node *curNode = Node::nodes[nodeIdx];
    int maskIndex = curNode->maskIndex;
    if (maskIndex != -1 && (!(mask & (1 << maskIndex)))) {
      s = max(s, (minutesLeft * (curNode->flowrate)) +
                 maxFlow(minutesLeft - 1, nodeIdx, mask | (1 << maskIndex), player));
    }
    // we can instead choose to go in any direction
    for (int i = 0; i < curNode->edges.size(); i++) {
      int nextNode = Node::lookup[curNode->edges[i]];
      s = max(s, maxFlow(minutesLeft - 1, nextNode, mask, player));
    }
    r = s;
    return r;
  }

  int solution() {
    memset(mem, -1, sizeof(mem));
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
      new Node(valveName, flowrate, edges);
    }
    return maxFlow(25, Node::lookup["AA"], 0, 1);
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
