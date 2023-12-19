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

// For debugging
char grid[10000][10000];
const int OFFSET = 5000;

struct VerticalSegment {
  int row;
  int col;
  int length;
  char direction;
  string connections;

  VerticalSegment(int row, int col, int length, char direction, string connections) : row(row), col(col),
                                                                                      length(length),
                                                                                      direction(direction),
                                                                                      connections(
                                                                                          std::move(connections)) {
  }

  bool operator<(const VerticalSegment &other) const {
    if (col != other.col) {
      return col < other.col;
    } else {
      return row < other.row;
    }
  }

  [[nodiscard]] int intersects(int crow) const {
    if (crow == row) return 1;
    if (direction == 'D' && crow > row && crow < row + length) return 2;
    if (direction == 'U' && crow < row && crow > row - length) return 2;
    return 0;
  }
};

struct HorizontalSegment {
  int col;
  int row;
  int length;
  char direction;
  string connections;

  HorizontalSegment(int row, int col, int length, char direction, string connections) : row(row), col(col),
                                                                                        length(length),
                                                                                        direction(direction),
                                                                                        connections(
                                                                                            std::move(connections)) {
  }

  bool operator<(const HorizontalSegment &other) const {
    if (row != other.row) {
      return row < other.row;
    } else {
      return col < other.col;
    }
  }

  [[nodiscard]] bool intersects(int rrow) const {
    return rrow == row;
  }
};

class Assignment {
public:
  int minRow{};
  int maxRow{};
  int minCol{};
  int maxCol{};
  vector<HorizontalSegment> hsegments;
  vector<VerticalSegment> vsegments;

  void printGrid() const {
    for (int row = minRow; row < maxRow; row++) {
      for (int col = minCol; col < maxCol; col++) {
        cout << grid[row + OFFSET][col + OFFSET];
      }
      cout << endl;
    }
  }

  LL calcInterior() {
    LL result = 0;

    for (int row = minRow; row < maxRow; row++) {
      /*
      for (int i = minCol; i < maxCol; i++) {
        cout << grid[row + OFFSET][i + OFFSET];
      }
      cout << endl;
      */
      int startInside = minCol;
      bool inside = false;
      bool aboveIsInside = false;
      LL lineResult = 0;
      // get a vector of all the horizontal segments that intersect this row
      vector<HorizontalSegment> ihsegments;
      for (auto &hsegment: hsegments) {
        if (!hsegment.intersects(row)) continue;
        ihsegments.push_back(hsegment);
      }
      sort(ihsegments.begin(), ihsegments.end());
      int nextHsegIdx = 0;
      // ihsegments[nextHsegIdx];
      for (auto &vsegment: vsegments) {
        if (!vsegment.intersects(row)) continue;
        // copy this bit after the for loop too
        while (nextHsegIdx < ihsegments.size() && vsegment.col > ihsegments[nextHsegIdx].col) {
          /*
          cout << "handling hsegment: " << ihsegments[nextHsegIdx].row << " " << ihsegments[nextHsegIdx].col << " "
               << ihsegments[nextHsegIdx].length << " " << ihsegments[nextHsegIdx].direction << " "
               << ihsegments[nextHsegIdx].connections << endl;
          */
          // handle hsegments
          if (ihsegments[nextHsegIdx].connections == "NE") {
            if (inside) {
              aboveIsInside = false;
              if (ihsegments[nextHsegIdx].col > startInside) {
                lineResult += ihsegments[nextHsegIdx].col - startInside;
              }
            } else {
              aboveIsInside = true;
            }
          } else if (ihsegments[nextHsegIdx].connections == "NW") {
            if (aboveIsInside) {
              inside = false;
            } else {
              inside = true;
              startInside = ihsegments[nextHsegIdx].col + 1;
            }
          } else if (ihsegments[nextHsegIdx].connections == "SE") {
            if (inside) {
              aboveIsInside = true;
              if (ihsegments[nextHsegIdx].col > startInside) {
                lineResult += ihsegments[nextHsegIdx].col - startInside;
              }
            } else {
              aboveIsInside = false;
            }
          } else if (ihsegments[nextHsegIdx].connections == "SW") {
            if (aboveIsInside) {
              inside = true;
              startInside = ihsegments[nextHsegIdx].col + 1;
            } else {
              inside = false;
            }
          } else {
            cout << "ERROR: unknown connections: " << ihsegments[nextHsegIdx].connections << endl;
            exit(1);
          }
          nextHsegIdx++;
        }
        if (vsegment.intersects(row) == 1) {
          /*
          cout << "handling vsegment (start): " << vsegment.row << " " << vsegment.col << " " << vsegment.length << " "
               << vsegment.direction << " " << vsegment.connections << endl;
           */
          if (vsegment.connections == "NE") {
            if (inside) {
              aboveIsInside = false;
              if (vsegment.col > startInside) {
                lineResult += vsegment.col - startInside;
              }
            } else {
              aboveIsInside = true;
            }
          } else if (vsegment.connections == "NW") {
            if (aboveIsInside) {
              inside = false;
            } else {
              inside = true;
              startInside = vsegment.col + 1;
            }
          } else if (vsegment.connections == "SE") {
            if (inside) {
              aboveIsInside = true;
              if (vsegment.col > startInside) {
                lineResult += vsegment.col - startInside;
              }
            } else {
              aboveIsInside = false;
            }
          } else if (vsegment.connections == "SW") {
            if (aboveIsInside) {
              inside = true;
              startInside = vsegment.col + 1;
            } else {
              inside = false;
            }
          } else {
            cout << "ERROR: unknown connections: " << vsegment.connections << endl;
            exit(1);
          }
        } else if (vsegment.intersects(row) == 2) {
          /*
          cout << "handling vsegment (vertical): " << vsegment.row << " " << vsegment.col << " " << vsegment.length << " "
               << vsegment.direction << " " << vsegment.connections << endl;
          */
          if (inside) {
            inside = false;
            if (vsegment.col > startInside) {
              lineResult += vsegment.col - startInside;
            }
          } else {
            inside = true;
            startInside = vsegment.col + 1;
          }
        }
      }
      while (nextHsegIdx < ihsegments.size()) {
        // handle hsegments
        /*
        cout << "handling hsegment: " << ihsegments[nextHsegIdx].row << " " << ihsegments[nextHsegIdx].col << " "
             << ihsegments[nextHsegIdx].length << " " << ihsegments[nextHsegIdx].direction << " "
             << ihsegments[nextHsegIdx].connections << endl;
        */
        if (ihsegments[nextHsegIdx].connections == "NE") {
          if (inside) {
            aboveIsInside = false;
            if (ihsegments[nextHsegIdx].col > startInside) {
              lineResult += ihsegments[nextHsegIdx].col - startInside;
            }
          } else {
            aboveIsInside = true;
          }
        } else if (ihsegments[nextHsegIdx].connections == "NW") {
          if (aboveIsInside) {
            inside = false;
          } else {
            inside = true;
            startInside = ihsegments[nextHsegIdx].col + 1;
          }
        } else if (ihsegments[nextHsegIdx].connections == "SE") {
          if (inside) {
            aboveIsInside = true;
            if (ihsegments[nextHsegIdx].col > startInside) {
              lineResult += ihsegments[nextHsegIdx].col - startInside;
            }
          } else {
            aboveIsInside = false;
          }
        } else if (ihsegments[nextHsegIdx].connections == "SW") {
          if (aboveIsInside) {
            inside = true;
            startInside = ihsegments[nextHsegIdx].col + 1;
          } else {
            inside = false;
          }
        } else {
          cout << "ERROR: unknown connections: " << ihsegments[nextHsegIdx].connections << endl;
          exit(1);
        }
        nextHsegIdx++;
      }
      // cout << "row: " << row << " lineResult: " << lineResult << endl << endl;
      result += lineResult;
    }
    return result;
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
      boundary += steps;

      // check if vsegment always followed by hsegment
      if ((direction == 'U' || direction == 'D') && (previousDirection == 'U' || previousDirection == 'D')) {
        cout << "ERROR: " << direction << " followed by " << previousDirection << endl;
        exit(1);
      }
      if ((direction == 'L' || direction == 'R') && (previousDirection == 'L' || previousDirection == 'R')) {
        cout << "ERROR: " << direction << " followed by " << previousDirection << endl;
        exit(1);
      }

      string connections;
      if (direction == 'D') {
        if (previousDirection == 'R') {
          connections = "SW";
        } else if (previousDirection == 'L') {
          connections = "SE";
        }
        vsegments.emplace_back(row, col, steps, direction, connections);
      } else if (direction == 'U') {
        if (previousDirection == 'R') {
          connections = "NW";
        } else if (previousDirection == 'L') {
          connections = "NE";
        }
        vsegments.emplace_back(row, col, steps, direction, connections);
      } else if (direction == 'R') {
        if (previousDirection == 'U') {
          connections = "SE";
        } else if (previousDirection == 'D') {
          connections = "NE";
        }
        hsegments.emplace_back(row, col, steps, direction, connections);
      } else if (direction == 'L') {
        if (previousDirection == 'U') {
          connections = "SW";
        } else if (previousDirection == 'D') {
          connections = "NW";
        }
        hsegments.emplace_back(row, col, steps, direction, connections);
      }

      int myrow = row;
      int mycol = col;
      for (int i = 0; i < steps; i++) {
        myrow += dirToDelta.at(direction).first;
        mycol += dirToDelta.at(direction).second;
        grid[myrow + OFFSET][mycol + OFFSET] = '#';
      }

      previousDirection = direction;
      row = nrow;
      col = ncol;
    }

    // Set the start or end connections for the first segments.
    if (previousDirection == 'D') {
      if (!hsegments.front().connections.empty()) {
        cout << "ERROR: " << hsegments.front().direction << " preceded by " << previousDirection << endl;
        exit(1);
      }
      // the last segment is vertical, so the first segment is horizontal
      if (hsegments.front().direction == 'R') {
        hsegments.front().connections = "NE";
      } else if (hsegments.front().direction == 'L') {
        hsegments.front().connections = "NW";
      }
    } else if (previousDirection == 'U') {
      if (!hsegments.front().connections.empty()) {
        cout << "ERROR: " << hsegments.front().direction << " preceded by " << previousDirection << endl;
        exit(1);
      }
      // the last segment is vertical, so the first segment is horizontal
      if (hsegments.front().direction == 'R') {
        hsegments.front().connections = "SE";
      } else if (hsegments.front().direction == 'L') {
        hsegments.front().connections = "SW";
      }
    } else if (previousDirection == 'R') {
      if (!vsegments.front().connections.empty()) {
        cout << "ERROR: " << vsegments.front().direction << " preceded by " << previousDirection << endl;
        exit(1);
      }
      // the last segment is horizontal, so the first segment is vertical
      if (vsegments.front().direction == 'D') {
        vsegments.front().connections = "SW";
      } else if (vsegments.front().direction == 'U') {
        vsegments.front().connections = "NW";
      }
    } else if (previousDirection == 'L') {
      if (!vsegments.front().connections.empty()) {
        cout << "ERROR: " << vsegments.front().direction << " preceded by " << previousDirection << endl;
        exit(1);
      }
      // the last segment is horizontal, so the first segment is vertical
      if (vsegments.front().direction == 'D') {
        vsegments.front().connections = "SE";
      } else if (vsegments.front().direction == 'U') {
        vsegments.front().connections = "NE";
      }
    }

    // If we end on the boundary, expand the grid, so we always start outside.
    maxRow += 2;
    maxCol += 2;
    minRow--;
    minCol--;

    // sort the segments
    sort(hsegments.begin(), hsegments.end());
    sort(vsegments.begin(), vsegments.end());

    // printGrid();

    // cout << "boundary : " << boundary << endl;
    return calcInterior() + boundary;
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
