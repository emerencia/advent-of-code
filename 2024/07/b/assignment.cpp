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
  bool canbeTrue(const vector<int> &numbers, LL output, LL sum, int index) {
    if (index == numbers.size()) {
      return sum == output;
    }
    stringstream s;
    s << sum << numbers[index];
    LL concatenation = stoll(s.str());
    return canbeTrue(numbers, output, sum + numbers[index], index + 1) ||
           canbeTrue(numbers, output, sum * numbers[index], index + 1) ||
           canbeTrue(numbers, output, concatenation, index + 1);
  }

  LL solution() {
    LL result = 0;
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      stringstream ss(line);
      LL output;
      char c;
      vector<int> numbers;
      ss >> output >> c;
      while (ss.good()) {
        int i;
        ss >> i;
        numbers.push_back(i);
      }
      if (canbeTrue(numbers, output, numbers[0], 1)) {
        result += output;
      }
    }
    return result;
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
