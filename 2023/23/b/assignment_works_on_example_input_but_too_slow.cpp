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

struct Node;

struct Edge {
  Node *to{};
  int weight{};

  bool operator<(const Edge &other) const {
    if (weight == other.weight) {
      return to < other.to;
    }
    return weight < other.weight;
  }
};

struct Node {
  set<Edge> edges;
};

const vector<PII> ds = {{-1, 0},
                        {1,  0},
                        {0,  -1},
                        {0,  1}};

const vector<char> NODE_SYMBOLS = {'>', '<', '^', 'v'};

class Assignment {
public:
  vector<vector<char>> grid;
  map<PII, Node *> nodes;
  map<pair<Node *, set<Node *>>, int> memo;

  bool isInGrid(int row, int col) {
    return row >= 0 && row < (int) grid.size() && col >= 0 && col < (int) grid[0].size();
  }

  bool canApproachFrom(int row, int col, int prevRow, int prevCol) {
    return true;
    // the node is at (row, col).
    if (grid[row][col] == '>') {
      return prevRow == row && prevCol + 1 == col;
    }
    if (grid[row][col] == '<') {
      return prevRow == row && prevCol - 1 == col;
    }
    if (grid[row][col] == '^') {
      return prevRow - 1 == row && prevCol == col;
    }
    if (grid[row][col] == 'v') {
      return prevRow + 1 == row && prevCol == col;
    }
    return false;
  }

  bool theOnlyDirection(char nodeSymbol, int dRow, int dCol) {
    if (nodeSymbol == '>') {
      return dRow == 0 && dCol == 1;
    }
    if (nodeSymbol == '<') {
      return dRow == 0 && dCol == -1;
    }
    if (nodeSymbol == '^') {
      return true; // override this symbolto go both directions
      // return dRow == -1 && dCol == 0;
    }
    if (nodeSymbol == 'v') {
      return dRow == 1 && dCol == 0;
    }
    return false;
  }

  void calculateGraph() {
    for (auto &p: nodes) {
      // find outgoing edges. Assume that we can only ever go
      // in one direction. Go until we can't go anymore
      int row = p.first.first;
      int col = p.first.second;
      int prevRow = -1;
      int prevCol = -1;
      int nextRow = -1;
      int nextCol = -1;
      int weight = 0;
      bool foundNextDirection = true;
      while (foundNextDirection) {
        foundNextDirection = false;
        for (const auto &d: ds) {
          int nRow = row + d.first;
          int nCol = col + d.second;
          if (!isInGrid(nRow, nCol) || grid[nRow][nCol] == '#') continue;
          // don't go back
          if (nRow == prevRow && nCol == prevCol) continue;
          // if we are currently on a node, we can only go in one direction
          if (find(NODE_SYMBOLS.begin(), NODE_SYMBOLS.end(), grid[row][col]) != NODE_SYMBOLS.end() &&
              !theOnlyDirection(grid[row][col], d.first, d.second)) {
            continue;
          }

          // if we found a node, add an edge
          if (find(NODE_SYMBOLS.begin(), NODE_SYMBOLS.end(), grid[nRow][nCol]) != NODE_SYMBOLS.end() &&
              canApproachFrom(nRow, nCol, row, col)) {
            p.second->edges.insert({nodes[{nRow, nCol}], weight + 1});
            // add an edge back
            nodes[{nRow, nCol}]->edges.insert({p.second, weight + 1});
          }
          if (grid[nRow][nCol] == '.') {
            if (foundNextDirection) {
              cout << "WARNING: found multiple directions for (" << row << ", " << col << ")" << endl;
            }
            foundNextDirection = true;
            nextRow = nRow;
            nextCol = nCol;
          }
        }
        if (foundNextDirection) {
          prevRow = row;
          prevCol = col;
          row = nextRow;
          col = nextCol;
        }
        weight++;
      }
    }
  }

  int longestPath(Node *curNode, Node *endNode, set<Node *> &visited) {
    // Node: the graph is not directed, so there may be cycles.
    // Make sure that we don't visit a node more than once.
    if (curNode == endNode) return 0;
    if (memo.find({curNode, visited}) != memo.end()) {
      return memo[{curNode, visited}];
    }
    int result = -1;

    // compute best path
    for (const auto &edge: curNode->edges) {
      if (visited.find(edge.to) != visited.end()) continue;
      visited.insert(edge.to);
      int pathLength = longestPath(edge.to, endNode, visited);
      visited.erase(edge.to);
      if (pathLength != -1) {
        result = max(result, pathLength + edge.weight);
      }
    }
    return memo[{curNode, visited}] = result;
  }

  void preprocessGrid() {
    // I think that our solution only goes wrong in the following cases:
    // #v#
    // >.>
    // #v#
    // if this is the case, replace the second > with a .
    for (int row = 1; row < (int) grid.size() - 1; row++) {
      for (int col = 1; col < (int) grid[0].size() - 1; col++) {
        if (grid[row][col] == '.' &&
            ((grid[row - 1][col] == 'v' && grid[row + 1][col] == 'v') ||
            (grid[row][col - 1] == '>' && grid[row][col + 1] == '>'))) {
           grid[row][col] = '^'; // since they're unused
           nodes.insert({{row, col}, new Node()});
        }
      }
    }
  }

  int solution() {
    memo.clear();
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      vector<char> row;
      for (char c: line) {
        row.push_back(c);
        if (find(NODE_SYMBOLS.begin(), NODE_SYMBOLS.end(), c) != NODE_SYMBOLS.end()) {
          nodes[{(int) grid.size(), (int) row.size() - 1}] = new Node();
        }
      }
      grid.push_back(row);
    }
    grid[0][1] = 'v';
    grid[(int) grid.size() - 1][(int) grid[0].size() - 2] = 'v';
    nodes[{0, 1}] = new Node();
    nodes[{(int) grid.size() - 1, (int) grid[0].size() - 2}] = new Node();
    preprocessGrid();
    calculateGraph();
    Node *startNode = nodes[{0, 1}];
    Node *endNode = nodes[{(int) grid.size() - 1, (int) grid[0].size() - 2}];
    set<Node *> visited;
    visited.insert(startNode);
    return longestPath(startNode, endNode, visited);
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
