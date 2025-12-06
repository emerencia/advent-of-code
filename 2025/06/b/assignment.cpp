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
  vector<vector<string> > data;
  vector<vector<char> > grid;
public:

  int nextSpace(const int col) const {
    // returns the next col (col included) that all rows in grid have a ' ' at this col or otherwise the length of the row.
    for (int nextCol = col; nextCol < grid[0].size(); ++nextCol) {
      bool allSpaces = true;
      for (const auto & row : grid) {
        if (row.size() <= nextCol || row[nextCol] == ' ') {
          // do nothing
        } else {
          allSpaces = false;
          break;
        }
      }
      if (allSpaces) {
        return nextCol;
      }
    }
    return static_cast<int>(grid[0].size());
  }

  char findCurrentOperation(const int col) const {
    const int maxCol = nextSpace(col);
    for (int ccol = col; ccol < maxCol; ++ccol) {
      if (grid[grid.size() - 1][ccol] == '*') return '*';
      if (grid[grid.size() - 1][ccol] == '+') return '+';
    }
    cout << "No operation found between cols " << col << " and " << maxCol << endl;
    exit(1);
  }

  LL processData2() const {
    LL result = 0;
    int col = 0;
    while (col < grid[0].size()) {
      const int maxCol = nextSpace(col);
      const char operation = findCurrentOperation(col);
      if (operation == '*') {
        LL cur = 1;
        for (int ccol = col; ccol < maxCol; ++ccol) {
          LL num = 0;
          for (int row = 0; row < grid.size() - 1; ++row) {
            if (grid[row].size() <= ccol || grid[row][ccol] == ' ') {
              // do nothing
            } else {
              num = num * 10 + (grid[row][ccol] - '0');
            }
          }
          cur *= num;
        }
        result += cur;
      } else {
        LL cur = 0;
        for (int ccol = col; ccol < maxCol; ++ccol) {
          LL num = 0;
          for (int row = 0; row < grid.size() - 1; ++row) {
            if (grid[row].size() <= ccol || grid[row][ccol] == ' ') {
              // do nothing
            } else {
              num = num * 10 + (grid[row][ccol] - '0');
            }
          }
          cur += num;
        }
        result += cur;
      }
      col = maxCol + 1;
    }
    return result;

  }

  LL processData() const {
    const size_t numberOfCalculations = data[0].size();
    LL result = 0;
    for (int i = 0;i < numberOfCalculations; ++i) {
      string operation = data[data.size() - 1][i];
      if (operation == "*") {
        LL cur = stoll(data[0][i]);
        for (int j = 1;j < data.size() - 1; ++j) {
          cur *= stoll(data[j][i]);
        }
        result += cur;
      } else if (operation == "+") {
        LL cur = stoll(data[0][i]);
        for (int j = 1;j < data.size() - 1; ++j) {
          cur += stoll(data[j][i]);
        }
        result += cur;
      } else {
        cout << "Unknown operation: " << operation << endl;
        exit(1);
      }
    }
    return result;
  }

  LL solution() {
    data.clear();
    grid.clear();
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      grid.emplace_back();
      for (char &c : line) {
        grid[grid.size() - 1].push_back(c);
      }

      stringstream ss(line);
      string token;
      vector<string> tokens;
      while (ss >> token) {
        tokens.push_back(token);
      }
      data.push_back(tokens);
    }
    return processData2();
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
