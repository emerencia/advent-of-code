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

const map<char, PII> dirToDelta = {{'R', {0,  1}},
                                   {'D', {1,  0}},
                                   {'L', {0,  -1}},
                                   {'U', {-1, 0}}};

const map<int, char> dirToChar = {{0, 'R'},
                                  {1, 'D'},
                                  {2, 'L'},
                                  {3, 'U'}};

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
    // return 1 for intersection with the start point of the line segment,
    // and 2 for intersection with the rest of the line segment (i.e., not the start point)
    if (crow == row) return 1;
    if (direction == 'D' && crow > row && crow < row + length) return 2;
    if (direction == 'U' && crow < row && crow > row - length) return 2;
    return 0;
  }
};

struct HorizontalSegment {
  int col;
  int row;
  int length; // not used
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
  vector<int> actionRows;

  bool isActionRow(int row) {
    return binary_search(actionRows.begin(), actionRows.end(), row);
  }

  int nextActionRow(int row) {
    // return the first actionRow that is greater than row
    auto it = upper_bound(actionRows.begin(), actionRows.end(), row);
    if (it == actionRows.end()) return -1;
    return *it;
  }

  static void handleSegmentStart(const string &connections, int col, bool &inside, bool &aboveIsInside,
                                 int &startInside, LL &lineResult) {
    if (connections == "NE") {
      if (inside) {
        aboveIsInside = false;
        if (col > startInside) {
          lineResult += col - startInside;
        }
      } else {
        aboveIsInside = true;
      }
    } else if (connections == "NW") {
      if (aboveIsInside) {
        inside = false;
      } else {
        inside = true;
        startInside = col + 1;
      }
    } else if (connections == "SE") {
      if (inside) {
        aboveIsInside = true;
        if (col > startInside) {
          lineResult += col - startInside;
        }
      } else {
        aboveIsInside = false;
      }
    } else if (connections == "SW") {
      if (aboveIsInside) {
        inside = true;
        startInside = col + 1;
      } else {
        inside = false;
      }
    } else {
      cout << "ERROR: unknown connections: " << connections << endl;
      exit(1);
    }
  }

  static void interweaveVerticalSegment(int row, const VerticalSegment &vsegment, bool &inside, bool &aboveIsInside,
                                        int &startInside, LL &lineResult) {
    if (vsegment.intersects(row) == 1) {
      /*
      cout << "handling vsegment (start): " << vsegment.row << " " << vsegment.col << " " << vsegment.length << " "
           << vsegment.direction << " " << vsegment.connections << endl;
       */
      handleSegmentStart(vsegment.connections, vsegment.col, inside, aboveIsInside, startInside, lineResult);
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

  static void interweaveHorizontalSegment(const HorizontalSegment &hsegment, bool &inside, bool &aboveIsInside,
                                          int &startInside, LL &lineResult) {
    /*
      cout << "handling hsegment: " << hsegment.row << " " << hsegment.col << " "
           << hsegment.length << " " << hsegment.direction << " "
           << hsegment.connections << endl;
    */
    // handle hsegments
    // precondition: hsegment intersects with the current row
    handleSegmentStart(hsegment.connections, hsegment.col, inside, aboveIsInside, startInside, lineResult);
  }

  LL calcInterior() {
    // We keep track of the vertical and horizontal line segments separately, and
    // interweave them as necessary. We skip rows where nothing happens by keeping track
    // of the "actionRows" (i.e., rows where something happens).
    // The assumption is that the result for rows that are not action rows is the same.
    // Within a row, rather than counting individual cells, we advance from segment to segment.
    // So both in the vertical and horizontal direction, we advance from segment to segment,
    // and never look at the cells in between.
    // We calculate the boundary separately, because that is easy to do and then we don't
    // have to deal with a whole load of edge cases.
    LL result = 0;
    LL lastlineResult = 0;
    for (int row = minRow; row < maxRow; row++) {

      // Skip rows where nothing happens
      if (row != minRow && !isActionRow(row) && !isActionRow(row - 1)) {
        int nxtActionRow = nextActionRow(row);
        if (nxtActionRow != -1) {
          int rowsSkipped = nxtActionRow - row;
          if (rowsSkipped > 0) {
            row = nxtActionRow - 1;
            result += lastlineResult * rowsSkipped;
            continue;
          }
        }
      }

      int startInside = minCol; // startInside = where the last inside segment started
      bool inside = false;
      bool aboveIsInside = false;
      LL lineResult = 0;
      // get a vector of all the horizontal segments that intersect this row
      vector<HorizontalSegment> ihsegments;
      for (const auto &hsegment: hsegments) {
        if (!hsegment.intersects(row)) continue;
        ihsegments.push_back(hsegment);
      }
      int nextHsegIdx = 0;
      for (auto &vsegment: vsegments) {
        if (!vsegment.intersects(row)) continue;
        // copy this bit after the for loop too
        while (nextHsegIdx < ihsegments.size() && vsegment.col > ihsegments[nextHsegIdx].col) {
          interweaveHorizontalSegment(ihsegments[nextHsegIdx], inside, aboveIsInside, startInside, lineResult);
          nextHsegIdx++;
        }
        interweaveVerticalSegment(row, vsegment, inside, aboveIsInside, startInside, lineResult);
      }
      while (nextHsegIdx < ihsegments.size()) {
        interweaveHorizontalSegment(ihsegments[nextHsegIdx], inside, aboveIsInside, startInside, lineResult);
        nextHsegIdx++;
      }
      // cout << "row: " << row << " lineResult: " << lineResult << endl << endl;
      lastlineResult = lineResult;
      result += lineResult;
    }
    return result;
  }

  static int hexToInt(const string &hex) {
    int result = 0;
    for (char i: hex) {
      result *= 16;
      if (i >= '0' && i <= '9') {
        result += i - '0';
      } else {
        result += i - 'a' + 10;
      }
    }
    return result;
  }

  LL solution() {
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
    set<int> tempActionRows;
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      char direction;
      int steps;
      string color;
      stringstream ss(line);
      ss >> direction >> steps >> color;
      int distance = hexToInt(color.substr(2, 5));
      int dir = stoi(color.substr(7, 1));
      // overwrite with the new amounts gained from the color string
      steps = distance;
      direction = dirToChar.at(dir);
      tempActionRows.insert(row);

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

      previousDirection = direction;
      row = nrow;
      col = ncol;
    }

    // Set the connections for the first segment based on previousDirection (= the last segment)
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

    // set actionRows to be tempActionRows (because of C++, this is already sorted)
    actionRows = vector<int>(tempActionRows.begin(), tempActionRows.end());

    // sort the segments
    sort(hsegments.begin(), hsegments.end());
    sort(vsegments.begin(), vsegments.end());

    // cout << "boundary : " << boundary << endl;
    return calcInterior() + boundary;
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
