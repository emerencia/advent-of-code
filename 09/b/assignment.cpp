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

  void moveTo(PII& toBeMoved, PII& target) {
    // no need cos we know they aint within range
    // if (toBeMoved.first == target.first && toBeMoved.second == target.second) return;
    if (toBeMoved.first == target.first) {
      // move second in the direction
      if (target.second > toBeMoved.second) {
        // toBeMoved.second = target.second - 1;
        toBeMoved.second++;
      } else {
        // toBeMoved.second = target.second + 1;
        toBeMoved.second--;
      }
    } else if (toBeMoved.second == target.second) {
      if (target.first > toBeMoved.first) {
        //toBeMoved.first = target.first - 1;
        toBeMoved.first++;
      } else {
        // toBeMoved.first = target.first + 1;
        toBeMoved.first--;
      }
    } else { // move diagonally
      if (target.first > toBeMoved.first && target.second > toBeMoved.second) {
        toBeMoved.first++;
        toBeMoved.second++;
      } else if (target.first < toBeMoved.first && target.second < toBeMoved.second) {
        toBeMoved.first--;
        toBeMoved.second--;
      } else if (target.first > toBeMoved.first && target.second < toBeMoved.second) {
        toBeMoved.first++;
        toBeMoved.second--;
      } else {
        toBeMoved.first--;
        toBeMoved.second++;
      }
    }
  }

  int solution() {
    set<PII> visited;

    // first = left, right
    // second = up, down
    // ..U...
    // .LsR..
    // ..D...
    vector<PII> knots(10,{0,0});

    // Index 0 = head
    // index knots.size()-1 = tail

    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      char direction;
      int distance;
      stringstream s(line);
      s >> direction >> distance;

      for (int i = 0; i < distance; i++) {
        //PII oldPos;
       // PII newPos;
        //oldPos = knots[0];
        if (direction == 'R') {
          knots[0] = {knots[0].first + 1, knots[0].second};
        } else if (direction == 'U') {
          knots[0] = {knots[0].first, knots[0].second + 1};
        } else if (direction == 'L') {
          knots[0] = {knots[0].first - 1, knots[0].second};
        } else if (direction == 'D') {
          knots[0] = {knots[0].first, knots[0].second - 1};
        }
        for (int j = 1; j < knots.size(); j++) {
          //newPos = knots[j];
          if (!withinRange(knots[j - 1], knots[j])) {
            moveTo(knots[j], knots[j-1]);
            //knots[j] = oldPos;
          }
          //oldPos = newPos;
        }
        visited.insert({knots[knots.size()-1].first,knots[knots.size() - 1].second});
      }
    }
    return visited.size();
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
