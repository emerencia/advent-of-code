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

const vector<PII> ds = {{-1, 0},
                        {1,  0},
                        {0,  -1},
                        {0,  1}};

const vector<int> nrSteps = {6, 10, 50, 100, 500, 1000, 5000};


class Assignment {
public:
  vector<vector<char>> grid;
  set<PII> endPositions;
  set<PIII> seen;

  void travelNrSteps(int row, int col, int stepsLeft) {
    if (seen.count({{row, col}, stepsLeft})) return;
    seen.insert({{row, col}, stepsLeft});

    if (stepsLeft == 0) {
      endPositions.insert({row, col});
      return;
    }
    for (auto d: ds) {
      int nRow = row + d.first;
      int nCol = col + d.second;
      int modRow = nRow;
      while (modRow < 0) modRow += (int) grid.size();
      modRow %= (int) grid.size();
      int modCol = nCol;
      while (modCol < 0) modCol += (int) grid[0].size();
      modCol %= (int) grid[0].size();
      if (grid[modRow][modCol] != '#') {
        travelNrSteps(nRow, nCol, stepsLeft - 1);
      }
    }
  }

  int simulateSteps(int maxSteps, int startRow, int startCol) {
    seen.clear();
    endPositions.clear();
    travelNrSteps(startRow, startCol, maxSteps);
    return (int) endPositions.size();
  }

  int solution() {
    grid.clear();
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

    for (int i = 0; i < nrSteps.size(); ++i) {
      int result = simulateSteps(nrSteps[i], startRow, startCol);
      cout << "Steps: " << nrSteps[i] << " Result: " << result << endl << endl;
    }
    return -1;
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
