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
typedef pair<LL, LL> PLL;

class Assignment {
  vector<PLL> ranges;
public:

  void readRange(const string &line) {
    stringstream ss(line);
    LL start, end;
    char dash;
    ss >> start >> dash >> end;
    mergeRange(start, end);
  }

  static bool overlapsWithRange(const PLL &range, const LL start, const LL end) {
    return !(end < range.first || start > range.second);
  }

  void mergeRange(LL start, LL end) {
    // assumption: all ranges in `ranges` are strictly non-overlapping
    vector<PLL> newRanges;
    for (auto it = ranges.begin(); it != ranges.end();) {
      if (overlapsWithRange(*it, start, end)) {
        start = min(start, it->first);
        end = max(end, it->second);
        it = ranges.erase(it);
      } else {
        ++it;
      }
    }
    ranges.emplace_back(start, end);
  }

  LL totalRangeCount() const {
    LL total = 0;
    for (const auto &range : ranges) {
      total += (range.second - range.first + 1);
    }
    return total;
  }

  LL solution() {
    ranges.clear();
    int phase = 1;
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) {
        phase = 2;
        continue;
      }

      if (phase == 1) {
        readRange(line);
      } else {
        stringstream ss(line);
        LL ingredientId;
        ss >> ingredientId;
      }
    }
    return totalRangeCount();
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
