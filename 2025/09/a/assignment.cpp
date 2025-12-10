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
typedef tuple<LL, int, int> PIII;

class Assignment {
  vector<PII> redTiles;
public:

  LL largestArea() const {
    priority_queue<PIII, vector<PIII>, less<>> q;
    for (int i = 0; i < redTiles.size(); i++) {
      for (int j = i+1;j < redTiles.size();j++) {
        LL dist = abs(redTiles[i].first - redTiles[j].first + 1LL) * abs(redTiles[i].second - redTiles[j].second + 1LL);
        q.emplace(dist, i, j);
      }
    }
    if (q.empty()) return 0;
    PIII top = q.top();
    q.pop();
    return get<0>(top);
  }

  LL solution() {
    redTiles.clear();
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      int row, col;
      sscanf(line.c_str(), "%d,%d", &row, &col);
      redTiles.emplace_back(row, col);
    }
    return largestArea();
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
