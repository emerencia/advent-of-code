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

  int solution() {
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
    int round = 0;
    set<PII> old_elves;
    do {
      old_elves = elves;
      int di = round % 4;
      doRound(di);
      round++;
    } while (old_elves != elves);
    return round;
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
