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
typedef pair<pair<int, int>, int> PIII;
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

  int minimumHeatloss(int row, int col) {
    queue<PIV> q;
    // set<PIV> seen;
    map<PIII, int> minHeatLossSeen;
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

      if (minHeatLossSeen.find({{crow, ccol}, prevDir}) != minHeatLossSeen.end()) {
        int minHeatLoss = minHeatLossSeen[{{crow, ccol}, prevDir}];
        if (heatLossSoFar >= minHeatLoss) continue;
        minHeatLossSeen[{{crow, ccol}, prevDir}] = heatLossSoFar;
      } else {
        minHeatLossSeen[{{crow, ccol}, prevDir}] = heatLossSoFar;
      }
      /* Turns out this wasn't needed and just slowed things
      if (seen.find(p) != seen.end()) continue;
      seen.insert(p);
      */
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
        for (int i = 0; i < 3; i++) {
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
