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


class B01 {
public:

  int mostCalories() {
    vector<int> calTotals;
    calTotals.push_back(0);
    calTotals.push_back(0);
    calTotals.push_back(0);
    int curCals = 0;
    string str;
    while (getline(cin, str) && cin.good()) {
      if (!str.size()) {
        calTotals.push_back(curCals);
        curCals = 0;
      } else {
        int calLine;
        istringstream(str) >> calLine;
        curCals += calLine;
      }
    }
    calTotals.push_back(curCals);
    sort(calTotals.rbegin(), calTotals.rend());
    return calTotals[0]+calTotals[1]+calTotals[2];
  };
};

using namespace std;

int main() {
  B01 obj;
  cout << obj.mostCalories() << endl;
}
