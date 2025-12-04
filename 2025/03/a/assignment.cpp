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

  int processBank(const string& line) {
    int maxx = -1;
    // find the highest number in the string from pos 0 to end -1
    for (char c : line.substr(0, line.size() - 1)) {
      maxx = max(maxx, c - '0');
    }
    // now find the highest number that's positioned in the string after the position of maxx
    int max2 = -1;
    for (size_t i = line.find(to_string(maxx)) + 1; i < line.size(); ++i) {
      max2 = max(max2, line[i] - '0');
    }
    // cout << "Processing line: " << line << " -> " << maxx << ", " << max2 << endl;
    return maxx * 10 + max2;
  }

  int solution() {
    int result = 0;
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      result+= processBank(line);
    }
    return result;
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
