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

const int cyclesToDo = 1000000000;

class Assignment {
public:
  vector<vector<char>> grid;

  int calcNorthSupport() {
    int result = 0;
    for (int row = 0; row < grid.size(); row++) {
      int weight = (int) grid.size() - row;
      for (int col = 0; col < grid[0].size(); col++) {
        if (grid[row][col] == 'O') {
          result += weight;
        }
      }
    }
    return result;
  }

  void doNorthRoll() {
    // do it per column
    for (int col = 0; col < grid[0].size(); col++) {
      int lastFixed = -1;
      for (int row = 0; row < grid.size(); row++) {
        if (grid[row][col] == 'O') {
          if (lastFixed + 1 < row) {
            grid[lastFixed + 1][col] = 'O';
            grid[row][col] = '.';
            lastFixed += 1;
          } else {
            lastFixed = row;
          }
        } else if (grid[row][col] == '#') {
          lastFixed = row;
        }
      }
    }
  }

  void doWestRoll() {
    // do it per row
    for (auto &row: grid) {
      int lastFixed = -1;
      for (int col = 0; col < grid[0].size(); col++) {
        if (row[col] == 'O') {
          if (lastFixed + 1 < col) {
            row[lastFixed + 1] = 'O';
            row[col] = '.';
            lastFixed += 1;
          } else {
            lastFixed = col;
          }
        } else if (row[col] == '#') {
          lastFixed = col;
        }
      }
    }
  }

  void doSouthRoll() {
    // do it per column
    for (int col = 0; col < grid[0].size(); col++) {
      int lastFixed = (int) grid.size();
      for (int row = (int) grid.size() - 1; row >= 0; row--) {
        if (grid[row][col] == 'O') {
          if (lastFixed - 1 > row) {
            grid[lastFixed - 1][col] = 'O';
            grid[row][col] = '.';
            lastFixed -= 1;
          } else {
            lastFixed = row;
          }
        } else if (grid[row][col] == '#') {
          lastFixed = row;
        }
      }
    }
  }

  void doEastRoll() {
    // do it per row
    for (auto &row: grid) {
      int lastFixed = (int) grid[0].size();
      for (int col = (int) grid[0].size() - 1; col >= 0; col--) {
        if (row[col] == 'O') {
          if (lastFixed - 1 > col) {
            row[lastFixed - 1] = 'O';
            row[col] = '.';
            lastFixed -= 1;
          } else {
            lastFixed = col;
          }
        } else if (row[col] == '#') {
          lastFixed = col;
        }
      }
    }
  }

  set<PII> calculateState() {
    set<PII> result;
    for (int row = 0; row < grid.size(); row++) {
      for (int col = 0; col < grid[0].size(); col++) {
        if (grid[row][col] == 'O') {
          result.insert(make_pair(row, col));
        }
      }
    }
    return result;
  }

  void doRollCycle() {
    doNorthRoll();
    doWestRoll();
    doSouthRoll();
    doEastRoll();
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

    int iteration = 1;
    int seenAtIteration;
    map<set<PII>, int> seenStates;
    while (true) {
      doRollCycle();
      set<PII> state = calculateState();
      if (seenStates.find(state) != seenStates.end()) {
        seenAtIteration = seenStates[state];
        break;
      }
      seenStates[state] = iteration;
      iteration++;
    }
    int cycleSize = iteration - seenAtIteration;
    cout << "repeat found at iteration " << seenAtIteration << endl;
    cout << "cyclesize " << cycleSize << endl;
    int cyclesRemaining = (cyclesToDo - seenAtIteration) % cycleSize;
    cout << "cycles remaining " << cyclesRemaining << endl;
    for (int i = 0; i < cyclesRemaining; i++) {
      doRollCycle();
    }
    result += calcNorthSupport();
    return result;
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
