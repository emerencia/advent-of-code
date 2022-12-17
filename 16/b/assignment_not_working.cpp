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

struct Node2 {
  int flowrate;
  int maskIndex;
  vector<PII> edges;

  static vector<Node2 *> nodes;
  static map<int, int> lookup; // from maskIndex to position in array

  Node2(int maskIndex, int flowrate, vector<PII> edges) : maskIndex(maskIndex), flowrate(flowrate), edges(edges) {
    lookup[maskIndex] = nodes.size();
    nodes.push_back(this);
  }
};

vector<Node2 *> Node2::nodes;
map<int, int> Node2::lookup;


int mem[26][15][15][2 << 15];

int mem2[26][58][58];

class Assignment {
public:

  int calculateFlow(int mask) {
    int r = 0;
    for (int i = 0; i < Node2::nodes.size(); i++) {
      int maskIndex = Node2::nodes[i]->maskIndex;
      if (maskIndex != -1 && (mask & (1 << maskIndex))) r += Node2::nodes[i]->flowrate;
    }
    return r;
  }

  // minutesLeft = Minutes left after the current step
  int maxFlow(int minutesLeft, int nodeIdx, int elephantNodeIdx, int mask) {
    if (minutesLeft < 0) return 0;
    int &r = mem[minutesLeft][nodeIdx][elephantNodeIdx][mask];
    if (r != -1) return r;
    // calculate the current flow
    r = calculateFlow(mask);
    int s = 0;

    // CALCULATE PERSON ACTIONS

    // if we are on a node that has flowrate and the valve is closed, we can choose to open it
    Node2 *curNode = Node2::nodes[nodeIdx];
    int maskIndex = curNode->maskIndex;
    if (maskIndex != -1 && (!(mask & (1 << maskIndex)))) {
      s = max(s, maxFlow(minutesLeft - 1, nodeIdx, elephantNodeIdx, mask | (1 << maskIndex)));
    }
    // we can instead choose to go in any direction
    for (int i = 0; i < curNode->edges.size(); i++) {
      int weight = curNode->edges[i].second;
      int nextNode = Node2::lookup[curNode->edges[i].first];
      // TODO: should we check if it is < -1 and then not do it? NAH
      s = max(s, maxFlow(minutesLeft - weight, nextNode, elephantNodeIdx, mask));
    }

    // CALCULATE ELEPHANT ACTIONS

    // if we are on a node that has flowrate and the valve is closed, we can choose to open it
    Node2 *curEleNode = Node2::nodes[elephantNodeIdx];
    maskIndex = curEleNode->maskIndex;
    if (maskIndex != -1 && (!(mask & (1 << maskIndex)))) {
      s = max(s, maxFlow(minutesLeft - 1, nodeIdx, elephantNodeIdx, mask | (1 << maskIndex)));
    }
    // we can instead choose to go in any direction
    for (int i = 0; i < curEleNode->edges.size(); i++) {
      int weight = curEleNode->edges[i].second;
      int nextNode = Node2::lookup[curEleNode->edges[i].first];
      // TODO: should we check if it is < -1 and then not do it? NAH
      s = max(s, maxFlow(minutesLeft - weight, nodeIdx, nextNode, mask));
    }

    r += s;
    return r;
  }

  int shortestPath(int timeLeft, int from, int to) {
    if (timeLeft < 0) return INT_MAX/2;
    if (from == to) return 0;
    int &r = mem2[timeLeft][from][to];
    if (r != -1) return r;

    int c = INT_MAX/2;
    Node* curNode = Node::nodes[from];
    for (int i=0;i<curNode->edges.size();i++) {
      int nextNode = Node::lookup[curNode->edges[i]];
      c = min(c, 1 + shortestPath(timeLeft - 1, nextNode, to));
    }
    r = c;
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
    // Create a new graph that collapses all the nodes

    memset(mem2,-1,sizeof(mem2));
    vector<Node2 *> nodes2;
    for (int i=0;i<nodes.size();i++) {
      if (nodes[i]->maskIndex == -1) continue;
      vector<PII> edges2; // outgoing edges from node i. .first is maskindex of dest, .second is weight (minutes)
      for (int j=0;j<nodes.size();j++) {
        if (i == j || nodes[j]->maskIndex == -1) continue;
        // both i and j have flow rate.
        // calculate shortest path from node i to node j IF THERE EVEN IS ONE LOL
        edges2.push_back({nodes[j]->maskIndex,shortestPath(25,i,j)});
      }
      nodes2.push_back(new Node2(nodes[i]->maskIndex, nodes[i]->flowrate, edges2));
    }

    for (int i=0;i<nodes2.size();i++) {
      cout << "Node: " << i << endl;
      cout << "maskIndex: " << nodes2[i]->maskIndex << endl;
      cout << "flowrate: " << nodes2[i]->flowrate << endl;
      cout << "edges: " << endl;
      for (int j=0;j<nodes2[i]->edges.size();j++) {
        cout << "  destination maskIndex: " << nodes2[i]->edges[j].first << ", weight: " << nodes2[i]->edges[j].second << endl;
      }
      cout << endl << endl;
    }

    int r = 0;
    int startNode = Node::lookup["AA"];
    for (int i = 0; i < nodes.size(); i++) {
      if (nodes[i]->maskIndex == -1) continue;
      int startNodePersonIdx = Node2::lookup[Node::nodes[i]->maskIndex];
      for (int j = 0; j < nodes.size(); j++) {
        if (nodes[j]->maskIndex == -1) continue;
        int startElephantIdx = Node2::lookup[Node::nodes[j]->maskIndex];
        // person starts from i, elephant from j
        // take
        int shortestPathPerson = shortestPath(25, startNode, i);
        int shortestPathElephant = shortestPath(25, startNode, j);
        int minutesLeft = 25 - max(shortestPathPerson, shortestPathElephant);
        if (shortestPathPerson > shortestPathElephant) {
          r = max(r, maxFlow(minutesLeft, startNodePersonIdx, startElephantIdx, (1 << startElephantIdx)));
        } else if (shortestPathElephant > shortestPathPerson) {
          r = max(r, maxFlow(minutesLeft, startNodePersonIdx, startElephantIdx, (1 << startNodePersonIdx)));
        } else {
          r = max(r, maxFlow(minutesLeft, startNodePersonIdx, startElephantIdx, 0));
        }
      }
    }

    //cout << "mask index: " << Node::nodes[Node::lookup["AA"]]->maskIndex << endl;
    //int startNodeIdx = Node2::lookup[Node::nodes[Node::lookup["AA"]]->maskIndex];
    //cout << "start node: " << startNodeIdx << endl;
    return r;
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
