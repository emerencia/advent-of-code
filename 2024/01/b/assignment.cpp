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
  static int solution() {
    int result = 0;
    vector<int> left;
    map<int, int> right;
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      stringstream ss(line);
      int x, y;
      ss >> x >> y;
      left.push_back(x);
      if (right.find(y) == right.end()) {
        right[y] = 1;
      } else {
        right[y]++;
      }
    }
    for (int i: left) {
      if (right.find(i) != right.end()) {
        result += i * right[i];
      }
    }
    return result;
  }
};

int main() {
  cout << Assignment::solution() << endl;
}
