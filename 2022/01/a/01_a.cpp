#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>
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

using namespace std;
typedef long long LL;
typedef pair<int, int> PII;


class A01 {
public:

  int mostCalories() {
    int maxCals = 0;
    int curCals = 0;
    string str;
    while (getline(cin, str) && cin.good()) {
      if (!str.size()) {
        curCals = 0;
      } else {
        int calLine;
        istringstream(str) >> calLine;
        curCals += calLine;
        if (curCals > maxCals) {
          maxCals = curCals;
        }
      }
    }
    return maxCals;
  };
};

using namespace std;

int main() {
  A01 obj;
  cout << obj.mostCalories() << endl;
}
