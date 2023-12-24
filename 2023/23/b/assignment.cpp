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
typedef tuple<int, int, int, int, int> TV;

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
  static int count;
  int id;

  Node() {
    id = count++;
  }
};

int Node::count = 0;

const vector<PII> ds = {{-1, 0},
                        {1, 0},
                        {0, -1},
                        {0, 1}};

const vector<char> NODE_SYMBOLS = {'>', '<', '^', 'v'};

class Assignment {
public:
  vector<vector<char>> grid;
  map<PII, Node *> nodes;
  map<pair<Node *, LL>, int> memo;

  bool isInGrid(int row, int col) {
    return row >= 0 && row < (int) grid.size() && col >= 0 && col < (int) grid[0].size();
  }

  void calculateGraph() {
    for (auto &p: nodes) {
      // find outgoing edges. Assume that we can only ever go
      // in one direction. Go until we can't go anymore
      int row = p.first.first;
      int col = p.first.second;
      queue<TV> q;
      q.emplace(row, col, -1, -1, 0);
      while (!q.empty()) {
        auto [cRow, cCol, prevRow, prevCol, weight] = q.front();
        for (const auto &d: ds) {
          int nRow = cRow + d.first;
          int nCol = cCol + d.second;
          if (!isInGrid(nRow, nCol) || grid[nRow][nCol] == '#') continue;
          // don't go back
          if (nRow == prevRow && nCol == prevCol) continue;

          // if we found a node, add an edge
          if (find(NODE_SYMBOLS.begin(), NODE_SYMBOLS.end(), grid[nRow][nCol]) != NODE_SYMBOLS.end()) {
            p.second->edges.insert({nodes[{nRow, nCol}], weight + 1});
            // add an edge back
            nodes[{nRow, nCol}]->edges.insert({p.second, weight + 1});
          }
          if (grid[nRow][nCol] == '.') {
            q.emplace(nRow, nCol, cRow, cCol, weight + 1);
          }
        }
        q.pop();
      }
    }
  }


  int longestPath(Node *curNode, Node *endNode, LL visited) {
    // Backtracking + dfs
    if (curNode == endNode) return 0;
    if (memo.find({curNode, visited}) != memo.end()) {
      return memo[{curNode, visited}];
    }
    int result = -1;

    // compute best path
    for (const auto &edge: curNode->edges) {
      if (visited & (1LL << edge.to->id)) continue;
      int pathLength = longestPath(edge.to, endNode, visited | (1LL << edge.to->id));
      if (pathLength != -1) {
        result = max(result, pathLength + edge.weight);
      }
    }
    return memo[{curNode, visited}] = result;
  }

  void preprocessGrid() {
    // I think that our solution only goes wrong in the following cases:
    // #v#
    // >.>  because it can cross the (.) twice (once horizontally and once vertically).
    // #v#
    // if this is the case, replace the second > with a .
    // Because the number of nodes was too high to feasibly run the backtracking algorithm,
    // in this preprocessing step I collapse all T-junctions and 4-way junctions into a single node
    // and adjusted the calculating the graph part to handle this.
    for (int row = 1; row < (int) grid.size() - 1; row++) {
      for (int col = 1; col < (int) grid[0].size() - 1; col++) {
        if (grid[row][col] == '.' &&
            ((grid[row - 1][col] == 'v' && grid[row + 1][col] == 'v') ||
             (grid[row][col - 1] == '>' && grid[row][col + 1] == '>'))) {
          grid[row][col] = '^'; // since they're unused
          nodes.insert({{row, col}, new Node()});
          // remove the other nodes
          if (grid[row - 1][col] == 'v') {
            grid[row - 1][col] = '.';
            nodes.erase({row - 1, col});
          }
          if (grid[row + 1][col] == 'v') {
            grid[row + 1][col] = '.';
            nodes.erase({row + 1, col});
          }
          if (grid[row][col - 1] == '>') {
            grid[row][col - 1] = '.';
            nodes.erase({row, col - 1});
          }
          if (grid[row][col + 1] == '>') {
            grid[row][col + 1] = '.';
            nodes.erase({row, col + 1});
          }
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
    cout << "nodes size: " << nodes.size() << endl;
    LL visited = 1LL << startNode->id;
    return longestPath(startNode, endNode, visited);
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
