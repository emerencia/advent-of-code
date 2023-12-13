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
  vector<vector<char>> grid;

  bool columnsEqual(int col1, int col2) {
    // precondition: col1 < col2 (not used)
    for (auto &row: grid) {
      if (row[col1] != row[col2]) {
        return false;
      }
    }
    return true;
  }

  bool rowsEqual(int row1, int row2) {
    // precondition: row1 < row2 (not used)
    for (int col = 0; col < grid[0].size(); col++) {
      if (grid[row1][col] != grid[row2][col]) {
        return false;
      }
    }
    return true;
  }

  vector<int> vertical() {
    // return the number of columns to the left of each vertical line of reflection
    vector<int> result;
    for (int col = 1; col < grid[0].size(); col++) {
      int left = col - 1;
      int right = col;
      bool good = true;
      while (left >= 0 && right < grid[0].size()) {
        if (!columnsEqual(left, right)) {
          good = false;
          break;
        }
        left--;
        right++;
      }
      if (good) {
        result.push_back(col);
      }
    }
    return result;
  }

  vector<int> horizontal() {
    // return the number of rows above each horizontal line of reflection.
    vector<int> result;
    for (int row = 1; row < grid.size(); row++) {
      int top = row - 1;
      int bottom = row;
      bool good = true;
      while (top >= 0 && bottom < grid.size()) {
        if (!rowsEqual(top, bottom)) {
          good = false;
          break;
        }
        top--;
        bottom++;
      }
      if (good) {
        result.push_back(row);
      }
    }
    return result;
  }

  int calculate() {
    // return the number of columns to the left of each vertical line of reflection + 100 times the number of
    // rows above each horizontal line of reflection.
    // NOTE: apparently with the given input, there's only ever one solution (either a horizontal axis or a vertical
    // one), but never both, and never neither. That doesn't hold in general, which is why I made my solution like this.
    vector<int> verticalSolutions = vertical();
    vector<int> horizontalSolutions = horizontal();
    int result = 0;
    for (int verticalSolution: verticalSolutions) {
      result += verticalSolution;
    }
    for (int horizontalSolution: horizontalSolutions) {
      result += horizontalSolution * 100;
    }
    return result;
  }

  int solution() {
    int result = 0;
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) {
        if (!grid.empty()) {
          result += calculate();
        }
        grid.clear();
        continue;
      }
      vector<char> row;
      for (char c: line) {
        row.push_back(c);
      }
      grid.push_back(row);
    }
    if (!grid.empty()) {
      result += calculate();
      grid.clear();
    }
    return result;
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
