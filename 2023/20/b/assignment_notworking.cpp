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
typedef pair<string, bool> PSB;
typedef tuple<string,bool,LL> TSBL;

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
  map<TSBL, LL> mem;

  PLL pressButton() {
    LL highPulses = 0;
    LL lowPulses = 0;
    LL rxHighPulses = 0;
    LL rxLowPulses = 0;
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
      } else if (name == "rx") {
        if (isHighPulse) {
          rxHighPulses++;
        } else {
          rxLowPulses++;
        }
      } else {
        cout << "ERROR: unknown module " << name << endl;
        exit(1);
      }
    }
    return {rxHighPulses, rxLowPulses};
  }

  LL gcd(LL a, LL b) {
    if (a == 0) return b;
    return gcd(b % a, a);
  }

  LL lcm(LL a, LL b) {
    return a * b / gcd(a, b);
  }

  // Fewest button presses needed to get the node with this name to send a pulse of this type.
  LL fewestButtonPressesTo(const string& name, bool isHighPulse, LL minimalPresses) {
    if (mem.find({name, isHighPulse, minimalPresses}) != mem.end()) {
      return mem[{name, isHighPulse, minimalPresses}];
    }
    const auto& module = modules[name];
    LL result;
    if (module.type == 'b') {
      if (isHighPulse) {
        result = -1; // can never happen
      } else {
        result = 1;
      }
    } else if (module.type == '%') {
      if (isHighPulse) {
        // the way to get a flipflop module to send a high pulse is to send it a low pulse
        result = LLONG_MAX;
        for (const auto &input: module.lastInputs) {
          LL subresult = fewestButtonPressesTo(input.first, false, minimalPresses);
          if (subresult == -1) continue;
          result = min(result, subresult);
        }
        if (result == LLONG_MAX) {
          result = -1;
        }
      } else {
        // it must first get a low pulse, then another low pulse.
        result = LLONG_MAX;
        for (const auto &input: module.lastInputs) {
          LL subresult = fewestButtonPressesTo(input.first, false, minimalPresses);
          if (subresult == -1) continue;
          result = min(result, subresult);
        }
        if (result == LLONG_MAX) {
          result = -1;
        } else {
          LL result2 = LLONG_MAX;
          for (const auto &input: module.lastInputs) {
            LL subresult = fewestButtonPressesTo(input.first, false, minimalPresses + 1);
            if (subresult == -1) continue;
            result2 = min(result2, subresult);
          }
          if (result2 == LLONG_MAX) {
            result = -1;
          } else {
            result = result + result2;
          }
        }
      }
    } else if (module.type == '&') {
      if (isHighPulse) {
        // the fewest presses to get any low input to this module.
        result = LLONG_MAX;
        for (const auto &input: module.lastInputs) {
          LL subresult = fewestButtonPressesTo(input.first, false, minimalPresses);
          if (subresult == -1) continue;
          result = min(result, subresult);
        }
        if (result == LLONG_MAX) {
          result = -1;
        }
      } else {
        // it sends a low pulse if it remembers high pulses for all inputs
        result = 1;
        bool found = false;
        for (const auto &input: module.lastInputs) {
          LL subresult = fewestButtonPressesTo(input.first, true, minimalPresses);
          if (subresult == -1) continue;
          found = true;
          result = lcm(result, subresult);
        }
        if (!found) {
          result = -1;
        }
      }
    } else {
      cout << "ERROR: unknown module " << name << endl;
      exit(1);
    }
    mem[{name, isHighPulse, minimalPresses}] = result;
    return result;
  }

  void printNomNom() {
    for (const auto &[name, module]: modules) {
      for (const auto &namee: module.outputs) {
        cout << "[" << name << "]->[" << namee << "]" << endl;
      }
    }
  }

  LL solution() {
    modules.clear();
    mem.clear();
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

    return fewestButtonPressesTo("rg", false, 0);
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
