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
typedef tuple<int, int, int, int> PIV;

const vector<PII> ds = {{1,  0},
                        {0,  1},
                        {-1, 0},
                        {0,  -1}};

class Assignment {
public:
  vector<vector<int>> heatLoss;

  bool outofBounds(int row, int col) {
    return row < 0 || row >= heatLoss.size() || col < 0 || col >= heatLoss[0].size();
  }

  /*
  int rec(int row, int col, int prevDir, int blocksLeftInDir, int stepsTaken) {
    int &r = mem[row][col][prevDir][blocksLeftInDir][stepsTaken];
    if (r != -1) return r;

    if (row == heatLoss.size() - 1 && col == heatLoss[0].size() - 1) {
      // we already counted the heatloss incurred by the current tile.
      return r = 0;
    }

    if (stepsTaken > 298) return r = 1000000;

    int result = 1000000;
    for (int d = 0; d < 4; d++) {
      // we can't go in the opposite direction of prevDir
      if ((d + 2) % 4 == prevDir) continue;

      int stepsLeft = 2;
      if (d == prevDir) {
        if (blocksLeftInDir == 0) continue;
        stepsLeft = blocksLeftInDir - 1;
      }
      int nrow = row + ds[d].first;
      int ncol = col + ds[d].second;
      if (outofBounds(nrow, ncol)) continue;
      result = min(result, heatLoss[nrow][ncol] + rec(nrow, ncol, d, stepsLeft, stepsTaken + 1));
    }
    return r = result;
  }
  */

  int minimumHeatloss(int row, int col) {
    queue<PIV> q;
    set<PIV> seen;
    q.emplace(row, col, -1, 0);
    int result = INT_MAX;
    while (!q.empty()) {
      PIV p = q.front();
      q.pop();
      int crow = get<0>(p);
      int ccol = get<1>(p);
      int prevDir = get<2>(p);
      int heatLossSoFar = get<3>(p);

      if (heatLossSoFar > result) continue;

      if (outofBounds(crow, ccol)) continue;
      if (seen.find(p) != seen.end()) continue;
      seen.insert(p);

      if (crow == heatLoss.size() - 1 && ccol == heatLoss[0].size() - 1) {
        result = min(result, heatLossSoFar);
      }

      for (int d = 0; d < 4; d++) {
        // we can't go in the opposite direction of prevDir
        if ((d + 2) % 4 == prevDir) continue;
        // we can't continue in the same direction as prevDir
        if (d == prevDir) continue;
        int nrow = crow;
        int ncol = ccol;
        int nHeatLossSoFar = heatLossSoFar;
        for (int i=0;i<3;i++) {
          nrow += ds[d].first;
          ncol += ds[d].second;
          if (outofBounds(nrow, ncol)) break;
          nHeatLossSoFar += heatLoss[nrow][ncol];
          q.emplace(nrow, ncol, d, nHeatLossSoFar);
        }
      }
    }
    return result;
  }

  int solution() {
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      // read the grid digit by digit
      vector<int> row;
      for (char c: line) {
        row.push_back(c - '0');
      }
      heatLoss.push_back(row);
    }
    return minimumHeatloss(0, 0);
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
