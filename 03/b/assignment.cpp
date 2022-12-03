#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>
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

using namespace std;
typedef long long LL;
typedef pair<int, int> PII;


class Assignment {
public:

  int itemPriority(char itemType) {
    if (itemType >= 'a' && itemType <= 'z') return (itemType - 'a' + 1);
    // otherwise uppercase
    return itemType - 'A' + 27;
  }

  void addToMap(map<char, int>& mmap, char chr, int bag) {
    if (mmap.count(chr)) {
      mmap[chr] = mmap[chr] | (1 << bag);
    } else {
      mmap[chr] = (1 << bag);
    }
  }

  int priorityLines(string line1, string line2, string line3) {
    map<char, int> mmap;
    for (int i = 0;i < line1.size(); i++) {
      addToMap(mmap, line1[i], 0);
    }
    for (int i = 0; i < line2.size(); i++) {
      addToMap(mmap, line2[i], 1);
    }
    int mask = 3;
    for (int i =0; i < line3.size(); i++) {
      if (mmap.count(line3[i]) && mmap[line3[i]] == mask) return itemPriority(line3[i]);
    }
    return 0;
  }

  int solution() {
    int result = 0;
    while (cin.good()) {
      string line1, line2, line3;
      getline(cin, line1);
      if (line1.empty()) continue;
      getline(cin, line2);
      if (line2.empty()) continue;
      getline(cin, line3);
      if (line3.empty()) continue;

      result += priorityLines(line1, line2, line3);
    }
    return result;
  };
};

using namespace std;

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
