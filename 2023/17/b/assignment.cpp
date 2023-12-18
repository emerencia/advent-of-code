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
    // reverse the order of the priority queue, so we get the smallest heat loss first.
    priority_queue<PIV, vector<PIV>, greater<>> q;
    map<PIII, int> minHeatLossSeen;
    q.emplace(0, row, col, -1);
    int result = INT_MAX;
    while (!q.empty()) {
      PIV p = q.top();
      q.pop();
      int heatLossSoFar = get<0>(p);
      int crow = get<1>(p);
      int ccol = get<2>(p);
      int prevDir = get<3>(p);

      if (heatLossSoFar > result) continue;

      if (minHeatLossSeen.find({{crow, ccol}, prevDir}) != minHeatLossSeen.end()) {
        int minHeatLoss = minHeatLossSeen[{{crow, ccol}, prevDir}];
        if (heatLossSoFar >= minHeatLoss) continue;
      }
      minHeatLossSeen[{{crow, ccol}, prevDir}] = heatLossSoFar;

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
        for (int i = 0; i < 10; i++) {
          nrow += ds[d].first;
          ncol += ds[d].second;
          if (outofBounds(nrow, ncol)) break;
          nHeatLossSoFar += heatLoss[nrow][ncol];
          if (i < 3) continue;
          q.emplace(nHeatLossSoFar, nrow, ncol, d);
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
