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

const vector<PII> ds = {
  {1, 0},
  {0, 1},
  {-1, 0},
  {0, -1}
};

class Assignment {
public:
  vector<vector<int> > grid;
  vector<PII> trailheads;

  [[nodiscard]] bool outOfBounds(const int row, const int col) const {
    return row < 0 || row >= grid.size() || col < 0 || col >= grid[0].size();
  }

  [[nodiscard]] int trailheadScore(const int row, const int col) const {
    vector waysToGetThere(grid.size(), vector(grid[0].size(), 0));
    waysToGetThere[row][col] = 1;

    for (int i = 0; i < 9; i++) {
      for (int r = 0; r < grid.size(); r++) {
        for (int c = 0; c < grid[0].size(); c++) {
          if (grid[r][c] != i) continue;
          for (const auto &[dr, dc]: ds) {
            const int newR = r + dr;
            const int newC = c + dc;
            if (outOfBounds(newR, newC) || grid[newR][newC] != i + 1) continue;
            waysToGetThere[newR][newC] += waysToGetThere[r][c];
          }
        }
      }
    }

    int result = 0;
    for (int r = 0; r < grid.size(); r++) {
      for (int c = 0; c < grid[0].size(); c++) {
        if (grid[r][c] == 9) {
          result += waysToGetThere[r][c];
        }
      }
    }
    return result;
  }

  int solution() {
    grid.clear();
    int result = 0;
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      istringstream ss(line);
      vector<int> row;
      char c;
      while (ss >> c) {
        if (c == '0') {
          trailheads.emplace_back(grid.size(), row.size());
        }
        row.push_back(c - '0');
      }
      grid.push_back(row);
    }
    for (const auto &[row,col]: trailheads) {
      result += trailheadScore(row, col);
    }
    return result;
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
