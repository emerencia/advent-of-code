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
typedef pair<LL, LL> PII;
// ((destination_range_start, source_range_start), range_length)
typedef pair<PII, LL> PIII;

class Assignment {
public:

  static LL solution() {
    bool inMapMode = false;
    vector<LL> currentItems;
    vector<LL> nextItems;
    set<PIII> conversionMap;
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) {
        if (inMapMode) {
          nextItems.clear();
          // category ends, process currentItems
          for (const auto &item: currentItems) {
            // find the conversion rule
            bool found = false;
            for (const auto &rule: conversionMap) {
              if (item >= rule.first.second && item < rule.first.second + rule.second) {
                // found the rule
                nextItems.push_back(rule.first.first + item - rule.first.second);
                found = true;
                break;
              }
            }
            if (!found) {
              // no rule found, add the unchanged item to nextItems
              nextItems.push_back(item);
            }
          }
          // swap currentItems and nextItems
          currentItems.swap(nextItems);
          inMapMode = false;
        }
        continue;
      }
      if (!inMapMode) {
        // read the first word
        // if it is seeds, we fill the array
        // otherwise we start map mode
        stringstream ss(line);
        string firstWord;
        ss >> firstWord;
        if (firstWord == "seeds:") {
          if (!currentItems.empty() || !nextItems.empty()) {
            // we have a problem
            cout << "ERROR: seeds: should be the first line" << endl;
            return -1;
          }
          LL item;
          while (ss >> item) {
            currentItems.push_back(item);
          }
        } else {
          // start map mode
          inMapMode = true;
          conversionMap.clear();
        }
      } else {
        // add the current numbers to the map
        stringstream ss(line);
        LL destination_range_start, source_range_start, range_length;
        ss >> destination_range_start >> source_range_start >> range_length;
        conversionMap.insert(make_pair(make_pair(destination_range_start, source_range_start), range_length));
      }
    }
    // return the minimum of currentItems
    return *min_element(currentItems.begin(), currentItems.end());
  }
};

int main() {
  cout << Assignment::solution() << endl;
}
