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
  map<int, vector<int> > before;
  map<int, vector<int> > after;

  bool validUpdate(const vector<int> &update) {
    for (int i = 0; i < update.size(); ++i) {
      int nbefore = update[i];
      for (int j = i + 1; j < update.size(); ++j) {
        int nafter = update[j];
        if (find(after[nafter].begin(), after[nafter].end(), nbefore) != after[nafter].end()) {
          return false;
        }
        if (find(before[nbefore].begin(), before[nbefore].end(), nafter) != before[nbefore].end()) {
          return false;
        }
      }
    }
    return true;
  }

  int solution() {
    int result = 0;
    before.clear();
    after.clear();
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) break;

      int nbefore, nafter;;
      sscanf(line.c_str(), "%d|%d", &nbefore, &nafter);

      before[nafter].push_back(nbefore);
      after[nbefore].push_back(nafter);
    }

    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      vector<int> update;
      stringstream ss(line);
      int n;
      char c;
      while (ss >> n) {
        update.push_back(n);
        ss >> c;
      }
      if (validUpdate(update)) {
        result += update[update.size() / 2];
      }
    }
    return result;
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
