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

const LL doubleFactor = 1000000;

class Assignment {
public:

  // Manhattan distance
  static LL solution() {
    LL result = 0;
    vector<vector<char>> grid;
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      vector<char> row;
      for (char c: line) {
        row.push_back(c);
      }
      grid.push_back(row);
    }

    // Expand the empty rows and columns of the grid
    vector<bool> rowsUsed(grid.size());
    vector<bool> colsUsed(grid[0].size());
    vector<PII> galaxies;
    for (int row = 0; row < grid.size(); row++) {
      for (int col = 0; col < grid[row].size(); col++) {
        if (grid[row][col] == '#') {
          rowsUsed[row] = true;
          colsUsed[col] = true;
          galaxies.emplace_back(row, col);
        }
      }
    }

    for (int i = 0; i + 1 < galaxies.size(); i++) {
      for (int j = i + 1; j < galaxies.size(); j++) {
        LL tempResult = 0;
        for (int row = min(galaxies[i].first, galaxies[j].first);
             row < max(galaxies[i].first, galaxies[j].first); row++) {
          if (!rowsUsed[row]) {
            tempResult += doubleFactor;
          } else {
            tempResult += 1;
          }
        }
        for (int col = min(galaxies[i].second, galaxies[j].second);
             col < max(galaxies[i].second, galaxies[j].second); col++) {
          if (!colsUsed[col]) {
            tempResult += doubleFactor;
          } else {
            tempResult += 1;
          }
        }
        result += tempResult;
      }
    }
    return result;
  }
};

int main() {
  cout << Assignment::solution() << endl;
}
