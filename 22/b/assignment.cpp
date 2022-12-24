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
typedef pair<pair<int, int>, int> PIII;


// row, column

vector<PII> ds({{0,  1},  // RIGHT
                {1,  0},  // DOWN
                {0,  -1}, // LEFT
                {-1, 0}});// UP
vector<string> grid;

const int RIGHT = 0;
const int DOWN = 1;
const int LEFT = 2;
const int UP = 3;

struct Field {
  int rightEdgeCol;
  int leftEdgeCol;
  int upperEdgeRow;
  int lowerEdgeRow;

  Field(int rightEdgeCol, int leftEdgeCol, int upperEdgeRow, int lowerEdgeRow) :
      rightEdgeCol(rightEdgeCol), leftEdgeCol(leftEdgeCol), upperEdgeRow(upperEdgeRow), lowerEdgeRow(lowerEdgeRow) {
  }

  PII toOffsets(int row, int col) const {
    return {row - upperEdgeRow, col - leftEdgeCol};
  }

  int toRow(int rowOffset) const {
    return rowOffset + upperEdgeRow;
  }

  int toCol(int colOffset) const {
    return colOffset + leftEdgeCol;
  }
};

const Field ONE(149, 100, 0, 49);
const Field TWO(99, 50, 0, 49);
const Field THREE(99, 50, 50, 99);
const Field FOUR(99, 50, 100, 149);
const Field FIVE(49, 0, 100, 149);
const Field SIX(49, 0, 150, 199);

class Assignment {
public:
  bool inField(int row, int col, const Field &field) {
    return (row >= field.upperEdgeRow && row <= field.lowerEdgeRow && col >= field.leftEdgeCol &&
            col <= field.rightEdgeCol);
  }

  int invertOffset(int offset) {
    return 49 - offset;
  }

  PIII nextFieldOneDir(int row, int col, int di) {
    PII offsets = ONE.toOffsets(row, col);
    // if on right edge going right
    if (di == RIGHT && col == ONE.rightEdgeCol) {
      return {{FOUR.toRow(invertOffset(offsets.first)), FOUR.rightEdgeCol}, LEFT};
    }
    // if on top edge going up
    if (di == UP && row == ONE.upperEdgeRow) {
      return {{SIX.lowerEdgeRow, SIX.toCol(offsets.second)}, UP};
    }
    // if on bottom edge going down
    if (di == DOWN && row == ONE.lowerEdgeRow) {
      return {{THREE.toRow(offsets.second), THREE.rightEdgeCol}, LEFT};
    }
    // else return default
    return {{row + ds[di].first, col + ds[di].second}, di};
  }

  PIII nextFieldTwoDir(int row, int col, int di) {
    PII offsets = TWO.toOffsets(row, col);
    // if on left edge going left
    if (di == LEFT && col == TWO.leftEdgeCol) {
      return {{FIVE.toRow(invertOffset(offsets.first)), FIVE.leftEdgeCol}, RIGHT};
    }
    // if on top edge going up
    if (di == UP && row == TWO.upperEdgeRow) {
      return {{SIX.toRow(offsets.second), SIX.leftEdgeCol}, RIGHT};
    }
    // else return default
    return {{row + ds[di].first, col + ds[di].second}, di};
  }

  PIII nextFieldThreeDir(int row, int col, int di) {
    PII offsets = THREE.toOffsets(row, col);
    // if on left edge going left
    if (di == LEFT && col == THREE.leftEdgeCol) {
      return {{FIVE.upperEdgeRow, FIVE.toCol(offsets.first)}, DOWN};
    }
    // if on right edge going right
    if (di == RIGHT && col == THREE.rightEdgeCol) {
      return {{ONE.lowerEdgeRow, ONE.toCol(offsets.first)}, UP};
    }

    // else return default
    return {{row + ds[di].first, col + ds[di].second}, di};
  }

  PIII nextFieldFourDir(int row, int col, int di) {
    PII offsets = FOUR.toOffsets(row, col);
    // if on right edge going right
    if (di == RIGHT && col == FOUR.rightEdgeCol) {
      return {{ONE.toRow(invertOffset(offsets.first)), ONE.rightEdgeCol}, LEFT};
    }
    // if on lower edge going down
    if (di == DOWN && row == FOUR.lowerEdgeRow) {
      return {{SIX.toRow(offsets.second), SIX.rightEdgeCol}, LEFT};
    }
    // else return default
    return {{row + ds[di].first, col + ds[di].second}, di};
  }

  PIII nextFieldFiveDir(int row, int col, int di) {
    PII offsets = FIVE.toOffsets(row, col);
    // if on upper edge going up
    if (di == UP && row == FIVE.upperEdgeRow) {
      return {{THREE.toRow(offsets.second), THREE.leftEdgeCol}, RIGHT};
    }
    // if on left edge going left
    if (di == LEFT && col == FIVE.leftEdgeCol) {
      return {{TWO.toRow(invertOffset(offsets.first)), TWO.leftEdgeCol}, RIGHT};
    }
    // else return default
    return {{row + ds[di].first, col + ds[di].second}, di};
  }

  PIII nextFieldSixDir(int row, int col, int di) {
    PII offsets = SIX.toOffsets(row, col);
    // if on left edge going left
    if (di == LEFT && col == SIX.leftEdgeCol) {
      return {{TWO.upperEdgeRow, TWO.toCol(offsets.first)}, DOWN};
    }
    // if on bottom edge going down
    if (di == DOWN && row == SIX.lowerEdgeRow) {
      return {{ONE.upperEdgeRow, ONE.toCol(offsets.second)}, DOWN};
    }
    // if on right edge going right
    if (di == RIGHT && col == SIX.rightEdgeCol) {
      return {{FOUR.lowerEdgeRow, FOUR.toCol(offsets.first)}, UP};
    }
    // else return default
    return {{row + ds[di].first, col + ds[di].second}, di};
  }

  PIII nextDir(int row, int col, int di) {
    if (inField(row, col, ONE)) return nextFieldOneDir(row, col, di);
    if (inField(row, col, TWO)) return nextFieldTwoDir(row, col, di);
    if (inField(row, col, THREE)) return nextFieldThreeDir(row, col, di);
    if (inField(row, col, FOUR)) return nextFieldFourDir(row, col, di);
    if (inField(row, col, FIVE)) return nextFieldFiveDir(row, col, di);
    if (inField(row, col, SIX)) return nextFieldSixDir(row, col, di);
    cout << "ERROR: not in field!" << endl;
    return {{-1, -1}, -1};
  }

  int walk(int row, int col, int di, const string &password) {
    int pIdx = 0;
    while (pIdx < password.size()) {
      if (password[pIdx] == 'R') {
        di = (di + 1) % 4;
        pIdx++;
      } else if (password[pIdx] == 'L') {
        di = (di + 3) % 4;
        pIdx++;
      } else {
        string num;
        while (pIdx < password.size() && password[pIdx] >= '0' && password[pIdx] <= '9') {
          num += password[pIdx++];
        }
        stringstream s(num);
        int steps;
        s >> steps;
        for (int i = 0; i < steps; i++) {
          PIII nextpos = nextDir(row, col, di);

          // you can add error cecking here that it is never oob or spcce
          if (grid[nextpos.first.first][nextpos.first.second] == '.') {
            row = nextpos.first.first;
            col = nextpos.first.second;
            di = nextpos.second;
          } else {
            break;
          }
        }
      }
    }
    return 1000 * (row + 1) + 4 * (col + 1) + di;
  }

  int solution() {
    int maxlength = 0;
    string password;
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      if (line[0] >= '0' && line[0] <= '9') {
        password = line;
      } else {
        grid.push_back(line);
      }
      maxlength = max((size_t) maxlength, line.size());
    }
    int firstopen = -1;
    for (int j = 0; j < grid[0].size(); j++) {
      if (grid[0][j] == ' ') continue;
      firstopen = j;
      break;
    }

    return walk(0, firstopen, 0, password);
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
