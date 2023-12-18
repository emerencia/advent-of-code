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

const vector<PII> ds = {{1,  0},
                        {0,  1},
                        {-1, 0},
                        {0,  -1}};

// The minimum amount of heat loss to get to the bottom right corner from this point
// row col prevDir blocksLeftInDir
int mem[150][150][5][3][300];

class Assignment {
public:
  vector<vector<int>> heatLoss;

  bool outofBounds(int row, int col) {
    return row < 0 || row >= heatLoss.size() || col < 0 || col >= heatLoss[0].size();
  }

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

  int solution() {
    memset(mem, -1, sizeof(mem));
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
    int result = rec(0, 0, 4, 0, 0);
    return result;
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
