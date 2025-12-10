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
constexpr int GRID_SIZE = 100;
char grid2[GRID_SIZE][GRID_SIZE];

vector<PII> directions = {{0, 1},
                          {1,  0},
                          {0,  -1},
                          {-1,  0}};

class Assignment {
  vector<PII> redTiles;
  vector<int> rows;
  vector<int> columns;
  set<PII> tiles;
public:

  LL largestArea() const {
    priority_queue<PIII, vector<PIII>, less<>> q;
    for (int i = 0; i < redTiles.size(); i++) {
      for (int j = i+1;j < redTiles.size();j++) {
        for (int k = 0; k < redTiles.size(); k++) {
          if (k == i || k == j) continue;
          // k has to match i in row and j in col, or vice versa
          if (!((redTiles[k].first == redTiles[i].first && redTiles[k].second == redTiles[j].second) ||
                (redTiles[k].first == redTiles[j].first && redTiles[k].second == redTiles[i].second))) {
            break;
          }
          LL dist = abs(redTiles[i].first - redTiles[j].first + 1LL) * abs(redTiles[i].second - redTiles[j].second + 1LL);
          q.emplace(dist, i, j);
        }
      }
    }
    if (q.empty()) return 0;
    PIII top = q.top();
    q.pop();
    return get<0>(top);
  }

  LL largestEmptyRectangle() const {
    priority_queue<PIII, vector<PIII>, less<>> q;
    for (int i = 0; i < redTiles.size(); i++) {
      for (int j = i+1;j < redTiles.size();j++) {
        for (int k = 0; k < redTiles.size(); k++) {
          if (k == i || k == j) continue;
          // k cannot lie in the rectangle formed by i and j
          if ((redTiles[k].first > min(redTiles[i].first, redTiles[j].first) &&
               redTiles[k].first < max(redTiles[i].first, redTiles[j].first)) &&
              (redTiles[k].second > min(redTiles[i].second, redTiles[j].second) &&
               redTiles[k].second < max(redTiles[i].second, redTiles[j].second))) {
            continue;
          }
          LL dist = abs(redTiles[i].first - redTiles[j].first + 1LL) * abs(redTiles[i].second - redTiles[j].second + 1LL);
          q.emplace(dist, i, j);
        }
      }
    }
    if (q.empty()) return 0;
    PIII top = q.top();
    q.pop();
    return get<0>(top);
  }

  LL solution() {
    fill_n(&grid2[0][0], sizeof(grid2) / sizeof(char), '.');
    redTiles.clear();
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      int row, col;
      sscanf(line.c_str(), "%d,%d", &row, &col);

      tiles.insert({row, col});
      grid2[row/1000][col/1000] = '#';
      redTiles.emplace_back(row, col);
      rows.push_back(row);
      columns.push_back(col);
    }
    // print grid2
    /*
    for (int i = 0; i < GRID_SIZE; i++) {
      for (int j = 0; j < GRID_SIZE; j++) {
        cout << grid2[i][j] << " ";
      }
      cout << endl;
    }
    cout << endl;
    */
    // sort rows and columns
    sort(rows.begin(), rows.end());
    sort(columns.begin(), columns.end());

    int firstRow = -1;
    int firstCol = -1;
    vector<PII> boundingBox;

    for (int ri = 0;ri < rows.size();ri++) {
      for (int ci = 0;ci < columns.size();ci++) {
        int row = rows[ri];
        int col = columns[ci];
        if (tiles.find({row, col}) == tiles.end()) continue;

        if (firstRow == -1 && firstCol == -1) {
          firstRow = row;
          firstCol = col;
        }
      }
    }

    int found = 1;




    return largestEmptyRectangle();
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
