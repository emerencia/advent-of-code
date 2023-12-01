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

vector<PII> ds = {{1,  0},
                  {0,  1},
                  {-1, 0},
                  {0,  -1},
                  {0,  0}}; // {0,0} because can also stay in place

// row, col
class Assignment {
public:
  vector<string> grid;
  int width;
  int height;
  int endRow;
  int endCol;

  bool isFree(int row, int col, int minutesSpent) {
    // if out of bounds then false;
    if (row < 0 || row >= grid.size()) return false;
    // if is end pos then true
    if (row == endRow && col == endCol) return true;
    // if is start pos then true
    if (row == 0 && col == 1) return true;
    // if is wall then false
    if (grid[row][col] == '#') return false;
    // otherwise, calc blizzards from each direction at this point
    int startingColFromLeft = 1 + (((col - 1) - minutesSpent + minutesSpent * width) % width);
    if (grid[row][startingColFromLeft] == '>') return false;
    int startingColFromRight = 1 + (((col - 1) + minutesSpent) % width);
    if (grid[row][startingColFromRight] == '<') return false;
    int startingRowFromTop = 1 + (((row - 1) - minutesSpent + minutesSpent * height) % height);
    if (grid[startingRowFromTop][col] == 'v') return false;
    int startingRowFromBottom = 1 + (((row - 1) + minutesSpent) % height);
    if (grid[startingRowFromBottom][col] == '^') return false;
    return true;
  }

  int minStepsToEnd(int minutesSpent, int row, int col) {
    int best = -1;
    queue<PIII> q;
    set<PIII> seen;
    endRow = grid.size() - 1;
    endCol = grid[endRow].size() - 2;
    q.push({{row, col}, minutesSpent});
    while (!q.empty()) {
      PIII p = q.front();
      q.pop();
      int crow = p.first.first;
      int ccol = p.first.second;
      int cminutesSpent = p.second;
      // if we already found a time, and we're above it: exit
      if (best != -1 && cminutesSpent >= best) continue;
      if (seen.find(p) != seen.end()) continue;
      seen.insert(p);
      // check if we reached the end
      if (crow == endRow && ccol == endCol) {
        if (best == -1) {
          best = cminutesSpent;
        } else {
          best = min(best, cminutesSpent);
        }
      }
      // go in directions
      for (int i = 0; i < ds.size(); i++) {
        int newRow = crow + ds[i].first;
        int newCol = ccol + ds[i].second;
        if (isFree(newRow, newCol, cminutesSpent + 1))
          q.push({{newRow, newCol}, cminutesSpent + 1});
      }
    }
    return best;
  }

  int solution() {
    grid.clear();
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      grid.push_back(line);
    }
    width = grid[0].size() - 2;
    height = grid.size() - 2;
    return minStepsToEnd(0, 0, 1);
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
