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
#include <tuple>

using namespace std;
typedef long long LL;
typedef pair<int, int> PII;

// timeLeft oreRobots clayRobots obsidianRobots geodeRobots oreCount clayCount obsidianCount geodeCount
typedef tuple<int, int, int, int, int, int, int, int, int> State;

struct Blueprint {
  int oreRobotOreCost;
  int clayRobotOreCost;
  int obsidianRobotOreCost;
  int obsidianRobotClayCost;
  int geodeRobotOreCost;
  int geodeRobotObsidianCost;
  int maxOreCost;

  Blueprint(int oreRobotOreCost,
            int clayRobotOreCost,
            int obsidianRobotOreCost,
            int obsidianRobotClayCost,
            int geodeRobotOreCost,
            int geodeRobotObsidianCost) :
      oreRobotOreCost(oreRobotOreCost),
      clayRobotOreCost(clayRobotOreCost),
      obsidianRobotOreCost(obsidianRobotOreCost),
      obsidianRobotClayCost(obsidianRobotClayCost),
      geodeRobotOreCost(geodeRobotOreCost),
      geodeRobotObsidianCost(geodeRobotObsidianCost) {
    maxOreCost = max(max(max(oreRobotOreCost, clayRobotOreCost), obsidianRobotOreCost), geodeRobotOreCost);
  }
};

vector<Blueprint> blueprints;

class Assignment {
public:
  int geodesMined(const Blueprint &blueprint) {
    // try greedy approach
    int r = 0;
    queue<State> q;
    set<State> seen;
    // timeLeft oreRobots clayRobots obsidianRobots geodeRobots oreCount clayCount obsidianCount geodeCount
    q.push(make_tuple(24, 1, 0, 0, 0, 0, 0, 0, 0));
    while (!q.empty()) {
      State p = q.front();
      q.pop();
      int timeLeft = get<0>(p);
      if (timeLeft == 0) continue;

      int oreRobots = get<1>(p);
      int clayRobots = get<2>(p);
      int obsidianRobots = get<3>(p);
      int geodeRobots = get<4>(p);
      int oreCount = get<5>(p);
      int clayCount = get<6>(p);
      int obsidianCount = get<7>(p);
      int geodeCount = get<8>(p);

      // clamp the state!
      // Reduce robots (if we can create more in a turn than we need in any turn, we are good)
      if (oreRobots > blueprint.maxOreCost) oreRobots = blueprint.maxOreCost;
      if (clayRobots > blueprint.obsidianRobotClayCost) clayRobots = blueprint.obsidianRobotClayCost;
      if (obsidianRobots > blueprint.geodeRobotObsidianCost) obsidianRobots = blueprint.geodeRobotObsidianCost;

      p = make_tuple(timeLeft, oreRobots, clayRobots, obsidianRobots, geodeRobots, oreCount, clayCount, obsidianCount, geodeCount);
      if (seen.find(p) != seen.end()) continue;
      seen.insert(p);

      int oldOreCount = oreCount;
      int oldClayCount = clayCount;
      int oldObsidianCount = obsidianCount;

      // Increase the counts
      oreCount += oreRobots;
      clayCount += clayRobots;
      obsidianCount += obsidianRobots;
      geodeCount += geodeRobots;

      // Possibly update the max
      r = max(r,geodeCount);

      // reduce the time
      timeLeft--;

      // Don't buy anything this turn
      q.push(make_tuple(timeLeft, oreRobots, clayRobots, obsidianRobots, geodeRobots, oreCount, clayCount, obsidianCount, geodeCount));
      // Try to buy any robot if you can
      if (oldOreCount >= blueprint.oreRobotOreCost) {
        q.push(make_tuple(timeLeft, oreRobots + 1, clayRobots, obsidianRobots, geodeRobots, oreCount - blueprint.oreRobotOreCost, clayCount, obsidianCount, geodeCount));
      }
      if (oldOreCount >= blueprint.clayRobotOreCost) {
        q.push(make_tuple(timeLeft, oreRobots, clayRobots + 1, obsidianRobots, geodeRobots, oreCount - blueprint.clayRobotOreCost, clayCount, obsidianCount, geodeCount));
      }
      if (oldOreCount >= blueprint.obsidianRobotOreCost && oldClayCount >= blueprint.obsidianRobotClayCost) {
        q.push(make_tuple(timeLeft, oreRobots, clayRobots, obsidianRobots + 1, geodeRobots, oreCount - blueprint.obsidianRobotOreCost, clayCount - blueprint.obsidianRobotClayCost, obsidianCount, geodeCount));
      }
      if (oldOreCount >= blueprint.geodeRobotOreCost && oldObsidianCount >= blueprint.geodeRobotObsidianCost) {
        q.push(make_tuple(timeLeft, oreRobots, clayRobots, obsidianRobots, geodeRobots + 1, oreCount - blueprint.geodeRobotOreCost, clayCount, obsidianCount - blueprint.geodeRobotObsidianCost, geodeCount));
      }
    }
    seen.clear();
    cout << "result for blueprint is: " << r << endl;
    return r;
  }

  int solution() {
    int result = 0;
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      int blueprint;
      int oreRobotOreCost;
      int clayRobotOreCost;
      int obsidianRobotOreCost;
      int obsidianRobotClayCost;
      int geodeRobotOreCost;
      int geodeRobotObsidianCost;
      sscanf(line.c_str(),
             "Blueprint %i: Each ore robot costs %i ore. Each clay robot costs %i ore. Each obsidian robot costs %i ore and %i clay. Each geode robot costs %i ore and %i obsidian.",
             &blueprint, &oreRobotOreCost, &clayRobotOreCost, &obsidianRobotOreCost, &obsidianRobotClayCost,
             &geodeRobotOreCost, &geodeRobotObsidianCost);
      blueprints.push_back(
          Blueprint(oreRobotOreCost, clayRobotOreCost, obsidianRobotOreCost, obsidianRobotClayCost, geodeRobotOreCost,
                    geodeRobotObsidianCost));
    }
    /*
    for (int i=0;i<blueprints.size();i++) {
      cout << "Blueprint " << i+1 << ":" << endl;
      cout << "  oreRobotOreCost: " << blueprints[i].oreRobotOreCost << endl;
      cout << "  clayRobotOreCost: " << blueprints[i].clayRobotOreCost << endl;
      cout << "  obsidianRobotOreCost: " << blueprints[i].obsidianRobotOreCost << endl;
      cout << "  obsidianRobotClayCost: " << blueprints[i].obsidianRobotClayCost << endl;
      cout << "  geodeRobotOreCost: " << blueprints[i].geodeRobotOreCost << endl;
      cout << "  geodeRobotObsidianCost: " << blueprints[i].geodeRobotObsidianCost << endl;
      cout << endl;
    }
    */
    for (int i = 0; i < blueprints.size(); i++) {
      result += (i + 1) * geodesMined(blueprints[i]);
    }
    return result;
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
