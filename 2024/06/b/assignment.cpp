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

const vector<PII> ds = {
  {1, 0},
  {0, 1},
  {-1, 0},
  {0, -1}
};

constexpr int UP = 2;
constexpr int DOWN = 0;
constexpr int LEFT = 3;
constexpr int RIGHT = 1;

class Assignment {
public:
  vector<vector<char> > grid;
  set<PIII> seen;
  PII start;

  bool outOfBounds(const int row, const int col) const {
    return row < 0 || row >= grid.size() || col < 0 || col >= grid[0].size();
  }

  bool hasLoop() {
    int direction = UP;
    int row = start.first;
    int col = start.second;
    seen.clear();
    while (!outOfBounds(row, col)) {
      if (seen.count({{row, col}, direction})) {
        return true;
      }
      seen.insert({{row, col}, direction});
      int nrow = row + ds[direction].first;
      int ncol = col + ds[direction].second;
      if (!outOfBounds(nrow, ncol) && grid[nrow][ncol] == '#') {
        direction = (direction + 3) % 4;
        nrow = row;
        ncol = col;
      }
      row = nrow;
      col = ncol;
    }
    return false;
  }

  int solution() {
    int result = 0;
    grid.clear();
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      stringstream ss(line);
      vector<char> row;
      char c;
      while (ss >> c) {
        row.push_back(c);
        if (c == '^') {
          start = {grid.size(), row.size() - 1};
        }
      }
      grid.push_back(row);
    }
    for (int i = 0; i < grid.size(); i++) {
      for (int j = 0; j < grid[i].size(); j++) {
        if (grid[i][j] != '.') {
          continue;
        }
        grid[i][j] = '#';
        result += hasLoop();
        grid[i][j] = '.';
      }
    }
    return result;
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
