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

// row col
vector<PII> directions = {{-1, 0},
                          {1,  0},
                          {0,  -1},
                          {0,  1}};
vector<vector<PII>> checks = {{{-1, 0},  {-1, 1},  {-1, -1}}, // north
                              {{1,  0},  {1,  1},  {1,  -1}}, // south
                              {{0,  -1}, {-1, -1}, {1,  -1}}, // west
                              {{0,  1},  {-1, 1},  {1,  1}}}; // east
vector<PII> all_eight = {{-1, -1},
                         {-1, 0},
                         {-1, 1},
                         {0,  -1},
                         {0,  1},
                         {1,  -1},
                         {1,  0},
                         {1,  1}};

class Assignment {
public:
  set<PII> elves;

  LL emptyGroundTiles() {
    int mincol = 100000000, minrow = 100000000, maxcol = -100000000, maxrow = -100000000;
    for (auto it = elves.begin(); it != elves.end(); it++) {
      const PII elf = *it;
      if (elf.first < minrow) minrow = elf.first;
      if (elf.first > maxrow) maxrow = elf.first;
      if (elf.second < mincol) mincol = elf.second;
      if (elf.second > maxcol) maxcol = elf.second;
    }
    LL surface = ((LL) maxrow - minrow + 1) * (maxcol - mincol + 1);
    return surface - (LL) (elves.size());
  }

  bool isFree(PII elf) {
    for (int i = 0; i < all_eight.size(); i++) {
      PII newpos = {elf.first + all_eight[i].first, elf.second + all_eight[i].second};
      if (elves.count(newpos) > 0) return false;
    }
    return true;
  }

  void doRound(int di) {
    map<PII, vector<PII>> proposed; // proposed[new] = {old, old2, ...};
    for (auto it = elves.begin(); it != elves.end(); ++it) {
      const PII elf = *it;
      if (isFree(elf)) {
        proposed[elf].push_back(elf);
        continue;
      }
      // try to move north etc.
      bool inserted = false;
      for (int i = 0; i < 4; i++) {
        int ddi = (di + i) % 4; // direction
        bool taken = false;
        for (int j = 0; j < checks[ddi].size(); j++) {
          PII check = checks[ddi][j];
          if (elves.count({elf.first + check.first, elf.second + check.second}) > 0) {
            taken = true;
            break;
          }
        }
        if (!taken) {
          proposed[{elf.first + directions[ddi].first, elf.second + directions[ddi].second}].push_back(elf);
          inserted = true;
          break;
        }
      }
      if (!inserted) {
        // still put back the old value
        proposed[elf].push_back(elf);
      }
    }

    set<PII> new_elves;
    for (auto it = proposed.begin(); it != proposed.end(); ++it) {
      if (it->second.size() == 1) {
        new_elves.insert(it->first);
      } else {
        for (int i = 0; i < it->second.size(); i++) {
          new_elves.insert(it->second[i]);
        }
      }
    }
    elves = new_elves;
  }

  void printElves() {
    int mincol = 100000000, minrow = 100000000, maxcol = -100000000, maxrow = -100000000;
    for (auto it = elves.begin(); it != elves.end(); it++) {
      const PII elf = *it;
      if (elf.first < minrow) minrow = elf.first;
      if (elf.first > maxrow) maxrow = elf.first;
      if (elf.second < mincol) mincol = elf.second;
      if (elf.second > maxcol) maxcol = elf.second;
    }
    for (int i = minrow; i <= maxrow; i++) {
      for (int j = mincol; j <= maxcol; j++) {
        if (elves.count({i, j})) {
          cout << '#';
        } else {
          cout << '.';
        }
      }
      cout << endl;
    }
  }

  LL solution() {
    elves.clear();
    int row = 0;

    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      for (int col = 0; col < line.size(); col++) {
        if (line[col] == '#') {
          elves.insert({row, col});
        }
      }

      row++;
    }
    for (int i = 0; i < 10; i++) {
      int di = i % 4;
      doRound(di);
    }
    return emptyGroundTiles();
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
