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

const map<char, PII> dirToDelta = {{'D', {1,  0}},
                                   {'R', {0,  1}},
                                   {'U', {-1, 0}},
                                   {'L', {0,  -1}}};

const vector<PII> ds = {{1,  0},
                        {0,  1},
                        {-1, 0},
                        {0,  -1}};

char grid[10000][10000];
const int OFFSET = 5000;

// vertical only
struct Segment {
  int startRow;
  int col;
  int endRow;
  int origOrdering;

  Segment(int startRow, int col, int endRow, int origOrdering) : startRow(startRow), col(col), endRow(endRow), origOrdering(origOrdering) {}

  bool operator<(const Segment &other) const {
    return col < other.col;
  }

  int intersects(int row) const {
    if (row == startRow) return 1;
    if (row == endRow) return 2;
    if (row > startRow && row < endRow) return 3;
    return 0;
  }
};

class Assignment {
public:
  int minRow;
  int maxRow;
  int minCol;
  int maxCol;
  vector<Segment> segments;

  bool adjacentIndices(int idx1, int idx2) {
    return abs(idx1 - idx2) == 1 || (idx1 == 0 && idx2 == segments.size() - 1) || (idx2 == 0 && idx1 == segments.size() - 1);
  }

  LL calcInterior() {
    // scanline but smart. Try to see if we can do it using vertical line segments only.
    LL result = 0;
    for (int row = minRow; row < maxRow; row++) {
      int col = minCol;
      bool inside = false;
      int previousIdx = -2;
      int previousIntersection = -1;
      LL lineResult = 0;
      int prevStart2 = -1;
      int prevStart = -1;
      bool downIsInside = true;
      // iterate over the segments
      for (auto &segment: segments) {
        int intersection = segment.intersects(row);
        if (!intersection) continue;

        // if (row == 2) {
           //cout << "row: " << row << " col: " << col << " segment.col: " << segment.col << " segment.ordering: " << segment.origOrdering << " prevOrdering: " << previousIdx << " prevIntersection: " << previousIntersection <<  " intersection: " << intersection << " inside: " << inside << endl;
        // }

        if (segment.col < col) {
          cout << "Warning segment col is smaller than col, this should not happen" << endl;
          // continue;
        }

        // if the difference in the original ordering is 1, we are on the boundary
        if (adjacentIndices(previousIdx, segment.origOrdering) && ((previousIntersection == 1 && intersection == 1) || (previousIntersection == 2 && intersection == 2))) {
          //cout << "  on boundary, adding " << segment.col - col + 1 << endl;
          if (prevStart2 != segment.startRow || row != segment.startRow) {
            lineResult += segment.col - col + 1;
            for (int c = col; c <= segment.col; c++) {
              if (grid[row + OFFSET][c + OFFSET] == '.') grid[row + OFFSET][c + OFFSET] = 'X';
              if (grid[row + OFFSET][c + OFFSET] == '#') grid[row + OFFSET][c + OFFSET] = '*';
            }
          } else {
            lineResult++;
            if (grid[row + OFFSET][segment.col + OFFSET] == '.') grid[row + OFFSET][segment.col + OFFSET] = 'X';
            if (grid[row + OFFSET][segment.col + OFFSET] == '#') grid[row + OFFSET][segment.col + OFFSET] = '*';
          }
          // inside = !inside;
        } else {
          if (inside) {
            if (intersection == 3 || (previousIntersection == 1 && intersection == 2) || (intersection == 1 && previousIntersection == 2)) {
              //cout << "  inside, adding " << segment.col - col + 1 << " and setting inside to false" << endl;
              inside = false;
            } else {
              //cout << "  inside, adding " << segment.col - col + 1 << " and not changing inside" << endl;
            }
            lineResult += segment.col - col + 1;
            for (int c = col; c <= segment.col; c++) {
              if (grid[row + OFFSET][c + OFFSET] == '.') grid[row + OFFSET][c + OFFSET] = 'X';
              if (grid[row + OFFSET][c + OFFSET] == '#') grid[row + OFFSET][c + OFFSET] = '*';
            }
          } else {
            if (adjacentIndices(previousIdx, segment.origOrdering) &&
                ((previousIntersection == 1 && intersection == 2) ||
                 (previousIntersection == 2 && intersection == 1))) {
              //cout << "  on boundary2, adding " << segment.col - col + 1 << endl;
              lineResult += segment.col - col + 1;
              for (int c = col; c <= segment.col; c++) {
                if (grid[row + OFFSET][c + OFFSET] == '.') grid[row + OFFSET][c + OFFSET] = 'X';
                if (grid[row + OFFSET][c + OFFSET] == '#') grid[row + OFFSET][c + OFFSET] = '*';
              }
            } else {
              if (grid[row + OFFSET][segment.col + OFFSET] == '.') grid[row + OFFSET][segment.col + OFFSET] = 'X';
              if (grid[row + OFFSET][segment.col + OFFSET] == '#') grid[row + OFFSET][segment.col + OFFSET] = '*';
              lineResult++;
            }
            if (intersection == 3 || (previousIntersection == 1 && intersection == 2) || (intersection == 1 && previousIntersection == 2)) {
              inside = true;
              //cout << "  not inside, setting inside to true" << endl;
            } else {
              //cout << "  not inside, not changing inside" << endl;
            }
          }
        }

        /*
        // I don't think the type of intersection matters
        if (inside) {
          inside = false;
          lineResult += segment.col - col + 1;
        } else {
          if ((previousIntersection == 1 && intersection == 2) || (previousIntersection == 2 && intersection == 1)) {
            // we are going from one segment to the next, but we are not inside.
            // this means we are on the boundary. Count only the inside part
            cout << "adding part of segment: " << segment.col - col - 1 << endl;
            lineResult += segment.col - col - 2;
          } else {
            inside = true;
          }
        }
        */
        prevStart2 = prevStart;
        prevStart = segment.startRow;
        col = segment.col + 1;
        previousIdx = segment.origOrdering;
        previousIntersection = intersection;
      }
      /*
      for (int ccol = minCol; ccol < maxCol; ccol++) {
        cout << grid[row + OFFSET][ccol + OFFSET];
      }
      cout << endl;
      cout << row << " " << lineResult << endl;
      cout << endl;
      */
      result += lineResult;
    }
    return result;
  }

  void printGrid() {
    for (int row = minRow; row < maxRow; row++) {
      for (int col = minCol; col < maxCol; col++) {
        cout << grid[row+OFFSET][col+OFFSET];
      }
      cout << endl;
    }
  }


  LL solution() {
    memset(grid, '.', sizeof(grid));
    int row = 0;
    int col = 0;
    minRow = 0;
    maxRow = 0;
    minCol = 0;
    maxCol = 0;
    int idx = 0;
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      char direction;
      int steps;
      stringstream ss(line);
      // ignore the color for now
      ss >> direction >> steps;
      int nrow = row + dirToDelta.at(direction).first * steps;
      if (nrow < minRow) minRow = nrow;
      if (nrow > maxRow) maxRow = nrow;
      int ncol = col + dirToDelta.at(direction).second * steps;
      if (ncol < minCol) minCol = ncol;
      if (ncol > maxCol) maxCol = ncol;
      if (direction == 'D') {
        segments.emplace_back(row, col, nrow, idx);
      }
      if (direction == 'U') {
        segments.emplace_back(nrow, col, row, idx);
      }
      if (direction == 'D' || direction == 'U') {
        idx++;
      }

      int myrow = row;
      int mycol = col;
      for (int i = 0; i < steps; i++) {
        myrow += dirToDelta.at(direction).first;
        mycol += dirToDelta.at(direction).second;
        grid[myrow+OFFSET][mycol+OFFSET] = '#';
      }

      row = nrow;
      col = ncol;
    }
    // If we end on the boundary, expand the grid, so we always start outside.
    maxRow += 2;
    maxCol += 2;
    minRow--;
    minCol--;
    // sort the segments
    sort(segments.begin(), segments.end());

    // printGrid();
    LL result = calcInterior();
    printGrid();
    cout << "number of segments: " << segments.size() << endl;
    return result;
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
