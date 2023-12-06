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

struct Rule {
  LL destination_range_start;
  LL source_range_start;
  LL range_length;

  Rule(LL destination_range_start, LL source_range_start, LL range_length) : destination_range_start(
      destination_range_start), source_range_start(source_range_start), range_length(range_length) {
  }

  [[nodiscard]] LL destination_range_end() const {
    return destination_range_start + range_length;
  }

  [[nodiscard]] LL source_range_end() const {
    return source_range_start + range_length;
  }
};

struct Item {
  LL start;
  LL length;

  Item(LL start, LL length) : start(start), length(length) {
  }

  [[nodiscard]] LL end() const {
    return start + length;
  }
};

class Assignment {
public:

  // The optimization here is that instead of individual seeds, we work with ranges of seeds
  static LL solution() {
    bool inMapMode = false;
    vector<Item> currentItems;
    vector<Item> nextItems;
    vector<Rule> conversionMap;
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) {
        if (inMapMode) {
          nextItems.clear();
          // category ends, process currentItems
          for (const auto &curItem: currentItems) {
            // curItem: (start, length)
            queue<Item> rangesToProcess;
            rangesToProcess.push(curItem);
            // find the conversion rule
            while (!rangesToProcess.empty()) {
              Item item = rangesToProcess.front();
              rangesToProcess.pop();
              bool found = false;
              for (const auto &rule: conversionMap) {
                // if item and rule are fully overlapping, push the converted item to nextItems, set found to true and break
                if (item.start >= rule.source_range_start && item.end() <= rule.source_range_end()) {
                  nextItems.emplace_back(item.start - rule.source_range_start + rule.destination_range_start,
                                         item.length);
                  found = true;
                  break;
                }

                // if item and rule do not overlap at all, do nothing
                if (item.end() <= rule.source_range_start || item.start >= rule.source_range_end()) {
                  continue;
                }

                // if item and rule overlap partially, push the converted item to nextItems, set found to true,
                // push the remaining item to rangesToProcess, and break
                if (item.start < rule.source_range_start) {
                  nextItems.emplace_back(rule.destination_range_start, item.end() - rule.source_range_start);
                  rangesToProcess.emplace(item.start, rule.source_range_start - item.start);
                  found = true;
                  break;
                } else { // item.start >= rule.source_range_start
                  nextItems.emplace_back(
                      rule.destination_range_start + rule.range_length - rule.source_range_end() + item.start,
                      rule.source_range_end() - item.start);
                  rangesToProcess.emplace(rule.source_range_end(), item.end() - rule.source_range_end());
                  found = true;
                  break;
                }
              }
              if (!found) {
                // no rule found, add the item to nextItems
                nextItems.push_back(item);
              }
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
          LL item, rangeLength;
          while (ss >> item >> rangeLength) {
            currentItems.emplace_back(item, rangeLength);
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
        conversionMap.emplace_back(destination_range_start, source_range_start, range_length);
      }
    }
    // return the minimum of (the .start property of currentItems)
    LL min = LLONG_MAX;
    for (const auto &item: currentItems) {
      if (item.start < min) {
        min = item.start;
      }
    }
    return min;
  }
};

int main() {
  cout << Assignment::solution() << endl;
}
