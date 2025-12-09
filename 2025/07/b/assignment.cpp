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
  vector<vector<char>> grid;
public:

  bool withinRange(const int i, const int j) const {
    return i >= 0 && i < grid.size() && j >= 0 && j < grid[0].size();
  }

  LL numberOfSplits() {
    // get the location of 'S' in the first line
    vector<char> vc = grid[0];
    vector<vector<LL>> dp(grid.size(), vector<LL>(grid[0].size(), 0LL));
    const int pos = find(vc.begin(), vc.end(), 'S') - vc.begin();
    grid[0][pos] = '|';
    dp[0][pos] = 1LL;
    for (int i = 1; i < grid.size(); i++) {
      for (int j=0;j<grid[0].size();j++) {
        if (grid[i-1][j] == '|') {
          if (grid[i][j] == '^') {
            if (withinRange(i, j-1) && (grid[i][j-1] == '.' || grid[i][j-1] == '|')) {
              grid[i][j-1] = '|';
              dp[i][j-1] += dp[i-1][j];
            }
            if (withinRange(i, j+1) && (grid[i][j+1] == '.' || grid[i][j+1] == '|')) {
              grid[i][j+1] = '|';
              dp[i][j+1] += dp[i-1][j];
            }
          } else if (grid [i][j] == '.' || grid[i][j] == '|') {
            grid[i][j] = '|';
            dp[i][j] += dp[i-1][j];
          }
        }
      }
    }
    LL result = 0;
    for (int j = 0; j < grid[0].size(); j++) {
      result += dp[grid.size()-1][j];
    }
    return result;
  }

  LL solution() {
    grid.clear();
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      // read the grid
      grid.push_back(vector<char>(line.begin(), line.end()));
    }
    return numberOfSplits();
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
