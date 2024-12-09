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

vector<PII> ds = {
  {1, 0},
  {1, -1},
  {0, -1},
  {-1, -1},
  {-1, 0},
  {-1, 1},
  {0, 1},
  {1, 1}
};

string XMAS = "XMAS";

class Assignment {
public:
  vector<vector<char> > grid;

  [[nodiscard]] bool outofBounds(int row, int col) const {
    return row < 0 || row >= grid.size() || col < 0 || col >= grid[0].size();
  }

  [[nodiscard]] int xmasTimes() const {
    int result = 0;
    for (int x = 0; x < grid.size(); ++x) {
      for (int y = 0; y < grid[0].size(); ++y) {
        for (auto [dx, dy] : ds) {
          int cx = x;
          int cy = y;
          bool found = true;
          for (const char c: XMAS) {
            if (outofBounds(cx, cy) || grid[cx][cy] != c) {
              found = false;
              break;
            }
            cx += dx;
            cy += dy;
          }
          result += found;
        }
      }
    }
    return result;
  }

  int solution() {
    grid.clear();
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      stringstream ss(line);
      vector<char> row;
      char c;
      while (ss >> c) {
        row.push_back(c);
      }
      grid.push_back(row);
    }
    return xmasTimes();
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
