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
typedef tuple<LL, int, int> PIII;

vector<PII> directions = {{0, 1},
                          {1,  0},
                          {0,  -1},
                          {-1,  0}};

class Assignment {
  vector<PII> redTiles;
  vector<int> rows;
  vector<int> columns;
  set<PII> tiles;
  vector<PII> boundingBox;
public:

  LL solution() {
    redTiles.clear();
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      int row, col;
      sscanf(line.c_str(), "%d,%d", &row, &col);

      tiles.insert({row, col});
      redTiles.emplace_back(row, col);
      rows.push_back(row);
      columns.push_back(col);
    }
    // sort rows and columns
    sort(rows.begin(), rows.end());
    sort(columns.begin(), columns.end());

    PII first = {-1, -1};

    for (int ri = 0;ri < rows.size();ri++) {
      for (int ci = 0;ci < columns.size();ci++) {
        int row = rows[ri];
        int col = columns[ci];
        if (tiles.find({row, col}) == tiles.end()) continue;

        if (first.first == -1) {
          first = {ri, ci};
        }
      }
    }

    int found = 1;
    PII cur = first;
    while (found < redTiles.size()) {
      PII start = cur;
      bool foundOne = false;
      for (int d = 0;d< directions.size();d++) {
        cur = start;
        for (int i = 0;i < redTiles.size();i++) {
          cur = {cur.first + directions[d].first, cur.second + directions[d].second};
          if (cur.first < 0 || cur.first >= rows.size() ||
              cur.second < 0 || cur.second >= columns.size()) {
            break;
          }
          if (tiles.find({rows[cur.first], columns[cur.second]}) != tiles.end()) {
            foundOne = true;
            break;
          }
        }
        if (foundOne) {
          break;
        }
      }
      if (foundOne) {
        found++;
        boundingBox.push_back({rows[cur.first], columns[cur.second]});
      }
    }

    return 0;
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
