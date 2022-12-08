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

  bool visibleFromTop(vector<vector<int> >& grid, int x, int y) {
    for (int i = 0; i < x; i++) {
      if (grid[i][y] >= grid[x][y]) return false;
    }
    return true;
  }

  bool visibleFromBottom(vector<vector<int> > &grid, int x, int y) {
    for (int i = x + 1; i < grid.size(); i++) {
      if (grid[i][y] >= grid[x][y]) return false;
    }
    return true;
  }

  bool visibleFromLeft(vector<vector<int> > &grid, int x, int y) {
    for (int j = 0; j < y; j++) {
      if (grid[x][j] >= grid[x][y]) return false;
    }
    return true;
  }

  bool visibleFromRight(vector<vector<int> > &grid, int x, int y) {
    for (int j = y + 1; j < grid[x].size(); j++) {
      if (grid[x][j] >= grid[x][y]) return false;
    }
    return true;
  }

  bool scenicScore(vector<vector<int> >& grid, int x, int y) {
    return visibleFromTop(grid, x, y) ||
        visibleFromBottom(grid, x, y) ||
        visibleFromLeft(grid, x, y) ||
        visibleFromRight(grid, x, y);
  }

  int visibleTrees(vector<vector<int> >& grid) {
    int result = 0;
    for (int i = 0; i < grid.size();i++) {
      for (int j = 0; j < grid[i].size(); j++) {
        result += isVisible(grid, i, j);
      }
    }
    return result;
  }

  int solution() {
    vector<vector<int> > grid;
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      grid.push_back(vector<int>());
      for (int i = 0; i < line.size(); i++) {
        grid[grid.size() - 1].push_back(line[i] - '0');
      }
    }
    return visibleTrees(grid);
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
