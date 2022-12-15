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

struct SensorBeacon {
  int sensorX, sensorY, manhattan;

  SensorBeacon(int sensorX, int sensorY, int beaconX, int beaconY) : sensorX(sensorX), sensorY(sensorY) {
    manhattan = abs(beaconX - sensorX) + abs(beaconY - sensorY);
  }
};

const int FACTOR = 4000000;
const int LIMIT = 4000000;

class Assignment {
public:

  bool isUnseen(int x, int y, vector<SensorBeacon> &v) {
    for (int i = 0; i < v.size(); i++) {
      int dist = abs(x - v[i].sensorX) + abs(y - v[i].sensorY);
      if (dist <= v[i].manhattan) return false;
    }
    return true;
  }

  LL solution() {
    vector<SensorBeacon> v;
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;
      int sensorX, sensorY, beaconX, beaconY;
      sscanf(line.c_str(), "Sensor at x=%d, y=%d: closest beacon is at x=%d, y=%d", &sensorX, &sensorY, &beaconX, &beaconY);
      v.push_back(SensorBeacon(sensorX, sensorY, beaconX, beaconY));
    }

    set<int> s;
    // since there is just one spot, it has to lie exactly 1 outside the reach of everything.
    for (int i = 0; i < v.size(); i++) {
      int manhattan = v[i].manhattan;
      for (int x = v[i].sensorX - manhattan - 1; x <= v[i].sensorX + manhattan + 1; x++) {
        if (x < 0 || x > LIMIT) continue;
        int y = v[i].sensorY + (manhattan + 1 - (x - v[i].sensorX));
        if (y >= 0 && y <= LIMIT && isUnseen(x, y, v)) return (LL) FACTOR * x + (LL) y;
        y = v[i].sensorY - (manhattan + 1 - (x - v[i].sensorX));
        if (y >= 0 && y <= LIMIT && isUnseen(x, y, v)) return (LL) FACTOR * x + (LL) y;
      }
    }
    return 0;
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
