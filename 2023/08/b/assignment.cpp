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
  string name;
  string left;
  string right;

  static map<string, Node *> nodes;

  Node(string name, string l, string r) : name(name), left(l), right(r) {
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

class Assignment {

public:
  // Greatest common divisor:
  LL gcd(LL a, LL b) {
    if (b == 0) return a;
    return gcd(b, a % b);
  }

  // Least common multiple:
  LL lcm(LL a, LL b) {
    LL g = gcd(a, b);
    return (a / g) * b;
  }

  LL solution() {
    string directions;
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
    vector<string> curNodes = Node::startingNodes();
    int nrSimultaneousNodes = curNodes.size();
    map<int, int> firstZFoundAt;
    int directionIdx = 0;
    int curStep = 0;
    while (firstZFoundAt.size() < nrSimultaneousNodes) {
      // go from all current to next nodes and update if we found any Z
      for (int i =0;i< curNodes.size() ;i++) {
        if (directions[directionIdx] == 'L') {
          curNodes[i] = Node::nodes[curNodes[i]]->left;
        } else {
          curNodes[i] = Node::nodes[curNodes[i]]->right;
        }
        if (curNodes[i][2] == 'Z') {
          if (!firstZFoundAt.count(i)) {
            firstZFoundAt[i] = curStep + 1;
          }
          if (firstZFoundAt.size() == nrSimultaneousNodes) break;
        }
      }
      if (firstZFoundAt.size() == nrSimultaneousNodes) break;
      curStep++;
      directionIdx = (directionIdx + 1)% directions.size();
    }
    // return the lcm of the values of firstZFoundAt
    LL r = 1;
    for (auto const &it : firstZFoundAt) {
      r = lcm(r, it.second);
    }
    return r;
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
