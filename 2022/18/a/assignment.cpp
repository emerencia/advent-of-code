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
typedef pair<PII, int> PIII;

// The number of sides this cube is missing.
// Note that a side is only shared between two cubes.
const int CENTER = 50;
int missing[100][100][100];

class Assignment {
public:

  void markMissingNeighbors(const PIII& cube) {
    int x = cube.first.first;
    int y = cube.first.second;
    int z = cube.second;

    missing[CENTER + x + 1][CENTER + y][CENTER + z]++;
    missing[CENTER + x - 1][CENTER + y][CENTER + z]++;
    missing[CENTER + x][CENTER + y + 1][CENTER + z]++;
    missing[CENTER + x][CENTER + y - 1][CENTER + z]++;
    missing[CENTER + x][CENTER + y][CENTER + z + 1]++;
    missing[CENTER + x][CENTER + y][CENTER + z - 1]++;
  }

  LL solution() {
    vector<PIII> cubes;
    memset(missing, 0, sizeof(missing));
    int maxint = INT_MIN;
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      int first, second, third;
      sscanf(line.c_str(), "%i,%i,%i", &first, &second, &third);
      if (first > maxint) maxint = first;
      if (second > maxint) maxint = second;
      if (third > maxint) maxint = third;
      cubes.push_back({{first, second}, third});
    }
    /*
    for (int i = 0; i < cubes.size(); i++) {
      cout << cubes[i].first.first << " :: " << cubes[i].first.second << " :: " << cubes[i].second << endl;
    }
    */
    for (int i=0;i<cubes.size();i++) {
      markMissingNeighbors(cubes[i]);
    }
    cout << maxint << endl << flush;
    LL result = 0;
    for (int i=0;i<cubes.size();i++) {
      int x = cubes[i].first.first;
      int y = cubes[i].first.second;
      int z = cubes[i].second;
      result += 6 - missing[CENTER + x][CENTER + y][CENTER + z];
    }
    return result;
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
