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

  bool isAllDifferent(vector<char>& window) {
    set<char> windowSet(window.begin(), window.end());
    bool result = window.size() == windowSet.size();
    return result;
  }

  void printWindow(vector<char>& window) {
    for (int i = 0; i < window.size(); i++) {
      cout << window[i];
    }
    cout << endl;
  }

  int startOfPacket(string line) {
    vector<char> window(4);
    int curIdx = 0;
    for (int i = 0;i < line.size();i++) {
      window[curIdx] = line[i];
      if (i > 2) {
        if (isAllDifferent(window)) {
          return i + 1;
        }
      }
      curIdx = (1 + curIdx)%4;
    }
    return -1;
  }
  void solution() {
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;
      cout << startOfPacket(line) << endl;
    }
  };
};

int main() {
  Assignment obj;
  obj.solution();
}
