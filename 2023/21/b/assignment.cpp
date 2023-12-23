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

const int NR_STEPS = 26501365;

class Assignment {
public:
  vector<vector<char>> grid;
  int startRow{};
  int startCol{};

  vector<LL> simulate(int maxSteps) {
    vector<LL> result = {0, 1};
    set<PII> current;
    set<PII> previous;
    current.insert({startRow, startCol});
    for (int i = 0; i < maxSteps; i++) {
      set<PII> newCurrent;
      for (auto p: current) {
        int row = p.first;
        int col = p.second;
        for (auto d: ds) {
          int nRow = row + d.first;
          int nCol = col + d.second;
          int modRow = nRow;
          while (modRow < 0) modRow += (int) grid.size();
          modRow %= (int) grid.size();
          int modCol = nCol;
          while (modCol < 0) modCol += (int) grid[0].size();
          modCol %= (int) grid[0].size();
          if (grid[modRow][modCol] != '#' && previous.find({nRow, nCol}) == previous.end()) {
            newCurrent.insert({nRow, nCol});
          }
        }
      }
      previous.clear();
      for (auto p: current) {
        previous.insert(p);
      }
      current = newCurrent;
      // We can reach everything that we could two steps ago plus what is currently on the boundary
      result.push_back(result[result.size() - 2] + (int) current.size());
    }
    return result;
  }

  static vector<LL> delta(vector<LL> a) {
    vector<LL> result;
    result.reserve(a.size() - 1);
    for (int i = 0; i < a.size() - 1; i++) {
      result.push_back(a[i + 1] - a[i]);
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

    // Calculate the first few grids out to get a feel for the speed of expansion.
    vector<LL> results = simulate((int) grid.size() * 5);
    vector<LL> newResults;
    // we are interested on how the results change when we go out a grid size farther.
    // The assumption is that the speed of expansion follows a quadratic function.
    for (int i = 1 + (NR_STEPS % (int) grid.size()); i < results.size(); i += (int) grid.size()) {
      newResults.push_back(results[i]);
    }
    vector<LL> deltas = delta(newResults);
    vector<LL> deltas2 = delta(deltas);
    // deltas2 should be constant
    LL c = newResults[0];
    LL b = deltas[0];
    LL a = deltas2[0] / 2;
    LL x = NR_STEPS / (int) grid.size();
    LL result = a * x * (x - 1) + b * x + c;
    return result;
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
