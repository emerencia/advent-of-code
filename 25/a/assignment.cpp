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
  vector<string> numbers;
  string solution() {
    numbers.clear();
    int maxlen = 0;
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      numbers.push_back(line);
      maxlen = max(maxlen,(int)line.size());
    }
    string r;
    int nextsum = 0;
    for (int i = 0;i<maxlen;i++) {
      int sum = nextsum;
      for (int j=0;j<numbers.size();j++) {
        int pos = (int)numbers[j].size() - 1 - i;
        if (pos < 0) continue;
        char digit = numbers[j][pos];
        if (digit >= '0' && digit <= '2') {
          sum += digit - '0';
        } else if (digit == '=') {
          sum -= 2;
        } else if (digit  == '-') {
          sum--;
        } else {
          cout << "ERROR: unknown digit: " << digit << endl;
        }
      }
      int nextdiff = 0;
      while (sum < 0) {
        nextdiff--;
        sum += 5;
      }
      nextsum = (sum + 2) / 5;
      nextsum += nextdiff;
      int nextchar = sum%5;
      if (nextchar < 3) {
        r += '0' + nextchar;
      } else if (nextchar == 3) {
        r += '=';
      } else { // nextchar is 4
        r += '-';
      }
    }
    reverse(r.begin(),r.end());
    return r;
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
