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

  static int hashValue(const string &s) {
    int currentValue = 0;
    for (char i: s) {
      currentValue += i;
      currentValue *= 17;
      currentValue %= 256;
    }
    return currentValue;
  }

  static int solution() {
    int result = 0;
    if (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) {
        cout << "line empty" << endl;
        exit(1);
      }
      // split line by commas
      stringstream ss(line);
      string token;
      while (getline(ss, token, ',')) {
        result += hashValue(token);
      }
    }
    return result;
  }
};

int main() {
  cout << Assignment::solution() << endl;
}
