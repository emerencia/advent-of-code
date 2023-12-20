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

struct PartRange {
  vector<int> min;
  vector<int> max;

  [[nodiscard]] LL nrCombinations() const {
    LL result = 1;
    for (int i = 0; i < 4; ++i) {
      result *= max[i] - min[i] + 1;
    }
    return result;
  }
};

typedef pair<PartRange, string> PRS;

struct Rule {
  bool hasGuard{};
  int guardVar{};
  bool guardOperatorIsLessThan{};
  int guardValue{};
  string destination;
};

struct Workflow {
  vector<Rule> rules;
};

class Assignment {
public:
  map<string, Workflow> workflows;
  vector<Part> parts;

  LL distinctCombinationsAccepted() {
    LL accepted = 0;
    LL rejected = 0;
    queue<PRS> q;
    PartRange prStart;
    for (int i = 0; i < 4; ++i) {
      prStart.min.push_back(1);
      prStart.max.push_back(4000);
    }
    q.emplace(prStart, "in");
    while (!q.empty()) {
      PRS prs = q.front();
      q.pop();
      PartRange pr = prs.first;
      string location = prs.second;

      if (location == "A") {
        accepted += pr.nrCombinations();
      } else if (location == "R") {
        rejected += pr.nrCombinations();
      } else {
        const auto &workflow = workflows.at(location);
        PartRange newPr = pr;
        for (const auto &rule: workflow.rules) {
          if (!rule.hasGuard) {
            q.emplace(newPr, rule.destination);
            continue;
          }
          int cmin = newPr.min[rule.guardVar];
          int cmax = newPr.max[rule.guardVar];
          if (rule.guardOperatorIsLessThan) {
            if (rule.guardValue <= cmin) continue;

            PartRange nextPr = newPr;
            nextPr.max[rule.guardVar] = min(cmax, rule.guardValue - 1);
            q.emplace(nextPr, rule.destination);
            newPr.min[rule.guardVar] = rule.guardValue;
          } else {
            if (rule.guardValue >= cmax) continue;

            PartRange nextPr = newPr;
            nextPr.min[rule.guardVar] = max(cmin, rule.guardValue + 1);
            q.emplace(nextPr, rule.destination);
            newPr.max[rule.guardVar] = rule.guardValue;
          }
          if (newPr.min[rule.guardVar] > newPr.max[rule.guardVar]) {
            // It never gets here, but I think in theory it can.
            // It's just that the input rules are well-behaved.
            break;
          }
        }
      }
    }
    // sanity check
    LL totalCombinations = 4000LL * 4000 * 4000 * 4000;
    if (accepted + rejected != totalCombinations) {
      cout << "ERROR: Accepted + rejected != totalCombinations" << endl;
      cout << "Accepted: " << accepted << endl;
      cout << "Rejected: " << rejected << endl;
      cout << "Total combinations: " << totalCombinations << endl;
      cout << "Difference: " << totalCombinations - accepted - rejected << endl << endl;
      exit(1);
    }
    return accepted;
  }

  LL solution() {
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
        // reading parts but they're not used anymore
        int x, m, a, s;
        sscanf(line.c_str(), "{x=%d,m=%d,a=%d,s=%d}", &x, &m, &a, &s);
        parts.push_back({{x, m, a, s}});
      }
    }
    return distinctCombinationsAccepted();
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
