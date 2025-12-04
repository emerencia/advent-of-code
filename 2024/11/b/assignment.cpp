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

constexpr int NR_BLINKS = 75;
constexpr int MULTIPLIER = 2024;

constexpr int LIMIT = 30000;

LL mem[LIMIT + 1][76];

class Assignment {
public:
  vector<LL> stones;

  static bool numberHasEvenNumberOfDigits(LL n) {
    int count = 0;
    while (n > 0) {
      n /= 10;
      count++;
    }
    return count % 2 == 0;
  }

  static LL blinkStone(const LL stone, const int stepsRemaining) {
    if (stepsRemaining == 0) {
      return 1;
    }
    if (stone < LIMIT && mem[stone][stepsRemaining] != -1) {
      return mem[stone][stepsRemaining];
    }
    LL result;
    if (stone == 0) {
      result = blinkStone(1, stepsRemaining - 1);
    } else if (numberHasEvenNumberOfDigits(stone)) {
      const string s = to_string(stone);
      const LL stone1 = stoll(s.substr(0, s.size() / 2));
      const LL stone2 = stoll(s.substr(s.size() / 2));
      result = blinkStone(stone1, stepsRemaining - 1) + blinkStone(stone2, stepsRemaining - 1);
    } else {
      result = blinkStone(stone * MULTIPLIER, stepsRemaining - 1);
    }
    if (stone < LIMIT) {
      mem[stone][stepsRemaining] = result;
    }
    return result;
  }

  LL solution() {
    LL result = 0;
    stones.clear();
    memset(mem, -1, sizeof(mem));
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      stringstream ss(line);
      LL n;
      while (ss >> n) {
        stones.push_back(n);
      }
    }
    for (const LL stone: stones) {
      result += blinkStone(stone, NR_BLINKS);
    }
    return result;
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
