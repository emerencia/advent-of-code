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

  [[nodiscard]] int trailheadScore(int row, int col) const {
    set<PII> endPositionsSeen;
    queue<PII> q;
    set<PII> seen;
    q.emplace(row, col);
    while (!q.empty()) {
      auto [fst, snd] = q.front();
      q.pop();
      int crow = fst;
      int ccol = snd;
      const int curVal = grid[crow][ccol];
      if (curVal == 9) {
        endPositionsSeen.insert({crow, ccol});
        continue;
      }
      for (const auto &[fst, snd]: ds) {
        int nrow = crow + fst;
        int ncol = ccol + snd;
        if (outOfBounds(nrow, ncol)) continue;
        if (const int nextVal = grid[nrow][ncol]; nextVal == curVal + 1) {
          if (endPositionsSeen.find({nrow, ncol}) != endPositionsSeen.end()) continue;
          if (seen.find({nrow, ncol}) != seen.end()) continue;
          seen.insert({nrow, ncol});
          q.emplace(nrow, ncol);
        }
      }
    }

    return static_cast<int>(endPositionsSeen.size());
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
