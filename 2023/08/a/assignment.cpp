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

  static vector<Node *> nodes;
  static map<string, int> lookup;

  Node(string nam, string l, string r) : name(nam), left(l), right(r) {
    lookup[nam] = nodes.size();
    nodes.push_back(this);
  }
};


vector<Node *> Node::nodes;
map<string, int> Node::lookup;

int mem[1000][1000];

class Assignment {
  string directions;

public:
  int rec(string currentNode, int directionsIdx) {
    int& r = mem[Node::lookup[currentNode]][directionsIdx];
    if (r != -1) {
      // apparently memoization is not being used
      cout << "yes" << endl;
      return r;
    }

    if (currentNode == "ZZZ") return r = 0;

    r = 1000000;
    if (directions[directionsIdx] == 'L') {
      r = min(r, 1 + rec(Node::nodes[Node::lookup[currentNode]]->left, (directionsIdx + 1) % directions.size()));
    } else {
      r = min(r, 1 + rec(Node::nodes[Node::lookup[currentNode]]->right, (directionsIdx + 1) % directions.size()));
    }
    return r;
  }

  int solution() {
    memset(mem, -1, sizeof(mem));
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
    return rec("AAA", 0);
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
