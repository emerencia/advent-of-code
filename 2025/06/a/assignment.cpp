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
  vector<vector<string> > data;
public:

  LL processData() const {
    const size_t numberOfCalculations = data[0].size();
    LL result = 0;
    for (int i = 0;i < numberOfCalculations; ++i) {
      string operation = data[data.size() - 1][i];
      if (operation == "*") {
        LL cur = stoll(data[0][i]);
        for (int j = 1;j < data.size() - 1; ++j) {
          cur *= stoll(data[j][i]);
        }
        result += cur;
      } else if (operation == "+") {
        LL cur = stoll(data[0][i]);
        for (int j = 1;j < data.size() - 1; ++j) {
          cur += stoll(data[j][i]);
        }
        result += cur;
      } else {
        cout << "Unknown operation: " << operation << endl;
        exit(1);
      }
    }
    return result;
  }

  LL solution() {
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      stringstream ss(line);
      string token;
      vector<string> tokens;
      while (ss >> token) {
        tokens.push_back(token);
      }
      data.push_back(tokens);
    }
    return processData();
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
