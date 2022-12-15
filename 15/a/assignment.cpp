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
  int sensorX, sensorY, beaconX, beaconY;
  SensorBeacon(int sensorX, int sensorY, int beaconX, int beaconY) : sensorX(sensorX), sensorY(sensorY),beaconX(beaconX),beaconY(beaconY) {
  }
};

const int Y = 2000000;

class Assignment {
public:

  int solution() {
    vector<SensorBeacon> v;
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;
      int sensorX,sensorY,beaconX,beaconY;
      sscanf(line.c_str(),"Sensor at x=%d, y=%d: closest beacon is at x=%d, y=%d",&sensorX,&sensorY,&beaconX,&beaconY);
      v.push_back(SensorBeacon(sensorX,sensorY,beaconX,beaconY));
    }

    set<int> s;
    // find all spaces occupado
    for (int i = 0;i<v.size();i++) {
      int manhattan = abs(v[i].beaconX - v[i].sensorX) + abs(v[i].beaconY - v[i].sensorY);
      if (abs(v[i].sensorY - Y) <= manhattan) {
        int diff = manhattan - abs(v[i].sensorY - Y);
        for (int x = v[i].sensorX - diff;x<= v[i].sensorX + diff;x++) {
          s.insert(x);
        }
      }
    }

    // subtract from it the number of beacons on this row
    for (int i = 0; i < v.size(); i++) {
      if (v[i].beaconY == Y)
        s.erase(v[i].beaconX);
    }

    return s.size();
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
