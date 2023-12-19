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

const map<char, PII> dirToDelta = {{'D', {1,  0}},
                                   {'R', {0,  1}},
                                   {'U', {-1, 0}},
                                   {'L', {0,  -1}}};

const vector<PII> ds = {{1,  0},
                        {0,  1},
                        {-1, 0},
                        {0,  -1}};

char grid[10000][10000];
const int OFFSET = 5000;

class Assignment {
public:
  int minRow;
  int maxRow;
  int minCol;
  int maxCol;

  bool outofBounds(int row, int col) {
    return row < minRow || row >= maxRow || col < minCol || col >= maxCol;
  }

  int calcBoundaryPlusInterior() {
    // floodfill the outside and subtract from the total.
    queue<PII> q;
    set<PII> seen;
    q.emplace(minRow, minCol);
    seen.emplace(minRow, minCol);
    grid[minRow][minCol] = 'X';
    while (!q.empty()) {
      PII p = q.front();
      q.pop();
      int row = p.first;
      int col = p.second;
      for (auto d: ds) {
        int nrow = row + d.first;
        int ncol = col + d.second;
        if (!outofBounds(nrow, ncol) && grid[nrow][ncol] == '.' && seen.find({nrow, ncol}) == seen.end()) {
          q.emplace(nrow, ncol);
          seen.emplace(nrow, ncol);
          grid[nrow][ncol] = 'X';
        }
      }
    }
    return ((maxRow - minRow) * (maxCol - minCol)) - (int) seen.size();
  }

  void printGrid() {
    for (int row = minRow; row < maxRow; row++) {
      for (int col = minCol; col < maxCol; col++) {
        cout << grid[row][col];
      }
      cout << endl;
    }
  }

  int solution() {
    memset(grid, '.', sizeof(grid));
    minRow = minCol = OFFSET;
    maxRow = maxCol = OFFSET;

    int col = OFFSET;
    int row = OFFSET;
    grid[row][col] = '#';
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      char direction;
      int steps;
      stringstream ss(line);
      // ignore the color for now
      ss >> direction >> steps;
      for (int i = 0; i < steps; i++) {
        row += dirToDelta.at(direction).first;
        col += dirToDelta.at(direction).second;
        if (row < minRow) minRow = row;
        if (row > maxRow) maxRow = row;
        if (col < minCol) minCol = col;
        if (col > maxCol) maxCol = col;
        grid[row][col] = '#';
      }
    }
    // If we end on the boundary, expand the grid, so we always start outside.
    maxRow += 2;
    maxCol += 2;
    minRow--;
    minCol--;
    int result = calcBoundaryPlusInterior();
    // printGrid();
    return result;
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
