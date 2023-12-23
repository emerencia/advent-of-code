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

const vector<PII> ds = {{-1, 0},
                        {1,  0},
                        {0,  -1},
                        {0,  1}};

class Assignment {
public:
  vector<vector<set<PII>>> grid;
  set<PII> rocks;

  void printGrid(const vector<vector<set<PII>>> &gridd) {
    for (int i = 0;i < gridd.size(); ++i) {
      for (int j = 0; j < gridd[0].size(); ++j) {
        if (rocks.find({i, j}) != rocks.end()) {
          cout << "#";
        } else if (gridd[i][j].empty()) {
          cout << ".";
        } else {
          cout << gridd[i][j].size();
        }
      }
      cout << endl;
    }
    cout << endl;
  }

  void calcNextGrid(int nrTimes) {
    for (int k = 0;k < nrTimes; k++) {
      vector<vector<set<PII>>> nextGrid(grid.size(), vector<set<PII>>(grid[0].size()));
      for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[0].size(); ++j) {
          if (rocks.find({i, j}) != rocks.end()) {
            nextGrid[i][j] = {}; // not sure if needed
            continue;
          }
          for (auto d: ds) {
            int nRow = i + d.first;
            int nCol = j + d.second;
            int rowDelta = 0;
            int colDelta = 0;
            int modRow = nRow;
            while (modRow < 0) modRow += (int) grid.size();
            modRow %= (int) grid.size();
            if (modRow > nRow) {
              rowDelta = -1;
            } else if (modRow < nRow) {
              rowDelta = 1;
            }
            int modCol = nCol;
            while (modCol < 0) modCol += (int) grid[0].size();
            modCol %= (int) grid[0].size();
            if (modCol > nCol) {
              colDelta = -1;
            } else if (modCol < nCol) {
              colDelta = 1;
            }
            if (rocks.find({modRow, modCol}) != rocks.end()) continue;
            for (auto p: grid[i][j]) {
              nextGrid[modRow][modCol].insert({p.first + rowDelta, p.second + colDelta});
            }
          }
        }
      }
      swap(grid, nextGrid);
    }
  }

  LL calcGridSize() {
    LL result = 0;
    for (int i = 0; i < grid.size(); ++i) {
      for (int j = 0; j < grid[0].size(); ++j) {
        if (rocks.find({i, j}) != rocks.end()) continue;
        result += grid[i][j].size();
      }
    }
    return result;
  }

  int solution() {
    grid.clear();
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;
      vector<set<PII>> row;
      for (char c: line) {
        if (c == '#') {
          rocks.insert({(int) grid.size(), (int) row.size()});
          row.push_back({});
        } else if (c == 'S') {
          row.push_back({{0,0}});
        } else if (c == '.') {
          row.push_back({});
        } else {
          cout << "ERROR: unknown char: " << c << endl;
          exit(1);
        }
      }
      grid.push_back(row);
    }
    calcNextGrid(1000);
    // printGrid(grid);
    return calcGridSize();
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
