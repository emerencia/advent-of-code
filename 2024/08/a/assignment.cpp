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
  vector<vector<char> > grid;
  int maxRow{}, maxCol{};
  map<char, vector<PII> > pos;
  set<PII> antinodes;

  [[nodiscard]] bool outOfBounds(const PII &point) const {
    return point.first < 0 || point.first >= grid.size() || point.second < 0 || point.second >= grid[0].size();
  }

  int solution() {
    grid.clear();
    pos.clear();
    antinodes.clear();
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      stringstream ss(line);
      vector<char> row;
      char c;
      while (ss >> c) {
        row.push_back(c);
        if (c != '.') {
          pos[c].emplace_back(grid.size(), row.size() - 1);
        }
      }
      grid.push_back(row);
    }
    maxRow = static_cast<int>(grid.size());
    maxCol = static_cast<int>(grid[0].size());
    for (auto &[fst, snd]: pos) {
      vector<PII> v = snd;
      const int n = static_cast<int>(v.size());
      for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
          auto [p1fst, p1snd] = v[i];
          auto [p2fst, p2snd] = v[j];
          if (PII antinode1 = {2 * p1fst - p2fst, 2 * p1snd - p2snd}; !outOfBounds(antinode1)) {
            // grid[antinode1.first][antinode1.second] = '#';
            antinodes.insert(antinode1);
          }
          if (PII antinode2 = {2 * p2fst - p1fst, 2 * p2snd - p1snd}; !outOfBounds(antinode2)) {
            // grid[antinode2.first][antinode2.second] = '#';
            antinodes.insert(antinode2);
          }
        }
      }
    }
    return static_cast<int>(antinodes.size());
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
