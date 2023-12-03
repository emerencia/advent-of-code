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

vector<PII> ds = {{1,  0},
                  {1,  -1},
                  {0,  -1},
                  {-1, -1},
                  {-1, 0},
                  {-1, 1},
                  {0,  1},
                  {1,  1}};

class Assignment {
public:

  static bool isDigit(char c) {
    return c >= '0' && c <= '9';
  }

  static bool isSymbol(char c) {
    return (!isDigit(c) && c != '.');
  }

  static bool symbolAdjacent(vector<vector<char> > &grid, int x, int y) {
    for (auto &d: ds) {
      int newX = x + d.first;
      int newY = y + d.second;
      if (newX >= 0 && newX < grid.size() && newY >= 0 && newY < grid[newX].size() && isSymbol(grid[newX][newY])) {
        return true;
      }
    }
    return false;
  }

  static int solution() {
    vector<vector<char> > grid;
    int result = 0;
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      grid.emplace_back();
      for (char i: line) {
        grid.back().push_back(i);
      }
    }
    for (int i = 0; i < grid.size(); i++) {
      string currentNumber;
      bool isSymbolAdjacent = false;
      for (int j = 0; j < grid[i].size(); j++) {
        if (isDigit(grid[i][j])) {
          currentNumber += grid[i][j];
          if (!isSymbolAdjacent) {
            isSymbolAdjacent = symbolAdjacent(grid, i, j);
          }
          if (j == grid[i].size() - 1) {
            if (isSymbolAdjacent) {
              result += stoi(currentNumber);
            }
          }
        } else {
          if (!currentNumber.empty()) {
            if (isSymbolAdjacent) {
              result += stoi(currentNumber);
            }
            currentNumber = "";
            isSymbolAdjacent = false;
          }
        }
      }
    }
    return result;
  }
};

int main() {
  cout << Assignment::solution() << endl;
}
