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

  static LL calculateNextValue(const vector<LL> &history) {
    // create a vector of vectors.
    vector<vector<LL> > dp;
    dp.push_back(history);
    int currentIndex = 0;
    // push a new vector that is the difference between the subsequent values in dp[currentIndex]
    while (true) {
      vector<LL> next;
      for (int i = 1; i < dp[currentIndex].size(); ++i) {
        next.push_back(dp[currentIndex][i] - dp[currentIndex][i - 1]);
      }
      dp.push_back(next);
      ++currentIndex;
      // break if all values of next are 0
      bool allZero = true;
      for (LL i: next) {
        if (i != 0) {
          allZero = false;
          break;
        }
      }
      if (allZero) break;
    }
    // push a zero to the last vector
    dp[dp.size() - 1].push_back(0);
    if (dp.size() > 1) {
      for (int i = (int) dp.size() - 2; i >= 0; --i) {
        dp[i].push_back(dp[i][dp[i].size() - 1] + dp[i + 1][dp[i + 1].size() - 1]);
      }
    }
    // return the last value of the first row of dp
    return dp[0][dp[0].size() - 1];
  }

  static LL solution() {
    LL result = 0;
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      vector<LL> history;
      stringstream ss(line);
      int value;
      while (ss >> value) {
        history.push_back(value);
      }
      result += calculateNextValue(history);
    }
    return result;
  }
};

int main() {
  cout << Assignment::solution() << endl;
}
