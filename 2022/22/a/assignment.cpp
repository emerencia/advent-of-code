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


// row, column

vector<PII> ds({{0,  1},
                {1,  0},
                {0,  -1},
                {-1, 0}});
vector<string> grid;


class Assignment {
public:
  int walk(int row, int col, int di, const string &password, const vector<vector<vector<PII>>> &next) {
    int pIdx = 0;
    while (pIdx < password.size()) {
      if (password[pIdx] == 'R') {
        di = (di + 1) % 4;
        pIdx++;
      } else if (password[pIdx] == 'L') {
        di = (di + 3) % 4;
        pIdx++;
      } else {
        string num;
        while (pIdx < password.size() && password[pIdx] >= '0' && password[pIdx] <= '9') {
          num += password[pIdx++];
        }
        stringstream s(num);
        int steps;
        s >> steps;
        for (int i = 0; i < steps; i++) {
          PII nextpos = next[row][col][di];

          // you can add error cecking here that it is never oob or spcce
          if (grid[nextpos.first][nextpos.second] == '.') {
            row = nextpos.first;
            col = nextpos.second;
          } else {
            break;
          }
        }
      }
    }
    return 1000 * (row + 1) + 4 * (col + 1) + di;
  }

  int solution() {
    int maxlength = 0;
    string password;
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      if (line[0] >= '0' && line[0] <= '9') {
        password = line;
      } else {
        grid.push_back(line);
      }
      maxlength = max((size_t) maxlength, line.size());
    }
    vector<vector<vector<PII>>> next(grid.size(), vector<vector<PII>>(maxlength, vector<PII>(4, {-1, -1})));
    for (int i = 0; i < grid.size(); i++) {
      int firstpos = -1;
      for (int j = 0; j < grid[i].size(); j++) {
        if (grid[i][j] == ' ') continue;
        if (firstpos == -1) {
          firstpos = j;
          break;
        }
      }
      int lastpos = -1;
      for (int j = grid[i].size() - 1; j >= 0; j--) {
        if (grid[i][j] == ' ') continue;
        if (lastpos == -1) {
          lastpos = j;
          break;
        }
      }
      for (int j = 0; j < grid[i].size(); j++) {
        if (grid[i][j] == ' ') continue;
        for (int k = 0; k < 3; k += 2) {
          if (j == firstpos && k == 2) {
            next[i][j][k] = {i, lastpos};
          } else if (j == lastpos && k == 0) {
            next[i][j][k] = {i, firstpos};
          } else {
            next[i][j][k] = {i + ds[k].first, j + ds[k].second};
          }
        }
      }
    }
    for (int j = 0; j < maxlength; j++) {
      // check if j within limits
      int firstpos = -1;
      for (int i = 0; i < grid.size(); i++) {
        if (j >= grid[i].size() || grid[i][j] == ' ') continue;
        if (firstpos == -1) {
          firstpos = i;
          break;
        }
      }
      int lastpos = -1;
      for (int i = grid.size() - 1; i >= 0; i--) {
        if (j >= grid[i].size() || grid[i][j] == ' ') continue;
        if (lastpos == -1) {
          lastpos = i;
          break;
        }
      }
      for (int i = 0; i < grid.size(); i++) {
        if (j >= grid[i].size() || grid[i][j] == ' ') continue;
        for (int k = 1; k < 4; k += 2) {
          if (i == firstpos && k == 3) {
            next[i][j][k] = {lastpos, j};
          } else if (i == lastpos && k == 1) {
            next[i][j][k] = {firstpos, j};
          } else {
            next[i][j][k] = {i + ds[k].first, j + ds[k].second};
          }
        }
      }
    }

    int firstopen = -1;
    for (int j = 0; j < grid[0].size(); j++) {
      if (grid[0][j] == ' ') continue;
      firstopen = j;
      break;
    }

    return walk(0, firstopen, 0, password, next);
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
