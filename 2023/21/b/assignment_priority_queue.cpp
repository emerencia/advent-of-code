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
typedef pair<int, pair<int, int>> PIII;

const vector<PII> ds = {{-1, 0},
                        {1,  0},
                        {0,  -1},
                        {0,  1}};

const vector<int> nrSteps = {6, 10, 50, 100, 500, 1000, 5000};
// const vector<int> nrSteps = {1,2,3,4,5,6,7,8,9,10};

class Assignment {
public:
  vector<vector<char>> grid;
  int startRow{};
  int startCol{};

  LL simulateSteps(int maxSteps) {
    // reverse the order so we find the smallest stepsTaken first
    priority_queue<PIII, vector<PIII>, greater<>> q;
    set<PIII> seen;
    q.push({0, {startRow, startCol}});
    int result = 0;
    while (!q.empty()) {
      PIII p = q.top();
      q.pop();
      int row = p.second.first;
      int col = p.second.second;
      int stepsTaken = p.first;

      // if we see something now we know it was reached in less steps,
      // so whatever we can reach here, we could do there as well.
      // So just stop.
      if (seen.find({stepsTaken, {row, col}}) != seen.end()) continue;
      seen.insert({stepsTaken, {row, col}});
      if (stepsTaken == maxSteps) {
        result++;
        continue;
      }
      for (auto d: ds) {
        int nRow = row + d.first;
        int nCol = col + d.second;
        int modRow = nRow;
        while (modRow < 0) modRow += (int) grid.size();
        modRow %= (int) grid.size();
        int modCol = nCol;
        while (modCol < 0) modCol += (int) grid[0].size();
        modCol %= (int) grid[0].size();
        if (grid[modRow][modCol] != '#') {
          q.push({stepsTaken + 1, {nRow, nCol}});
        }
      }
    }
    return result;
  }

  LL solution() {
    startRow = -1;
    startCol = -1;
    grid.clear();
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      vector<char> row;
      for (char c: line) {
        if (c == 'S') {
          startRow = (int) grid.size();
          startCol = (int) row.size();
          c = '.';
        }
        row.push_back(c);
      }
      grid.push_back(row);
    }
    if (startRow == -1 || startCol == -1) {
      cout << "ERROR: start not found" << endl;
      exit(1);
    }
    for (auto steps : nrSteps) {
      cout << steps << ": " << simulateSteps(steps) << endl;
    }
    /*
    vector<int> results;
    for (int i = 0; i < 200; ++i) {
      cout << i << endl << flush;
      LL result = simulateSteps(nrSteps[i]);
      results.push_back(result);
    }
    // output the results as a c() list in R
    cout << "y <- c(";
    for (int i = 0; i < 200; ++i) {
      cout << results[i];
      if (i != 199) cout << ", ";
    }
    cout << ")" << endl;
    cout << "x <- 0:499" << endl;
    cout << "plot(x, y, type='l')" << endl;
    return -1;
    */
    return -1;
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
