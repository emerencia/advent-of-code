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

  int calculateOrig() {
    // return the number of columns to the left of each vertical line of reflection + 100 times the number of rows
    // above each horizontal line of reflection.
    // NOTE: apparently with the given input, there's only ever one solution (either a horizontal axis or a vertical
    // one), but never both, and never neither. That doesn't hold in general, which is why I made my solution like this.
    vector<int> verticalSolutions = vertical();
    if (verticalSolutions.size() > 1) {
      cout << "vertical size bigger than one: " << verticalSolutions.size() << endl;
      return -1;
    }
    vector<int> horizontalSolutions = horizontal();
    if (horizontalSolutions.size() > 1) {
      cout << "horizontal size bigger than one: " << horizontalSolutions.size() << endl;
      return -1;
    }
    if (!horizontalSolutions.empty() && !verticalSolutions.empty()) {
      cout << "horizontal and vertical size bigger than zero: " << horizontalSolutions.size() << " "
           << verticalSolutions.size() << endl;
    }
    int result = 0;
    for (int verticalSolution: verticalSolutions) {
      result += verticalSolution;
    }
    for (int horizontalSolution: horizontalSolutions) {
      result += horizontalSolution * 100;
    }
    return result;
  }

  int calculate(int oldResult) {
    // Do the same als in calculateOrig but remove the original result from the solutions.
    vector<int> verticalSolutions2 = vertical();
    int oldVerticalResult = oldResult % 100;

    // remove oldVerticalResult from verticalSolutions if it exists in there.
    vector<int> verticalSolutions;
    for (int i: verticalSolutions2) {
      if (i != oldVerticalResult) {
        verticalSolutions.push_back(i);
      }
    }

    if (verticalSolutions.size() > 1) {
      cout << "vertical size bigger than one: " << verticalSolutions.size() << endl;
      return -1;
    }
    vector<int> horizontalSolutions2 = horizontal();
    int oldHorizontalResult = oldResult / 100;
    vector<int> horizontalSolutions;
    for (int i: horizontalSolutions2) {
      if (i != oldHorizontalResult) {
        horizontalSolutions.push_back(i);
      }
    }

    if (horizontalSolutions.size() > 1) {
      cout << "horizontal size bigger than one: " << horizontalSolutions.size() << endl;
      return -1;
    }
    if (!horizontalSolutions.empty() && !verticalSolutions.empty()) {
      cout << "horizontal and vertical size bigger than zero: " << horizontalSolutions.size() << " "
           << verticalSolutions.size() << endl;
    }
    int result = 0;
    for (int verticalSolution: verticalSolutions) {
      result += verticalSolution;
    }
    for (int horizontalSolution: horizontalSolutions) {
      result += horizontalSolution * 100;
    }
    return result;
  }

  int calculate2() {
    // naive solution would be to change each cell to find a different line of reflection.
    // Naive solution works here. Another idea I had was just to check the number of differences
    // between rows or columns and if there's exactly one difference then use that as solution.
    // But I'm not sure if that would result in a unique solution.
    int originalResult = calculateOrig();
    if (originalResult == 0) {
      cout << "ERROR: could not find original line of reflection" << endl;
    }
    for (auto &row: grid) {
      for (int col = 0; col < grid[0].size(); col++) {
        char oldChar = row[col];
        row[col] = (oldChar == '#') ? '.' : '#';
        int newResult = calculate(originalResult);
        if (newResult > 0 && newResult != originalResult) {
          return newResult;
        }
        row[col] = oldChar;
      }
    }
    // Btw: none of the couts here, or in calculate or calculateOrig are ever triggered.
    // There's probably some underlying assumption about the input that I didn't have to look into to solve this.
    cout << "ERROR: did not find a new line" << endl;
    return -1;
  }

  int solution() {
    int result = 0;
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) {
        if (!grid.empty()) {
          result += calculate2();
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
      result += calculate2();
      grid.clear();
    }
    return result;
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
