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
const int CENTER2 = 1;
int reachable[22][22][22];
int iscube[22][22][22];
int seen[22][22][22];

class Assignment {
public:

  void markMissingNeighbors(const PIII &cube) {
    int x = cube.first.first;
    int y = cube.first.second;
    int z = cube.second;

    iscube[x+CENTER2][y+CENTER2][z+CENTER2] = 1;
  }

  int isReachable(int x, int y, int z) {
    // if we reached the outside, we are reachable
    if (x < 0 || x >= 22 || y < 0 || y >= 22 || z < 0 || z >= 22) return 1;
    if (iscube[x][y][z]) return 0;
    // if we got here from another route first, prefer that one
    if (seen[x][y][z]) return 0;
    seen[x][y][z] = 1;
    int &r = reachable[x][y][z];
    if (isReachable(x + 1, y, z)) return r = 1;
    if (isReachable(x - 1, y, z)) return r = 1;
    if (isReachable(x, y + 1, z)) return r = 1;
    if (isReachable(x, y - 1, z)) return r = 1;
    if (isReachable(x, y, z + 1)) return r = 1;
    if (isReachable(x, y, z - 1)) return r = 1;
    return r = 0;
  }

  LL solution() {
    vector<PIII> cubes;
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
    memset(iscube, 0, sizeof(iscube));
    memset(reachable, -1, sizeof(reachable));
    for (int i = 0; i < cubes.size(); i++) {
      markMissingNeighbors(cubes[i]);
    }
    cout << maxint << endl << flush;
    LL result = 0;
    for (int i = 0; i < cubes.size(); i++) {
      int x = cubes[i].first.first;
      int y = cubes[i].first.second;
      int z = cubes[i].second;
      memset(seen, 0, sizeof(seen));
      result += isReachable(x - 1 + CENTER2, y + CENTER2, z + CENTER2);
      memset(seen, 0, sizeof(seen));
      result += isReachable(x + 1 + CENTER2, y + CENTER2, z + CENTER2);
      memset(seen, 0, sizeof(seen));
      result += isReachable(x + CENTER2, y + 1 + CENTER2, z + CENTER2);
      memset(seen, 0, sizeof(seen));
      result += isReachable(x + CENTER2, y - 1 + CENTER2, z + CENTER2);
      memset(seen, 0, sizeof(seen));
      result += isReachable(x + CENTER2, y + CENTER2, z + 1 + CENTER2);
      memset(seen, 0, sizeof(seen));
      result += isReachable(x + CENTER2, y + CENTER2, z - 1 + CENTER2);
    }

    return result;
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
