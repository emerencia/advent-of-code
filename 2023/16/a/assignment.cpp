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
typedef pair<pair<int, int>, int> PIII;

const vector<PII> ds = {{1,  0},
                        {0,  1},
                        {-1, 0},
                        {0,  -1}};

const int UP = 2;
const int DOWN = 0;
const int LEFT = 3;
const int RIGHT = 1;

class Assignment {
public:
  vector<vector<char>> grid;
  set<PIII> seen;
  set<PII> energizedTiles;

  bool outOfBounds(int row, int col) {
    return row < 0 || row >= grid.size() || col < 0 || col >= grid[0].size();
  }

  void energizeTiles() {
    // keep a seen state of coord and direction of light
    queue<PIII> q;
    seen.clear();
    energizedTiles.clear();
    q.push({{0, 0}, RIGHT});
    while (!q.empty()) {
      PIII p = q.front();
      q.pop();
      int crow = p.first.first;
      int ccol = p.first.second;
      int cdir = p.second;

      if (outOfBounds(crow, ccol)) {
        // do nothing
        continue;
      }

      if (seen.find(p) != seen.end()) continue;
      seen.insert(p);
      if (energizedTiles.find({crow, ccol}) == energizedTiles.end()) {
        energizedTiles.insert({crow, ccol});
      }

      char c = grid[crow][ccol];
      // separate based on what the tile is, five possibilities:
      switch (c) {
        case '.':
          // continue in the same direction.
          q.push({{crow + ds[cdir].first, ccol + ds[cdir].second}, cdir});
          break;
        case '|':
          // if coming from right or left, split up and down
          if (cdir == RIGHT || cdir == LEFT) {
            q.push({{crow + ds[UP].first, ccol + ds[UP].second}, UP});
            q.push({{crow + ds[DOWN].first, ccol + ds[DOWN].second}, DOWN});
          } else {
            // otherwise, continue in the same direction
            q.push({{crow + ds[cdir].first, ccol + ds[cdir].second}, cdir});
          }
          break;
        case '-':
          // if coming from up or down, split left and right
          if (cdir == UP || cdir == DOWN) {
            q.push({{crow + ds[LEFT].first, ccol + ds[LEFT].second}, LEFT});
            q.push({{crow + ds[RIGHT].first, ccol + ds[RIGHT].second}, RIGHT});
          } else {
            // otherwise, continue in the same direction
            q.push({{crow + ds[cdir].first, ccol + ds[cdir].second}, cdir});
          }
          break;
        case '/':
          // if going right, go up. if going down, go left. if going left, go down. if going up, go right.
          if (cdir == RIGHT) {
            q.push({{crow + ds[UP].first, ccol + ds[UP].second}, UP});
          } else if (cdir == DOWN) {
            q.push({{crow + ds[LEFT].first, ccol + ds[LEFT].second}, LEFT});
          } else if (cdir == LEFT) {
            q.push({{crow + ds[DOWN].first, ccol + ds[DOWN].second}, DOWN});
          } else if (cdir == UP) {
            q.push({{crow + ds[RIGHT].first, ccol + ds[RIGHT].second}, RIGHT});
          }
          break;
        case '\\':
          // if going right, go down. if going down, go right. if going left, go up. if going up, go left.
          if (cdir == RIGHT) {
            q.push({{crow + ds[DOWN].first, ccol + ds[DOWN].second}, DOWN});
          } else if (cdir == DOWN) {
            q.push({{crow + ds[RIGHT].first, ccol + ds[RIGHT].second}, RIGHT});
          } else if (cdir == LEFT) {
            q.push({{crow + ds[UP].first, ccol + ds[UP].second}, UP});
          } else if (cdir == UP) {
            q.push({{crow + ds[LEFT].first, ccol + ds[LEFT].second}, LEFT});
          }
          break;
        default:
          cout << "ERROR: unknown character " << c << endl;
          exit(1);
      }
    }
  }

  int solution() {
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
    energizeTiles();
    return (int) energizedTiles.size();
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
