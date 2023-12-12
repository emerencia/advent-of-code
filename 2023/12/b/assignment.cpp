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

// position position_in_record
LL mem[160][160];

const int copiesToAdd = 4;

class Assignment {
public:
  string conditions;
  vector<int> record;

  bool allPossibleFailures(int pos, int failureCount) {
    // Can be # or ? but not .
    for (int i = 0; i < failureCount; ++i) {
      if (conditions[pos + i] == '.') return false;
    }
    return true;
  }

  bool endOrPossibleDot(int pos) {
    // Can ? or . but not anything else (== has to be #)
    if (pos == conditions.size()) return true;
    return conditions[pos] != '#';
  }

  LL treatAsFailure(int pos, int recIdx) {
    // we have to start and read a continuous segment of failures
    // return 0 if we have no more failures left in record
    if (recIdx == record.size()) return 0;
    // return 0 if the conditions don't match the current record of failures
    int failureCount = record[recIdx];
    if (pos + failureCount > conditions.size() ||
        !allPossibleFailures(pos, failureCount) ||
        !endOrPossibleDot(pos + failureCount))
      return 0;
    // otherwise advance by however many failures + one for the space after (IF it ends before the last character on the line)
    if (pos + failureCount == conditions.size()) return rec(pos + failureCount, recIdx + 1);
    return rec(pos + failureCount + 1, recIdx + 1);
  }

  LL treatAsDot(int pos, int recIdx) {
    // advance by the entire range of contiguous periods and return
    int nextPos = pos + 1;
    while (nextPos < conditions.size() && conditions[nextPos] == '.') ++nextPos;
    return rec(nextPos, recIdx);
  }

  LL rec(int pos, int recIdx) {
    LL &r = mem[pos][recIdx];
    if (r != -1) return r;
    if (pos == conditions.size()) return r = (recIdx == record.size());
    char cur = conditions[pos];
    if (cur == '#') {
      return r = treatAsFailure(pos, recIdx);
    }
    if (cur == '.') {
      return r = treatAsDot(pos, recIdx);
    }
    if (cur == '?') {
      // return the sum of the two branches (taking it as a dot or as a hash)
      r = 0;
      // treat it as a hash
      r += treatAsFailure(pos, recIdx);
      // treat it as a dot and return
      r += treatAsDot(pos, recIdx);
      return r;
    }
    cout << "ERROR: character unknown: " << cur << endl;
    return -1;
  }

  LL solution() {
    LL result = 0;
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      stringstream ss(line);
      string recordStr;
      ss >> conditions >> recordStr;
      // recordStr is a string of numbers separated by commas. read them into record

      record.clear();
      memset(mem, -1, sizeof(mem));
      stringstream ss2(recordStr);
      string numStr;
      while (ss2.good() && getline(ss2, numStr, ',')) {
        record.push_back(stoi(numStr));
      }

      int oldRecordSize = record.size();
      string oldConditions = conditions;
      for (int i = 0; i < copiesToAdd; ++i) {
        for (int j = 0; j < oldRecordSize; ++j) {
          record.push_back(record[j]);
        }
        conditions += "?" + oldConditions;
      }
      result += rec(0, 0);
    }
    return result;
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
