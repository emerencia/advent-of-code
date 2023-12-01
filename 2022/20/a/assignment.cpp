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

class Assignment {
public:

  int solution() {
    vector<PII> numbers;
    int result = 0;
    int idx = 0;
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;
      stringstream s(line);
      int number;
      s >> number;
      numbers.push_back({number, idx});
      idx++;
    }
    /*
    for (int i = 0; i < numbers.size(); i++) {
      cout << numbers[i].first << " ";
    }
    cout << endl;
    */
    for (int i = 0; i < numbers.size(); i++) {
      for (int j = 0; j < numbers.size(); j++) {
        PII value = numbers[j];
        if (value.second == i) {
          if (value.first == 0) break;
          numbers.erase(numbers.begin() + j);
          int newpos = (((j + value.first + 4 * numbers.size()) % numbers.size()));
          if (newpos == 0) {
            // cout << "moving: " << value.first << ", inserting at the end" << endl;
            numbers.push_back(value);
          } else {
            // cout << "moving: " << value.first << ", inserting at: " << newpos << endl;
            numbers.insert(numbers.begin() + newpos, value);
          }
          /*
          for (int k = 0; k < numbers.size(); k++) {
            cout << numbers[k].first << " ";
          }
          cout << endl;
          */
          break;
        }
      }
    }
    for (int i = 0; i < numbers.size(); i++) {
      PII value = numbers[i];
      if (value.first != 0) continue;
      for (int j = 0; j < 3; j++) {
        int pos = (i + (j + 1) * 1000) % numbers.size();
        cout << "number " << ((j + 1) * 1000) << " is " << numbers[pos].first << endl;
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
