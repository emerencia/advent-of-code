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

constexpr int NR_BLINKS = 25;
constexpr int MULTIPLIER = 2024;

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

  void blinkStones() {
    vector<LL> newStones;
    for (const LL stone: stones) {
      if (stone == 0) {
        newStones.push_back(1);
      } else if (numberHasEvenNumberOfDigits(stone)) {
        string s = to_string(stone);
        newStones.push_back(stoll(s.substr(0, s.size() / 2)));
        newStones.push_back(stoll(s.substr(s.size() / 2)));
      } else {
        newStones.push_back(stone * MULTIPLIER);
      }
    }
    stones = newStones;
  }

  int solution() {
    stones.clear();
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
    for (int i = 0; i < NR_BLINKS; ++i) {
      blinkStones();
    }
    /*
    for (LL stone : stones) {
      cout << stone << " ";
    }
    cout << endl;
    */
    return static_cast<int>(stones.size());
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
