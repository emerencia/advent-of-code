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

  static int digitsInNumber(LL number) {
    int digits = 0;
    while (number > 0) {
      digits++;
      number /= 10;
    }
    return digits;
  }

  static LL doubleANumber(LL number) {
    LL result = 0;
    int digits = digitsInNumber(number);
    for (int i = 0; i < digits; i++) {
      result *= 10;
      result += (number / (LL)pow(10, digits - 1 - i)) % 10;
    }
    for (int i = 0; i < digits; i++) {
      result *= 10;
      result += (number / (LL)pow(10, digits - 1 - i)) % 10;
    }
    return result;
  }

  static LL firstHalfOfNumber(LL number) {
    LL result = 0;
    int digits = digitsInNumber(number);
    for (int i = 0; i < digits/2; i++) {
      result *= 10;
      result += (number / (LL)pow(10, digits - 1 - i)) % 10;
    }
    return result;
  }

  static LL invalidIdsInRange(const string &range) {
    // parse the range
    const size_t dashPos = range.find('-');
    LL start = 0, end = 0;
    if (dashPos == string::npos) {
      cout << "Error: this should not happen, single range: " << range << endl;
      exit(1);
    }
    start = stoll(range.substr(0, dashPos));
    end = stoll(range.substr(dashPos + 1));
    // cout << "\n\nProcessing range: " << start << " - " << end << endl;
    // Start at the first even length number higher than start but lower or equal to end
    LL cur = start;
    if ((digitsInNumber(cur) % 2) == 1) {
      int digits = digitsInNumber(start);
      cur = 1;
      for (int i = 0; i < digits; i++) {
        cur *= 10;
      }
      if (cur > end) {
        // cout << "cur is now " << cur << ", which is greater than end " << end << ", so no invalid IDs in range " << range << endl;
        return 0;
      }
      if (cur < start) {
        cout << "Error: this should not happen, cur is less than start" << range << endl;
        exit(1);
      }
      // cout << "cur is now" << cur << endl;
    }
    // Now cur is even length
    // read the first half of cur
    LL firstHalf = firstHalfOfNumber(cur);
    // cout << "firstHalf of " << cur << " is " << firstHalf << endl;
    LL result = 0;
    while (doubleANumber(firstHalf) < start) {
      firstHalf++;
    }
    while (doubleANumber(firstHalf) <= end) {
      result += doubleANumber(firstHalf);
      firstHalf++;
    }
    // cout << "Invalid IDs in range " << range << " is " << result << endl;
    return result;
  }

  static LL invalidIds(const string &line) {
    // tokennize the line into ranges by comma's.
    LL result = 0;
    stringstream ss(line);
    string token;
    while (getline(ss, token, ',')) {
      result += invalidIdsInRange(token);
    }
    return result;
  }

  static LL solution() {
    LL result = 0;
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      result += invalidIds(line);
    }
    return result;
  }
};

int main() {
  cout << Assignment::solution() << endl;
}
