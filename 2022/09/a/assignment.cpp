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

  bool withinRange(PII a, PII b) {
    return (a.first >= (b.first - 1) && a.first <= (b.first + 1) &&
        a.second >= (b.second - 1) && a.second <= (b.second + 1));
  }

  int solution() {
    set<PII> visited;

    // first = left, right
    // second = up, down
    // ..U...
    // .LsR..
    // ..D...
    PII head = {0, 0};
    PII tail = {0, 0};

    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      char direction;
      int distance;
      stringstream s(line);
      s >> direction >> distance;

      for (int i = 0; i < distance; i++) {
        PII oldPos = head;
        if (direction == 'R') {
          head = {head.first + 1, head.second};
        } else if (direction == 'U') {
          head = {head.first, head.second + 1};
        } else if (direction == 'L') {
          head = {head.first - 1, head.second};
        } else if (direction == 'D') {
          head = {head.first, head.second - 1};
        }
        if (!withinRange(head, tail)) {
          tail = oldPos;
        }
        visited.insert({tail.first,tail.second});
      }
    }
    return visited.size();
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
