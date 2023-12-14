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

  int calcNorthRoll() {
    int result = 0;
    // do it per column
    for (int col = 0; col < grid[0].size(); col++) {
      int lastFixed = -1;
      for (int row = 0; row < grid.size(); row++) {
        if (grid[row][col] == 'O') {
          // move it after lastFixed.
          result += (int) grid.size() - (lastFixed + 1);
          lastFixed += 1;
        } else if (grid[row][col] == '#') {
          lastFixed = row;
        }
      }
    }
    return result;
  }

  int solution() {
    int result = 0;
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
    result += calcNorthRoll();
    return result;
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
