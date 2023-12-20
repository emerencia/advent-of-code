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

const map<char, int> propMap = {{'x', 0},
                                {'m', 1},
                                {'a', 2},
                                {'s', 3}};

struct Part {
  vector<int> props;
};

struct Rule {
  bool hasGuard{};
  int guardVar{};
  bool guardOperatorIsLessThan{};
  int guardValue{};
  string destination;

  [[nodiscard]] bool conditionHolds(const Part &part) const {
    if (!hasGuard) {
      return true;
    }
    if (guardOperatorIsLessThan) {
      return part.props[guardVar] < guardValue;
    }
    return part.props[guardVar] > guardValue;
  }
};

struct Workflow {
  vector<Rule> rules;
};

class Assignment {
public:
  map<string, Workflow> workflows;
  vector<Part> parts;

  static int partValue(const Part &part) {
    int result = 0;
    for (int i = 0; i < 4; ++i) {
      result += part.props[i];
    }
    return result;
  }

  bool partIsAccepted(const Part &part) {
    string location = "in";
    while (location != "R" && location != "A") {
      const auto &workflow = workflows.at(location);
      bool found = false;
      for (const auto &rule: workflow.rules) {
        if (rule.conditionHolds(part)) {
          location = rule.destination;
          found = true;
          break;
        }
      }
      if (!found) {
        cout << "No rule found for " << location << endl;
        exit(1);
      }
    }
    return location == "A";
  }

  int sumOfAcceptedParts() {
    int result = 0;
    for (const auto &part: parts) {
      if (partIsAccepted(part)) {
        result += partValue(part);
      }
    }
    return result;
  }

  int solution() {
    workflows.clear();
    parts.clear();
    bool readingRules = true;
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) {
        readingRules = false;
        continue;
      }
      if (readingRules) {
        // read the name until the {
        string name = line.substr(0, line.find('{'));
        string rules = line.substr(line.find('{') + 1, line.size() - line.find('{') - 2);
        stringstream ss(rules);
        // read by comma separated
        string rule;
        while (getline(ss, rule, ',')) {
          Rule r;
          if (rule.find(':') == string::npos) {
            r.hasGuard = false;
            r.destination = rule;
          } else {
            r.hasGuard = true;
            string guard = rule.substr(0, rule.find(':'));
            r.guardVar = propMap.at(guard[0]);
            r.guardOperatorIsLessThan = guard[1] == '<';
            r.guardValue = stoi(guard.substr(2, guard.size() - 2));
            r.destination = rule.substr(rule.find(':') + 1, rule.size() - rule.find(':') - 1);
          }
          workflows[name].rules.push_back(r);
        }
      } else {
        // reading parts
        int x, m, a, s;
        sscanf(line.c_str(), "{x=%d,m=%d,a=%d,s=%d}", &x, &m, &a, &s);
        parts.push_back({{x, m, a, s}});
      }
    }
    return sumOfAcceptedParts();
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
