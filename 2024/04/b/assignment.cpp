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
  vector<vector<char> > grid;

  [[nodiscard]] int xmasTimes() const {
    int result = 0;
    for (int x = 1; x + 1 < grid.size(); ++x) {
      for (int y = 1; y + 1 < grid[0].size(); ++y) {
        if (grid[x][y] != 'A') continue;
        const char tl = grid[x - 1][y - 1];
        const char tr = grid[x - 1][y + 1];
        const char bl = grid[x + 1][y - 1];
        const char br = grid[x + 1][y + 1];

        if (tl == 'A' || tr == 'A' || bl == 'A' || br == 'A') continue;
        if (tl == 'X' || tr == 'X' || bl == 'X' || br == 'X') continue;
        if (tl == br || tr == bl) continue;
        ++result;
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
