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
typedef pair<int, pair<int, int>> PIII;

const vector<PII> ds = {{-1, 0},
                        {1,  0},
                        {0,  -1},
                        {0,  1}};

const vector<int> nrSteps = {6, 10, 50, 100, 500, 1000, 5000};

const int MAX_STEPS = 30;

class Assignment {
public:
  vector<vector<char>> grid;
  int startRow{};
  int startCol{};
  int minCol{};
  int maxCol{};
  int minRow{};
  int maxRow{};

  void printGrid(const set<PIII> &seen, int maxSteps) {
    int sRow = 0;
    while (sRow > minRow) sRow -= (int) grid.size();
    int eRow = (int) grid.size();
    while (eRow <= maxRow) eRow += (int) grid.size();
    int sCol = 0;
    while (sCol > minCol) sCol -= (int) grid[0].size();
    int eCol = (int) grid[0].size();
    while (eCol <= maxCol) eCol += (int) grid[0].size();
    for (int row = sRow; row < eRow; ++row) {
      for (int col = sCol; col < eCol; ++col) {
        if (seen.find({maxSteps, {row, col}}) != seen.end()) {
          cout << "X";
        } else if (row == startRow && col == startCol) {
          cout << "S";
        } else {
          int modRow = row;
          while (modRow < 0) modRow += (int) grid.size();
          modRow %= (int) grid.size();
          int modCol = col;
          while (modCol < 0) modCol += (int) grid[0].size();
          modCol %= (int) grid[0].size();
          cout << grid[modRow][modCol];
        }
      }
      cout << endl;
    }
  }

  LL simulateSteps(int maxSteps) {
    // reverse the order so we find the smallest stepsTaken first
    priority_queue<PIII, vector<PIII>, greater<>> q;
    set<PIII> seen;
    q.push({0, {startRow, startCol}});
    int result = 0;
    while (!q.empty()) {
      PIII p = q.top();
      q.pop();
      int row = p.second.first;
      int col = p.second.second;
      int stepsTaken = p.first;

      // if we see something now we know it was reached in less steps,
      // so whatever we can reach here, we could do there as well.
      // So just stop.
      if (seen.find({stepsTaken, {row, col}}) != seen.end()) continue;
      seen.insert({stepsTaken, {row, col}});
      if (stepsTaken == maxSteps) {
        result++;
        if (row < minRow) minRow = row;
        if (row > maxRow) maxRow = row;
        if (col < minCol) minCol = col;
        if (col > maxCol) maxCol = col;
        continue;
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
          q.push({stepsTaken + 1, {nRow, nCol}});
        }
      }
    }
    printGrid(seen, maxSteps);
    return result;
  }

  LL solution() {
    startRow = -1;
    startCol = -1;
    grid.clear();
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      vector<char> row;
      for (char c: line) {
        if (c == 'S') {
          startRow = (int) grid.size();
          startCol = (int) row.size();
          c = '.';
        }
        row.push_back(c);
      }
      grid.push_back(row);
    }
    if (startRow == -1 || startCol == -1) {
      cout << "ERROR: start not found" << endl;
      exit(1);
    }
    LL lastDiff = 0;
    for (int steps = 1; steps < MAX_STEPS; ++steps) {
      int emptySimulation = (steps + 1) * (steps + 1);
      LL simulatedSteps = simulateSteps(steps);
      LL curDiff = emptySimulation - simulatedSteps;
      cout << steps << ": " << simulatedSteps << " (empty: " << emptySimulation << ") diff: " << curDiff
           << " delta diff:" << (curDiff - lastDiff) << endl << endl;
      lastDiff = emptySimulation - simulatedSteps;
    }
    return -1;
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
