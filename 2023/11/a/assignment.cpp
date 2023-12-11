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

class Assignment {
public:

  // Manhattan distance
  static int solution() {
    int result = 0;
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
    for (int row = 0; row < grid.size(); row++) {
      for (int col = 0; col < grid[row].size(); col++) {
        if (grid[row][col] == '#') {
          rowsUsed[row] = true;
          colsUsed[col] = true;
        }
      }
    }

    vector<vector<char>> newGrid;
    // double the unused rows
    for (int row = 0; row < grid.size(); row++) {
      newGrid.push_back(grid[row]);
      if (!rowsUsed[row]) {
        newGrid.push_back(grid[row]);
      }
    }

    // double the unused columns
    int colsInserted = 0;
    for (int col = 0; col < grid[0].size(); col++) {
      if (colsUsed[col]) continue;
      for (int row = 0; row < newGrid.size(); row++) {
        newGrid[row].insert(newGrid[row].begin() + col + colsInserted, '.');
      }
      colsInserted++;
    }

    // calculate galaxies on the new grid
    vector<PII> galaxies;
    for (int row = 0; row < newGrid.size(); row++) {
      for (int col = 0; col < newGrid[row].size(); col++) {
        if (newGrid[row][col] == '#') {
          galaxies.emplace_back(row, col);
        }
      }
    }

    for (int i = 0; i + 1 < galaxies.size(); i++) {
      for (int j = i + 1; j < galaxies.size(); j++) {
        result += abs(galaxies[i].first - galaxies[j].first) + abs(galaxies[i].second - galaxies[j].second);
      }
    }
    return result;
  }
};

int main() {
  cout << Assignment::solution() << endl;
}
