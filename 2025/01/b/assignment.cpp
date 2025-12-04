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
    int result = 0;
    istringstream iss(line);
    iss >> direction >> numberRotations;
    while (numberRotations > 0) {
      dial = dial + (direction == 'L' ? -1 : 1);
      if (dial == -1) dial = 99;
      if (dial == 100) dial = 0;
      if (dial == 0) result++;

      numberRotations--;
    }
    return result;
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
