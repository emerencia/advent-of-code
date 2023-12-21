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

  PLL pressButton() {
    LL highPulses = 0;
    LL lowPulses = 0;
    queue<PSSB> q;
    // the boolean state is whether this is a low pulse (false) or a high pulse (true)
    q.push({{"button", "broadcaster"}, false});
    while (!q.empty()) {
      PSSB psb = q.front();
      q.pop();
      string fromName = psb.first.first;
      string name = psb.first.second;
      bool isHighPulse = psb.second;
      if (isHighPulse) {
        highPulses++;
      } else {
        lowPulses++;
      }
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
        for (const auto &output: module.outputs) {
          q.push({{name, output}, !sendLowPulse});
        }
      } else {
        // cout << "WARNING: unknown module type " << module.type << endl;
        // exit(1);
      }
    }
    return {highPulses, lowPulses};
  }

  LL pressButtonTimes(int nr) {
    LL highPulses = 0;
    LL lowPulses = 0;
    for (int i = 0; i < nr; i++) {
      const auto &[high, low] = pressButton();
      highPulses += high;
      lowPulses += low;
    }
    return highPulses * lowPulses;
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

    return pressButtonTimes(1000);
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
