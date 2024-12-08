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

class Assignment {
public:
  int addMultiplications(const string &line) {
    int result = 0;
    int i = 0;
    while (i < line.size()) {
      if (i + 4 >= line.size() || line.substr(i, 4) != "mul(") {
        ++i;
        continue;
      }
      i += 4;
      bool foundAnyDigit = false;
      int maxI = i + 3;
      int digit1 = 0;
      while (line[i] >= '0' && line[i] <= '9' && i < maxI) {
        digit1 = digit1 * 10 + (line[i] - '0');
        foundAnyDigit = true;
        ++i;
      }
      if (!foundAnyDigit) {
        continue;
      }
      if (i < line.size() && line[i] == ',') {
        ++i;
      } else {
        continue;
      }
      int digit2 = 0;
      foundAnyDigit = false;
      maxI = i + 3;
      while (line[i] >= '0' && line[i] <= '9' && i < maxI) {
        digit2 = digit2 * 10 + (line[i] - '0');
        foundAnyDigit = true;
        ++i;
      }
      if (!foundAnyDigit) {
        continue;
      }
      if (i < line.size() && line[i] == ')') {
        ++i;
        result += digit1 * digit2;
      }
    }
    return result;
  }

  int solution() {
    int result = 0;
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      result += addMultiplications(line);
    }
    return result;
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
