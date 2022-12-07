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

const LL MAX_SIZE = 100000;

struct Node {
  string name;
  LL size;
  Node* parent;
  vector<Node> children;
  Node(string name, LL size, Node* parent = NULL): name(name), size(size), parent(parent) {
  }

  LL recursiveSize() {
    LL result = size;
    for (int i = 0; i< children.size();i++) {
      result += children[i].recursiveSize();
    }
    return result;
  }

  void addNode(string nname, LL sz) {
    if (!dirExists(nname)) {
      children.push_back(Node(nname, sz, this));
    }
  }

  Node* findDir(string nname) {
    for (int i = 0; i < children.size(); i++) {
      if (children[i].name == nname) {
        return &children[i];
      }
    }
    cout << "ERROR: child not found: " << nname << " in " << name << endl;
    return NULL;
  }

  bool dirExists(string nname) {
    for (int i = 0;i < children.size(); i++) {
      if (children[i].name == nname) return true;
    }
    return false;
  }

  LL largeSize() {
    // Don't count individual files
    if (size > 0) return 0;

    LL result = 0;
    LL curSize = recursiveSize();
    if (curSize <= MAX_SIZE) {
      // cout << "counting " << name << " at: " << curSize << endl;
      result += curSize;
    }
    for (int i = 0;i<children.size();i++) {
      result += children[i].largeSize();
    }
    return result;
  }
};

class Assignment {
public:

  LL solution() {
    Node fs("/", 0);
    Node* curNode = &fs;
    // string cwd = "/";
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      stringstream s(line);
      if (line[0] == '$') { // command
        if (line.substr(2,2) == "cd") {
          string newDir = line.substr(5);
          if (newDir == "/") {
            curNode = &fs;
          } else if (newDir == "..") {
            curNode = (curNode->parent == NULL ? &fs : curNode->parent);
          } else {
            // find a directory named this and go to it.
            curNode = curNode->findDir(newDir);
          }
        } else {
          // we are listing this directory... do nothing for now;
        }
      } else if (line[0] == 'd') { // dir
        string dir;
        string nname;
        s >> dir >> nname;
        curNode->addNode(nname, 0);
      } else { // file size
        LL sz;
        string filename;
        s >> sz >> filename;
        curNode->addNode(filename, sz);
      }
    }

    return fs.largeSize();
  };
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
