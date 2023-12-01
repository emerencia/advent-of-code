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

  int solution() {
    int result = 0;
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      string number = "";
      for (int i=0;i<line.size();i++)
        if (line[i] >= '0' && line[i] <= '9') {
          number += line[i];
          break;
        }
      for (int i=line.size()-1;i>=0;i--)
        if (line[i] >= '0' && line[i] <= '9') {
          number += line[i];
          break;
        }
      int calLine;
      istringstream(number) >> calLine;
      result += calLine;
    }
    return result;
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
