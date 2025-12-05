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

vector<PII> ds({{-1,  1},
                {-1,  0},
                {-1, -1},
                {0,  -1},
                {1,  -1},
                {1,  0},
                {1,  1},
                {0,  1}});

class Assignment {
public:
  vector<string> grid;
  vector<string> newGrid;
  int width;
  int height;

  int accessibleRolls() {
    int result = 0;
    int removedRolls = -1;
    while (removedRolls != 0) {
      removedRolls = 0;
      newGrid = grid;
      for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
          if (grid[i][j] == '@') {
            int adjacentRolls = 0;
            for (int d = 0; d < ds.size(); d++) {
              int ni = i + ds[d].first;
              int nj = j + ds[d].second;
              if (ni >= 0 && ni <= height && nj >= 0 && nj <= width && grid[ni][nj] == '@') {
                adjacentRolls += 1;
              }
            }
            if (adjacentRolls < 4) {
              newGrid[i][j] = '.';
              removedRolls++;
            }
          }
        }
      }
      grid = newGrid;
      result += removedRolls;
    }
    return result;
  }

  int solution() {
    grid.clear();
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      grid.push_back(line);
    }
    width = grid[0].size() - 1;
    height = grid.size() - 1;
    newGrid = grid;
    return accessibleRolls();
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
