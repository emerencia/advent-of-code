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

// 12:52
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;

class Assignment {
public:

  static int processLine(int &dial, const string &line) {
    // read L or R and number
    char direction;
    int numberRotations;
    istringstream iss(line);
    iss >> direction >> numberRotations;
    if (direction == 'L') {
      dial = (dial - (numberRotations)%100 + 100)%100;
    } else { // direction == 'R'
      dial = (dial + numberRotations)%100;
    }
    return (dial == 0);
  }

  static int solution() {
    int result = 0;
    int dial = 50;
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;
      result += processLine(dial, line);
    }
    return result;
  }
};

int main() {
  cout << Assignment::solution() << endl;
}
