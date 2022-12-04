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
#include <cstdio>

using namespace std;
typedef long long LL;
typedef pair<int, int> PII;


class Assignment {
public:

  bool overlapping(int a, int b, int c, int d) {
    // beginning or end falls in between beginning to end of the other range, so four cases.
    return (a >= c && a <= d) || (b >= c && b <= d) || (c >= a && c <= b) || (d >= a && d <= b);
  }


  int solution() {
    int result = 0;
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      int a, b, c, d;
      sscanf(line.c_str(),"%d-%d,%d-%d",&a,&b,&c,&d);
      result += overlapping(a,b,c,d);
    }
    return result;
  };
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
