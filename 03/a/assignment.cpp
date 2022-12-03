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

  int priorityLine(string line) {
    set<char> itemTypes;
    for (int i = 0;i< line.size()/2; i++) {
      itemTypes.insert(line[i]);
    }
    for (int i = line.size()/2; i < line.size(); i++) {
      if (itemTypes.count(line[i])) return itemPriority(line[i]);
    }
    return 0;
  }

  int solution() {
    int result = 0;
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      result += priorityLine(line);
    }
    return result;
  };
};

using namespace std;

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
