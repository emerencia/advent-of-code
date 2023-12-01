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

string a[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
vector<string> numbers(a, a + (sizeof a / sizeof a[0]));

class Assignment {
public:

  int isDigit(string line, int offset) {
    if (line[offset] >= '0' && line[offset] <= '9') {
      return line[offset] - '0';
    }
    for (int i=0;i<numbers.size();i++) {
      if (offset + numbers[i].size() <= line.size()) {
        bool good = true;
        for (int j=0;j<numbers[i].size();j++) {
          if (line[offset+j] != numbers[i][j]) {
            good = false;
            break;
          }
        }
        if (good) {
          return i+1;
        }
      }
    }
    return -1;
  }

  int solution() {
    int result = 0;
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      stringstream number;
      for (int i=0;i<line.size();i++) {
        int realDigit = isDigit(line, i);
        if (realDigit > -1) {
          number << realDigit;
          break;
        }
      }
      for (int i = line.size() - 1; i >= 0; i--) {
        int realDigit = isDigit(line, i);
        if (realDigit > -1) {
          number << realDigit;
          break;
        }
      }
      int calLine;
      istringstream(number.str()) >> calLine;
      //cout << calLine << endl;
      result += calLine;
    }
    return result;
  }
};

int main() {
  Assignment obj;
  /*
  for (int i=0;i<numbers.size();i++) {
    cout << numbers[i] << endl;
  }
  */
  cout << obj.solution() << endl;
}
