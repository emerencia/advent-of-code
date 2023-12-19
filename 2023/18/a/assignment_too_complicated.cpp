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

struct VerticalSegment {
  int startRow;
  int col;
  int endRow;
  char direction;
  string startConnections;
  string endConnections;

  VerticalSegment(int startRow, int col, int endRow, char direction, string startConnections, string endConnections) : startRow(startRow), col(col), endRow(endRow), direction(direction), startConnections(startConnections), endConnections(endConnections) {
  }

  bool operator<(const VerticalSegment &other) const {
    return col < other.col;
  }

  int intersects(int row) const {
    if (row == startRow) return 1;
    if (row == endRow) return 2;
    if (row > startRow && row < endRow) return 3;
    return 0;
  }
};

struct HorizontalSegment {
  int startCol;
  int row;
  int endCol;
  char direction;
  string startConnections;
  string endConnections;

  HorizontalSegment(int startCol, int row, int endCol, char direction, string startConnections, string endConnections) : startCol(startCol), row(row), endCol(endCol), direction(direction), startConnections(startConnections), endConnections(endConnections) {
  }

  bool operator<(const HorizontalSegment &other) const {
    return row < other.row;
  }

  int intersects(int col) const {
    if (col == startCol) return 1;
    if (col == endCol) return 2;
    if (col > startCol && col < endCol) return 3;
    return 0;
  }
};

class Assignment {
public:
  int minRow;
  int maxRow;
  int minCol;
  int maxCol;
  vector<HorizontalSegment> hsegments;
  vector<VerticalSegment> vsegments;

  void printGrid() {
    for (int row = minRow; row < maxRow; row++) {
      for (int col = minCol; col < maxCol; col++) {
        cout << grid[row+OFFSET][col+OFFSET];
      }
      cout << endl;
    }
  }

  LL calcInterior() {
    return 0;
  }

  LL solution() {
    memset(grid, '.', sizeof(grid));
    hsegments.clear();
    vsegments.clear();
    int row = 0;
    int col = 0;
    minRow = 0;
    maxRow = 0;
    minCol = 0;
    maxCol = 0;
    LL boundary = 0;
    char previousDirection = ' ';
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

      // check if vsegment always followed by hsegment
      if ((direction == 'U' || direction == 'D') && (previousDirection == 'U' || previousDirection == 'D')) {
        cout << "ERROR: " << direction << " followed by " << previousDirection << endl;
        exit(1);
      }
      if ((direction == 'L' || direction == 'R') && (previousDirection == 'L' || previousDirection == 'R')) {
        cout << "ERROR: " << direction << " followed by " << previousDirection << endl;
        exit(1);
      }

      // TODO: how to deal with overlapping segments?

      string startConnections = "";
      string endConnections = "";
      if (direction == 'D') {
        if (previousDirection == 'R') {
          startConnections = "SW";
          hsegments.back().endConnections = "SW";
        } else if (previousDirection == 'L') {
          startConnections = "SE";
          hsegments.back().startConnections = "SE";
        }
        vsegments.emplace_back(row, col, nrow, direction, startConnections, endConnections);
      } else if (direction == 'U') {
        if (previousDirection == 'R') {
          endConnections = "NW";
          hsegments.back().endConnections = "NW";
        } else if (previousDirection == 'L') {
          endConnections = "NE";
          hsegments.back().startConnections = "NE";
        }
        vsegments.emplace_back(nrow, col, row, direction, startConnections, endConnections);
      } else if (direction == 'R') {
        if (previousDirection == 'U') {
          startConnections = "SE";
          vsegments.back().startConnections = "SE";
        } else if (previousDirection == 'D') {
          startConnections = "NE";
          vsegments.back().endConnections = "NE";
        }
        hsegments.emplace_back(col, row, ncol, direction, startConnections, endConnections);
      } else if (direction == 'L') {
        if (previousDirection == 'U') {
          endConnections = "SW";
          vsegments.back().startConnections = "SW";
        } else if (previousDirection == 'D') {
          endConnections = "NW";
          vsegments.back().endConnections = "NW";
        }
        hsegments.emplace_back(ncol, row, col, direction, startConnections, endConnections);
      }

      int myrow = row;
      int mycol = col;
      for (int i = 0; i < steps; i++) {
        myrow += dirToDelta.at(direction).first;
        mycol += dirToDelta.at(direction).second;
        grid[myrow+OFFSET][mycol+OFFSET] = '#';
      }

      previousDirection = direction;
      row = nrow;
      col = ncol;
    }

    // Set the start or end connections for the first and last segments.
    if (previousDirection == 'D') {
      // set the startConnections of vsegments.back()
      // the last segment is vertical, so the first segment is horizontal
      if (hsegments.front().direction == 'R') {
        hsegments.front().startConnections = "NE";
        vsegments.back().endConnections = "NE";
      } else if (hsegments.front().direction == 'L') {
        hsegments.front().endConnections = "NW";
        vsegments.back().endConnections = "NW";
      }
    } else if (previousDirection == 'U') {
      // set the endConnections of vsegments.back()
      // the last segment is vertical, so the first segment is horizontal
      if (hsegments.front().direction == 'R') {
        hsegments.front().startConnections = "SE";
        vsegments.back().startConnections = "SE";
      } else if (hsegments.front().direction == 'L') {
        hsegments.front().endConnections = "SW";
        vsegments.back().startConnections = "SW";
      }
    } else if (previousDirection == 'R') {
      // set the startConnections of hsegments.back()
      // the last segment is horizontal, so the first segment is vertical
      if (vsegments.front().direction == 'U') {
        vsegments.front().startConnections = "SW";
        hsegments.back().startConnections = "SW";
      } else if (vsegments.front().direction == 'D') {
        vsegments.front().endConnections = "NW";
        hsegments.back().startConnections = "NW";
      }
    } else if (previousDirection == 'L') {
      // set the endConnections of hsegments.back()
      // the last segment is horizontal, so the first segment is vertical
      if (vsegments.front().direction == 'U') {
        vsegments.front().startConnections = "SE";
        hsegments.back().endConnections = "SE";
      } else if (vsegments.front().direction == 'D') {
        vsegments.front().endConnections = "NE";
        hsegments.back().endConnections = "NE";
      }
    }



    // If we end on the boundary, expand the grid, so we always start outside.
    maxRow += 2;
    maxCol += 2;
    minRow--;
    minCol--;
    // set the start and end connections
    hsegments[

    // sort the segments
    sort(hsegments.begin(), hsegments.end());
    sort(vsegments.begin(), vsegments.end());

    // printGrid();
    return calcInterior() + boundary;
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
