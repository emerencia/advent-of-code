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
  static bool isReportSafe(const vector<int> &report) {
    // 1 is increasing, -1 is decreasing, 0 is unknown
    int direction = 0;
    int prev = report[0];
    int cur = -1;
    for (int i = 1; i < report.size(); ++i) {
      cur = report[i];
      int diff = abs(cur - prev);
      if (diff > 3 || diff == 0) {
        return false;
      }
      if (direction == 0) {
        if (prev < cur) {
          direction = 1;
        } else {
          direction = -1;
        }
      } else if (direction == 1) {
        if (prev > cur) {
          return false;
        }
      } else {
        if (prev < cur) {
          return false;
        }
      }
      prev = cur;
    }
    return true;
  }

  static int solution() {
    int result = 0;
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      vector<int> report;
      stringstream ss(line);
      int x;
      while (ss >> x) {
        report.push_back(x);
      }
      for (int i = 0; i < report.size(); ++i) {
        vector<int> report2;
        for (int j = 0; j < report.size(); ++j) {
          if (j != i) {
            report2.push_back(report[j]);
          }
        }
        if (isReportSafe(report2)) {
          result++;
          break;
        }
      }
    }
    return result;
  }
};

int main() {
  cout << Assignment::solution() << endl;
}
