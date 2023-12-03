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

  static bool isGear(char c) {
    return c == '*';
  }

  static vector<PII> symbolAdjacent(vector<vector<char> > &grid, int x, int y) {
    vector<PII> result;
    for (auto &d: ds) {
      int newX = x + d.first;
      int newY = y + d.second;
      if (newX >= 0 && newX < grid.size() && newY >= 0 && newY < grid[newX].size() && isGear(grid[newX][newY])) {
        result.emplace_back(newX, newY);
      }
    }
    return result;
  }

  static int solution() {
    vector<vector<char> > grid;
    map<PII, vector<int>> gearUse;
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
      set<PII> isSymbolAdjacent;
      for (int j = 0; j < grid[i].size(); j++) {
        if (isDigit(grid[i][j])) {
          currentNumber += grid[i][j];
          vector<PII> symbols = symbolAdjacent(grid, i, j);
          for (const auto &symbol: symbols) {
            isSymbolAdjacent.insert(symbol);
          }
          if (j == grid[i].size() - 1) {
            int currentNum = stoi(currentNumber);
            for (const auto &it: isSymbolAdjacent) {
              gearUse[it].push_back(currentNum);
            }
          }
        } else {
          if (!currentNumber.empty()) {
            int currentNum = stoi(currentNumber);
            for (const auto &it: isSymbolAdjacent) {
              gearUse[it].push_back(currentNum);
            }
            currentNumber = "";
            isSymbolAdjacent.clear();
          }
        }
      }
    }
    for (auto &it: gearUse) {
      vector<int> &v = it.second;
      if (v.size() == 2) {
        result += v[0] * v[1];
      }
    }
    return result;
  }
};

int main() {
  cout << Assignment::solution() << endl;
}
