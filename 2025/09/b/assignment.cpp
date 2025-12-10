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


const int GRID_SIZE = 100;
char grid[GRID_SIZE][GRID_SIZE];


class Assignment {
  vector<PII> redTiles;
  vector<PII> greenTiles;
  vector<int> rows;
  vector<int> columns;
  set<PII> tiles;
  vector<PII> boundingBox;
public:

  bool linesCross(PII afrom, PII ato, PII bfrom, PII bto) const {
    int d1 = (ato.first - afrom.first) * (bfrom.second - afrom.second) - (ato.second - afrom.second) * (bfrom.first - afrom.first);
    int d2 = (ato.first - afrom.first) * (bto.second - afrom.second) - (ato.second - afrom.second) * (bto.first - afrom.first);
    int d3 = (bto.first - bfrom.first) * (afrom.second - bfrom.second) - (bto.second - bfrom.second) * (afrom.first - bfrom.first);
    int d4 = (bto.first - bfrom.first) * (ato.second - bfrom.second) - (bto.second - bfrom.second) * (ato.first - bfrom.first);
    return (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) &&
            ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0)));
  }

  LL largestArea() const {
    priority_queue<PIII, vector<PIII>, less<>> q;
    for (int i = 0; i < redTiles.size(); i++) {
      for (int j = i+1;j < redTiles.size();j++) {
        // The line between i and j cannot cross any line piece in the bounding box.
        PII afrom = redTiles[i];
        PII ato = redTiles[j];
        bool crosses = false;
        for (int k = 0; k < redTiles.size(); k++) {
          if (k == i || k == j) continue;
          // k has lie within the rectangle formed by i and j
          if ((redTiles[k].first > min(redTiles[i].first, redTiles[j].first) &&
               redTiles[k].first < max(redTiles[i].first, redTiles[j].first)) &&
              (redTiles[k].second > min(redTiles[i].second, redTiles[j].second) &&
               redTiles[k].second < max(redTiles[i].second, redTiles[j].second))) {
            crosses = true;
            break;
          }
        }
        for (int k =0; k < greenTiles.size(); k++) {
          // k has to lie within the rectangle formed by i and j
          if ((greenTiles[k].first > min(redTiles[i].first, redTiles[j].first) &&
               greenTiles[k].first < max(redTiles[i].first, redTiles[j].first)) &&
              (greenTiles[k].second > min(redTiles[i].second, redTiles[j].second) &&
               greenTiles[k].second < max(redTiles[i].second, redTiles[j].second))) {
            crosses = true;
            break;
          }
        }
        if (!crosses && false) {
          for (int k = 0;k < redTiles.size();k++) {
            PII bfrom = redTiles[k];
            PII bto = redTiles[(k+1) % redTiles.size()];
            // Check if line (afrom, ato) crosses (bfrom, bto)
            if (linesCross(afrom, ato, bfrom, bto)) {
              // crosses = true;
              break;
            }
          }
        }
        if (!crosses) {
          LL dist = (abs(redTiles[i].first - redTiles[j].first) + 1LL) * (abs(redTiles[i].second - redTiles[j].second) + 1LL);
          /*
          cout << "Found area " << dist << " between (" << redTiles[i].first << "," << redTiles[i].second << ") and ("
               << redTiles[j].first << "," << redTiles[j].second << ")" << endl;
          */
          q.emplace(dist, i, j);
        }
      }
    }
    if (q.empty()) return 0;
    PIII top = q.top();
    q.pop();
    // in grid, mark the rectangle with X
    PII a = redTiles[get<1>(top)];
    PII b = redTiles[get<2>(top)];
    for (int r = min(a.first, b.first); r <= max(a.first, b.first); r++) {
      for (int c = min(a.second, b.second); c <= max(a.second, b.second); c++) {
        if (grid[r/1000][c/1000] != 'G') {
          grid[r/1000][c/1000] = 'X';
        }
      }
    }


    return get<0>(top);
  }

  LL solution() {
    redTiles.clear();
    fill(&grid[0][0], &grid[0][0] + sizeof(grid) / sizeof(char), '.');
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      int row, col;
      sscanf(line.c_str(), "%d,%d", &row, &col);

      tiles.insert({row, col});
      grid[row/1000][col/1000] = '#';
      redTiles.emplace_back(row, col);
      // if either the row or col is more than 10000 away from the previous row or col respectively,
      // add a tile exactly in between the two tiles to the green tiles
      if (!rows.empty()) {
        int prevRow = rows.back();
        int prevCol = columns.back();
        if (abs(row - prevRow) > 10000) {
          int midRow = (row + prevRow) / 2;
          greenTiles.emplace_back(midRow, col);
          tiles.insert({midRow, col});
          grid[midRow/1000][col/1000] = 'G';
        } else if (abs(col - prevCol) > 10000) {
          int midCol = (col + prevCol) / 2;
          greenTiles.emplace_back(row, midCol);
          tiles.insert({row, midCol});
          grid[row/1000][midCol/1000] = 'G';
        }
      }

      rows.push_back(row);
      columns.push_back(col);
    }
    // sort rows and columns
    sort(rows.begin(), rows.end());
    sort(columns.begin(), columns.end());
    // remove duplicates
    rows.erase(unique(rows.begin(), rows.end()), rows.end());
    columns.erase(unique(columns.begin(), columns.end()), columns.end());

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

    int found = 0;
    PII cur = {first.first, first.second};
    PII prev = {-1, -1};
    while (found < redTiles.size()) {
      PII start = {cur.first, cur.second};
      bool foundOne = false;
      for (int d = 0;d< directions.size();d++) {
        cur = {start.first,start.second};
        for (int i = 0;i < redTiles.size();i++) {
          cur = {cur.first + directions[d].first, cur.second + directions[d].second};
          if (cur.first < 0 || cur.first >= rows.size() ||
              cur.second < 0 || cur.second >= columns.size()) {
            break;
          }
          if (tiles.find({rows[cur.first], columns[cur.second]}) != tiles.end() &&
            (prev.first != cur.first || prev.second != cur.second)) {
            //cout << "previous point: (" << (prev.first == -1 ? -1 : rows[prev.first]) << "," << (prev.second == -1 ? -1 : columns[prev.second]) << ")" << endl;
            //cout << "starting from: (" << rows[start.first] << "," << columns[start.second] << ")" << endl;
            //cout << "found next bounding box point at: (" << rows[cur.first] << "," << columns[cur.second] << ")" << endl;
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
        //cout << "adding to bounding box: (" << rows[cur.first] << "," << columns[cur.second] << ")" << endl << endl;
        grid[rows[cur.first]/1000][columns[cur.second]/1000] =  '0' + (boundingBox.size() % 10);
      }
      prev = {start.first, start.second};
    }

    //cout << "bounding box size: " << boundingBox.size() << endl;

    // print grid
    LL result = largestArea();

    for (int i = 0;i < GRID_SIZE;i++) {
      for (int j = 0;j < GRID_SIZE;j++) {
        cout << grid[i][j] << " ";
      }
      cout << endl;
    }
    cout << endl;


    return result;
  }
};

int main() {
  // it's not 4631418792
  // it's not 85610176
  // it's not 1439862255
  // maybe    1439894345
  //
  Assignment obj;
  cout << obj.solution() << endl;
}
