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

  int shortestToEnd(PII cur, PII end, int timeToGetHere, vector<vector<char>> &grid, vector<vector<int>>& timesToGetHere) {
    if (timesToGetHere[cur.first][cur.second] != -1 && timeToGetHere >= timesToGetHere[cur.first][cur.second]) return INT_MAX/2;
    timesToGetHere[cur.first][cur.second] = timeToGetHere;

    if (cur.first == end.first && cur.second == end.second) {
      return 0;
    }
    char currentHeight = grid[cur.first][cur.second];
    int result = INT_MAX / 2;

    // try left
    if (cur.first > 0 && grid[cur.first - 1][cur.second] <= currentHeight + 1) {
      result = min(result, 1 + shortestToEnd({cur.first - 1, cur.second}, end, timeToGetHere + 1, grid,
                                             timesToGetHere));
    }
    // try right
    if (cur.first + 1 < grid.size() && grid[cur.first + 1][cur.second] <= currentHeight + 1) {
      result = min(result, 1 + shortestToEnd({cur.first + 1, cur.second}, end, timeToGetHere + 1, grid,
                                             timesToGetHere));
    }
    // try up
    if (cur.second > 0 && grid[cur.first][cur.second - 1] <= currentHeight + 1) {
      result = min(result, 1 + shortestToEnd({cur.first, cur.second - 1}, end, timeToGetHere + 1, grid,
                                             timesToGetHere));
    }
    // try down
    if (cur.second + 1 < grid[cur.first].size() && grid[cur.first][cur.second + 1] <= currentHeight + 1) {
      result = min(result, 1 + shortestToEnd({cur.first, cur.second + 1}, end, timeToGetHere + 1, grid,
                                             timesToGetHere));
    }

    return result;
  }

  int solution() {
    vector<vector<char>> grid;
    PII end = {-1, -1};
    int idx = 0;
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      if (line.find('S') != string::npos) {
        replace(line.begin(), line.end(), 'S', 'a');
      }
      if (line.find('E') != string::npos) {
        end = {idx, line.find('E')};
        replace(line.begin(), line.end(), 'E', 'z');
      }
      vector<char> row;
      for (int i = 0;i<line.size();i++) {
        row.push_back(line[i]);
      }
      grid.push_back(row);
      idx++;
    }
    vector<vector<int>> timesToGetHere(grid.size());
    for (int i=0;i<grid.size();i++) {
      for (int j = 0; j < grid[0].size(); j++) {
        timesToGetHere[i].push_back(-1);
      }
    }

    int result = INT_MAX/2;
    for (int i=0;i<grid.size();i++) {
      for (int j =0;j<grid[i].size();j++) {
        if (grid[i][j] == 'a') {
          for (int x = 0; x < grid.size(); x++) {
            for (int y = 0; y < grid[0].size(); y++) {
              timesToGetHere[x][y] = -1;
            }
          }
          result = min(result, shortestToEnd({i,j}, end, 0, grid, timesToGetHere));
        }
      }
    }
    return result;
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
