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

  int checkAdd(int cycle, int x) {
    if (cycle == 20 || (cycle > 20 && (cycle - 20)%40 == 0)) {
      // cout << "cycle: " << cycle << ", x: " << x << ", signal: " << cycle*x << endl;
      return cycle * x;
    }
    return 0;
  }

  int solution() {
    int result = 0;
    int x = 1;
    int cycle = 1;
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      stringstream s(line);
      string operation;
      s >> operation;
      if (operation == "noop") {
        // do nothing
        result += checkAdd(cycle, x);
        cycle++;
      } else {
        int amount;
        s >> amount;
        result += checkAdd(cycle, x);
        cycle++;
        result += checkAdd(cycle, x);
        cycle++;
        x += amount;
      }
    }
    return result;
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
