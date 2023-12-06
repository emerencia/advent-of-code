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

struct Race {
  int time;
  int distance;

  Race(int t, int d) : time(t), distance(d) {}
};

class Assignment {
public:

  static LL numberOfWaysToBeatRecord(const Race &race) {
    double upperLimit = (race.time + sqrt(race.time * race.time - 4 * race.distance)) / 2.0;
    double lowerLimit = (race.time - sqrt(race.time * race.time - 4 * race.distance)) / 2.0;
    LL upper = (LL) floor(upperLimit - 1e-9);
    LL lower = (LL) ceil(lowerLimit + 1e-9);
    return upper - lower + 1;
  }

  static LL solution() {
    string timeline;
    getline(cin, timeline);
    if (timeline.empty()) {
      cout << "Error: timeline empty" << endl;
      exit(1);
    }
    string distanceline;
    getline(cin, distanceline);
    if (distanceline.empty()) {
      cout << "Error: distanceline empty" << endl;
      exit(1);
    }

    vector<int> times;
    vector<int> distances;
    stringstream ss(timeline);
    string timeword;
    ss >> timeword;
    int time;
    while (ss >> time) {
      times.push_back(time);
    }
    stringstream ss2(distanceline);
    string distanceword;
    ss2 >> distanceword;
    int distance;
    while (ss2 >> distance) {
      distances.push_back(distance);
    }

    if (times.size() != distances.size()) {
      cout << "Error: times.size() != distances.size()" << endl;
      exit(1);
    }
    vector<Race> races;
    races.reserve(times.size());
    for (int i = 0; i < times.size(); i++) {
      races.emplace_back(times[i], distances[i]);
    }

    LL result = 1;
    for (const auto &race: races) {
      result *= numberOfWaysToBeatRecord(race);
    }
    return result;
  }
};

int main() {
  cout << Assignment::solution() << endl;
}
