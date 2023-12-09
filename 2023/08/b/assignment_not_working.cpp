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

// currentNodeName, directionsIdx
typedef pair<string, int> State;

struct Node {
  string name;
  string left;
  string right;

  static map<string, Node *> nodes;

  Node(string name, string l, string r) : name(name), left(l), right(r) {
    // cout << "name: " << name << " left: " << left << " right: " << right << endl;
    nodes[name] = this;
  }

  static vector<string> startingNodes() {
    // return all nodes that end in A
    vector<string> r;
    for (auto const &it : nodes) {
      if (it.first[2] == 'A') r.push_back(it.first);
    }
    return r;
  }
};


map<string, Node *> Node::nodes;
map<State, set<int>> mem;


class Assignment {
  string directions;

public:
  // max depth shouldn't be needed.
  set<int> rec(string currentNode, int directionsIdx) {
    // cout << "currentNode: " << currentNode << " directionsIdx: " << directionsIdx << endl << flush;
    State state = make_pair(currentNode, directionsIdx);
    if (mem.count(state)) {
      // cout << "yep" << endl << flush;
      return mem[state];
    }

    mem[state] = {};

    set<int> r;
    // if current node ends in Z
    if (currentNode[2] == 'Z') {
      r.insert(0);
      // but we keep going
    }

    set<int> tempSet;
    if (directions[directionsIdx] == 'L') {
      tempSet = rec(Node::nodes[currentNode]->left, (directionsIdx + 1) % directions.size());
    } else {
      tempSet = rec(Node::nodes[currentNode]->right, (directionsIdx + 1) % directions.size());
    }
    for (const auto &it : tempSet) {
      r.insert(it + 1);
    }
    return mem[state] = r;
  }

  set<int> rec2(string currentNode, int directionsIdx, int stepsleft) {
    // if (stepsleft < 0) return {};
    // cout << "currentNode: " << currentNode << " directionsIdx: " << directionsIdx << endl << flush;
    State state = make_pair(currentNode, directionsIdx);
    if (mem.count(state)) {
      // cout << "yep" << endl << flush;
      return mem[state];
    }

    if (stepsleft < 0) {
      mem[state] = {};
    }

    set<int> r;
    // if current node ends in Z
    if (currentNode[2] == 'Z') {
      r.insert(0);
      // but we keep going
    }

    set<int> tempSet;
    if (directions[directionsIdx] == 'L') {
      tempSet = rec2(Node::nodes[currentNode]->left, (directionsIdx + 1) % directions.size(), stepsleft - 1);
    } else {
      tempSet = rec2(Node::nodes[currentNode]->right, (directionsIdx + 1) % directions.size(), stepsleft - 1);
    }
    for (const auto &it: tempSet) {
      r.insert(it + 1);
    }
    return mem[state] = r;
  }

  int solution() {
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      if (directions.empty()) {
        directions = line;
      } else {
        // read the input
        // the format is like this:
        // BVP = (QKT, GHR)
        char nname[4], lleft[4], rright[4];
        string name, left, right;
        // scanf should ignore the , and the ()
        sscanf(line.c_str(), "%s = (%[^,], %[^)])", nname, lleft, rright);
        name = nname;
        left = lleft;
        right = rright;
        new Node(name, left, right);
      }
    }
    vector<string> startNodes = Node::startingNodes();
    int highest = 0;
    for (const auto &it : startNodes) {
      mem.clear();
      cout << "new run, starting at " << it << endl;
      set<int> possibleResults = rec(it, 0);

      cout << "end run, results:" << endl << endl;
      for (const auto &it2 : possibleResults) {
        cout << it2 << endl;
      }
      // set highest to the max of highest and the maximum of possibleResults
      highest = max(highest, *possibleResults.rbegin());
    }

    cout << highest << endl << flush;
    set<int> jointIntersection;
    for (const auto &it : startNodes) {
      mem.clear();
      set<int> possibleResults = rec2(it, 0, highest + 1);
      if (jointIntersection.empty()) {
        jointIntersection = possibleResults;
      } else {
        set<int> newIntersection;
        set_intersection(jointIntersection.begin(), jointIntersection.end(), possibleResults.begin(),
                         possibleResults.end(), inserter(newIntersection, newIntersection.begin()));
        jointIntersection = newIntersection;
      }
    }

    // return the minimum of jointIntersection
    if (jointIntersection.empty()) return -1;
    return *jointIntersection.begin();
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
