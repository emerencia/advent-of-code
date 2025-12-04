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

  LL processBank(const string& line, int n) {
    LL result = 0;
    int lastpos = 0;
    for (int i = 0;i < n; ++i) {
      // find the highest number in the string from pos lastpos to end - n
      LL maxx = -1;
      // cout << "Substring: " << line.substr(lastpos, line.size() - lastpos - n + i + 1) << endl;
      int j = lastpos;
      int newlastpos = lastpos;
      for (char c : line.substr(lastpos, line.size() - lastpos - n + i + 1)) {
        if (c - '0' > maxx) {
          maxx = c - '0';
          newlastpos = j + 1;
        }
        j++;
      }
      lastpos = newlastpos;
      result = result * 10 + maxx;
    }
    // cout << "Processed line: " << line << " to " << result << endl;
    return result;
  }

  LL solution() {
    LL result = 0;
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      result+= processBank(line, 12);
    }
    return result;
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
