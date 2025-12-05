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
    ranges.emplace_back(start, end);
  }

  bool isFresh(const LL ingredientId) const {
    for (const auto &range : ranges) {
      if (ingredientId >= range.first && ingredientId <= range.second) {
        return true;
      }
    }
    return false;
  }

  int solution() {
    ranges.clear();
    int result = 0;
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
        result+=isFresh(ingredientId);
      }
    }
    return result;
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
