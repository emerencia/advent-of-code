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

int mem[65][150][150];

class Assignment {
public:
  vector<vector<char>> grid;
  set<PII> endPositions;

  bool inGrid(int x, int y) {
    return x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size();
  }

  void travelNrSteps(int row, int col, int stepsLeft) {
    int &r = mem[stepsLeft][row][col];
    if (r != -1) return;
    r = 0;

    if (stepsLeft == 0) {
      endPositions.insert({row, col});
      return;
    }
    for (auto d: ds) {
      int nRow = row + d.first;
      int nCol = col + d.second;
      if (inGrid(nRow, nCol) && grid[nRow][nCol] != '#') {
        travelNrSteps(nRow, nCol, stepsLeft - 1);
      }
    }
  }

  int solution() {
    grid.clear();
    memset(mem, -1, sizeof(mem));
    int startRow = -1;
    int startCol = -1;
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      vector<char> row;
      for (char c: line) {
        if (c == 'S') {
          startRow = (int) grid.size();
          startCol = (int) row.size();
        }
        row.push_back(c);
      }
      grid.push_back(row);
    }
    if (startRow == -1 || startCol == -1) {
      cout << "ERROR: start not found" << endl;
      exit(1);
    }
    travelNrSteps(startRow, startCol, grid.size() == 11 ? 6 : 64);
    return (int) endPositions.size();
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
