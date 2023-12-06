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

struct Race {
  LL time;
  LL distance;

  Race(LL d, LL t) : time(t), distance(d) {}
};

class Assignment {
public:

  static LL numberOfWaysToBeatRecord(const Race &race) {
    double upperLimit = (race.time + sqrt(race.time * race.time - 4 * race.distance)) / 2.0;
    double lowerLimit = (race.time - sqrt(race.time * race.time - 4 * race.distance)) / 2.0;
    // When we match the record, we don't break it, so discount those cases.
    LL upper = (LL) floor(upperLimit - 1e-9);
    LL lower = (LL) ceil(lowerLimit + 1e-9);
    return upper - lower + 1;
  }

  static LL readABigNumber() {
    string line;
    getline(cin, line);
    if (line.empty()) {
      cout << "Error: line empty" << endl;
      exit(1);
    }
    cout << line << endl;
    string numberString = line.substr(line.find(':') + 1);
    // remove all spaces from numberString
    numberString.erase(remove_if(numberString.begin(), numberString.end(), ::isspace), numberString.end());
    return stoll(numberString);
  }

  static LL solution() {
    return numberOfWaysToBeatRecord(Race(readABigNumber(), readABigNumber()));
  }
};

int main() {
  cout << Assignment::solution() << endl;
}
