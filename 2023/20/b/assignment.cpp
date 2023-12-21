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
typedef pair<LL, LL> PLL;
typedef pair<pair<string, string>, bool> PSSB;

struct Module {
  map<string, bool> lastInputs;
  vector<string> outputs;
  char type{};
  bool isOn{};

  bool allLastInputsHigh() {
    for (const auto &input: lastInputs) {
      if (!input.second) {
        return false;
      }
    }
    return true;
  }
};

class Assignment {
public:
  map<string, Module> modules;

  LL gcd(LL a, LL b) {
    if (a == 0) return b;
    return gcd(b % a, a);
  }

  LL lcm(LL a, LL b) {
    return a * b / gcd(a, b);
  }

  LL fewestPressesToRx() {
    // The whole thing is too slow, so instead of calculating when the last node gets
    // all high pulses, calculate when its inputs send a high input individually, and take the lcm of those.
    set<string> gateKeepers;
    for (const auto &input: modules["rg"].lastInputs) {
      gateKeepers.insert(input.first);
    }
    queue<PSSB> q;
    map<string, LL> seen;
    LL presses = 0;
    while (seen.size() < gateKeepers.size()) {
      // the boolean state is whether this is a low pulse (false) or a high pulse (true)
      q.push({{"button", "broadcaster"}, false});
      presses++;

      while (!q.empty()) {
        PSSB psb = q.front();
        q.pop();
        string fromName = psb.first.first;
        string name = psb.first.second;
        bool isHighPulse = psb.second;
        Module &module = modules[name];
        module.lastInputs[fromName] = isHighPulse;
        // handle the different types of modules
        if (module.type == 'b') {
          // send the same type of pulse to all outputs
          for (const auto &output: module.outputs) {
            q.push({{name, output}, isHighPulse});
          }
        } else if (module.type == '%') {
          if (isHighPulse) {
            // ignore high pulses for this module type.
            continue;
          }
          if (module.isOn) {
            module.isOn = false;
            for (const auto &output: module.outputs) {
              q.push({{name, output}, false});
            }
          } else {
            module.isOn = true;
            for (const auto &output: module.outputs) {
              q.push({{name, output}, true});
            }
          }
        } else if (module.type == '&') {
          bool sendLowPulse = isHighPulse && module.allLastInputsHigh();
          if (!sendLowPulse && gateKeepers.find(name) != gateKeepers.end() && seen.find(name) == seen.end()) {
            seen[name] = presses;
          }
          for (const auto &output: module.outputs) {
            q.push({{name, output}, !sendLowPulse});
          }
        } else {
          // cout << "WARNING: unknown module type " << module.type << endl;
          // exit(1);
        }
      }
    }
    LL result = 1;
    for (const auto &press: seen) {
      result = lcm(result, press.second);
    }
    return result;
  }

  LL solution() {
    modules.clear();
    map<string, vector<string>> inputs;
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      stringstream ss(line);
      string name;
      char type;
      ss >> name;
      if (name == "broadcaster") {
        type = 'b';
      } else {
        type = name[0];
        name = name.substr(1);
      }
      string arrow;
      ss >> arrow;
      if (ss.peek() == ' ') ss.ignore();
      vector<string> outputs;
      string outputName;
      while (getline(ss, outputName, ',')) {
        outputs.push_back(outputName);
        inputs[outputName].push_back(name);
        if (ss.peek() == ' ') ss.ignore();
      }
      modules[name] = {map<string, bool>(), outputs, type, false};
    }
    // use inputs to set the lastInputs for each module
    for (const auto &input: inputs) {
      modules[input.first].lastInputs = map<string, bool>();
      for (const auto &name: input.second) {
        modules[input.first].lastInputs[name] = false;
      }
    }

    return fewestPressesToRx();
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
