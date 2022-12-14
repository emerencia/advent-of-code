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

const LL DECRYPTION_KEY = 811589153;

class Assignment {
public:

  LL solution() {
    vector<PII> numbers;
    LL result = 0;
    int idx = 0;
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;
      stringstream s(line);
      LL number;
      s >> number;
      numbers.push_back({number * DECRYPTION_KEY, idx});
      idx++;
    }
    // Since the input size is only 5000, a quadratic algorithm is good enough.
    for (int k = 0; k < 10; k++) {
      for (int i = 0; i < numbers.size(); i++) {
        for (int j = 0; j < numbers.size(); j++) {
          PII value = numbers[j];
          if (value.second == i) {
            if (value.first == 0) break;
            numbers.erase(numbers.begin() + j);
            LL newpos = (((j + value.first + 4 * DECRYPTION_KEY * numbers.size()) % numbers.size()));
            if (newpos == 0) {
              numbers.push_back(value);
            } else {
              numbers.insert(numbers.begin() + newpos, value);
            }
            break;
          }
        }
      }
    }
    for (int i = 0; i < numbers.size(); i++) {
      PII value = numbers[i];
      if (value.first != 0) continue;
      for (int j = 0; j < 3; j++) {
        int pos = (i + (j + 1) * 1000) % numbers.size();
        result += numbers[pos].first;
      }
      break;
    }
    return result;
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
