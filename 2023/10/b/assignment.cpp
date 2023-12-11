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

// row, col
typedef pair<int, int> PII;

const int UP = 0;
const int RIGHT = 1;
const int DOWN = 2;
const int LEFT = 3;

const vector<PII> directions = {
    {-1, 0}, // UP
    {0,  1},  // RIGHT
    {1,  0},  // DOWN
    {0,  -1}, // LEFT
};

const vector<map<char, int>> allowedMoves = {
    {{'|', UP},    {'7', LEFT},  {'F', RIGHT}}, // going to UP
    {{'-', RIGHT}, {'7', DOWN},  {'J', UP}}, // going to RIGHT
    {{'|', DOWN},  {'L', RIGHT}, {'J', LEFT}}, // going to DOWN
    {{'-', LEFT},  {'F', DOWN},  {'L', UP}}, // going to LEFT
};

const map<char, vector<bool> > canApproachFromDirection = {
    //      UP, RIGHT, DOWN, LEFT
    {'|', {true,  false, true,  false}},
    {'-', {false, true,  false, true}},
    {'L', {false, false, true,  true}},
    {'J', {false, true,  true,  false}},
    {'7', {true,  true,  false, false}},
    {'F', {true,  false, false, true}},
};

class Assignment {
public:
  vector<vector<char>> grid;
  set<PII> seenPos;

  bool withinLimits(PII pos) {
    if (grid.empty()) return false;

    return pos.first >= 0 && pos.first < grid.size() && pos.second >= 0 && pos.second < grid[0].size();
  }

  vector<int> findStartingDirections(PII pos) {
    vector<int> result;
    for (int i = 0; i < 4; i++) {
      PII newPos = {pos.first + directions[i].first, pos.second + directions[i].second};
      if (withinLimits(newPos)) {
        char newChar = grid[newPos.first][newPos.second];
        if (canApproachFromDirection.find(newChar) != canApproachFromDirection.end() &&
            canApproachFromDirection.at(newChar)[i]) {
          result.push_back(i);
        }
      }
    }
    return result;
  }

  char determineStartingSymbol(int startRow, int startCol) {
    vector<int> dirs = findStartingDirections({startRow, startCol});
    if (dirs.size() != 2) {
      cout << "ERROR: dirs.size() != 2, it is " << dirs.size() << endl;
      for (int i = 0; i < dirs.size(); ++i) {
        cout << "curdir " << i << ": " << dirs[i] << endl;
      }
      exit(1);
    }
    // convert dirs to a set
    set<int> dirsSet(dirs.begin(), dirs.end());
    if (dirsSet.find(LEFT) != dirsSet.end() && dirsSet.find(DOWN) != dirsSet.end()) {
      return '7';
    }
    if (dirsSet.find(RIGHT) != dirsSet.end() && dirsSet.find(DOWN) != dirsSet.end()) {
      return 'F';
    }
    if (dirsSet.find(UP) != dirsSet.end() && dirsSet.find(RIGHT) != dirsSet.end()) {
      return 'L';
    }
    if (dirsSet.find(UP) != dirsSet.end() && dirsSet.find(LEFT) != dirsSet.end()) {
      return 'J';
    }
    if (dirsSet.find(UP) != dirsSet.end() && dirsSet.find(DOWN) != dirsSet.end()) {
      return '|';
    }
    if (dirsSet.find(LEFT) != dirsSet.end() && dirsSet.find(RIGHT) != dirsSet.end()) {
      return '-';
    }
    cout << "ERROR: Unknown dirsections: " << dirs[0] << ", " << dirs[1] << endl;
    exit(1);
  }

  void stepsToFarthestPoint(int startRow, int startCol) {
    // we go in both directions simultaneously.
    vector<PII> curPos = {{startRow, startCol},
                          {startRow, startCol}};
    vector<int> curDir = findStartingDirections({startRow, startCol});
    if (curDir.size() != 2) {
      cout << "ERROR: curDir.size() != 2, it is " << curDir.size() << endl;
      for (int i = 0; i < curDir.size(); ++i) {
        cout << "curdir " << i << ": " << curDir[i] << endl;
      }
      exit(1);
    }
    seenPos.insert({startRow, startCol});
    bool found = false;
    while (true) {
      for (int i = 0; i < 2; ++i) {
        PII pos = curPos[i];
        int dir = curDir[i];
        PII newPos = {pos.first + directions[dir].first, pos.second + directions[dir].second};
        if (!withinLimits(newPos)) {
          cout << "ERROR: Not within limits: " << newPos.first << ", " << newPos.second << endl;
          exit(1);
        }
        if (seenPos.find(newPos) != seenPos.end()) {
          found = true;
          break;
        }
        char newChar = grid[newPos.first][newPos.second];
        const map<char, int> &allowed = allowedMoves[dir];
        if (allowed.find(newChar) == allowed.end()) {
          cout << "ERROR: Not allowed: " << newChar << endl;
          exit(1);
        }
        int newDir = allowed.at(newChar);
        curPos[i] = newPos;
        curDir[i] = newDir;
        seenPos.insert(newPos);
      }
      if (found) {
        break;
      }
    }
  }

  int solution() {
    grid.clear();
    seenPos.clear();
    int startRow = 0, startCol = 0;
    int result = 0;
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      vector<char> row;
      for (int i = 0; i < line.size(); ++i) {
        row.push_back(line[i]);
        if (line[i] == 'S') {
          startRow = (int)grid.size();
          startCol = i;
        }
      }
      grid.push_back(row);
    }
    stepsToFarthestPoint(startRow, startCol);
    // create a new grid with the same size as the original one.
    vector<vector<char>> newGrid(grid.size(), vector<char>(grid[0].size(), '.'));
    // fill the new grid with the seen positions.
    for (const auto &pos: seenPos) {
      newGrid[pos.first][pos.second] = grid[pos.first][pos.second];
    }
    // determine the actual symbol of the starting position.
    newGrid[startRow][startCol] = determineStartingSymbol(startRow, startCol);

    // scanline algorithm
    for (auto & row : newGrid) {
      // we start outside
      bool inside = false;
      // if the border is currently horizontal, we keep track of which side
      // (above or below) is inside the loop.
      bool aboveIsInside = false;
      for (char cur : row) {
        if (cur == '|') {
          inside = !inside;
        } else if (cur == '-') {
          // the border is horizontal, nothing changes.
        } else if (cur == 'L') {
          // we go under and around the L, approaching it from the left, so
          // if we are currently inside, then from now on, below is inside.
          aboveIsInside = !inside;
        } else if (cur == 'J') {
          // if above was inside, we cross a border here and are now outside.
          inside = !aboveIsInside;
        } else if (cur == '7') {
          // if above was inside, we are now inside.
          inside = aboveIsInside;
        } else if (cur == 'F') {
          // if we are currently inside, then now above is inside.
          aboveIsInside = inside;
        } else {
          if (cur != '.') {
            cout << "ERROR: Unknown symbol: " << cur << endl;
            exit(1);
          }
          if (inside) {
            result++;
          }
          // newGrid[row][cur] = inside ? 'I' : 'O';
        }
      }
    }

    /*
    for (int i = 0; i < newGrid.size(); ++i) {
      for (int j = 0; j < newGrid[i].size(); ++j) {
        cout << newGrid[i][j];
      }
      cout << endl;
    }
    */

    return result;
  }

};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
