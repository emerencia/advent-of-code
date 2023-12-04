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

int mem[1000];

class Assignment {
public:

  static set<int> readNumbers(const string &line) {
    set<int> result;
    stringstream ss(line);
    int number;
    while (ss >> number) {
      result.insert(number);
    }
    return result;
  }

  static int numberOfMatches(const string &card) {
    int result = 0;
    set<int> winningNumbers = readNumbers(card.substr(0, card.find('|')));
    set<int> ownCards = readNumbers(card.substr(card.find('|') + 1));
    for (const auto &number: winningNumbers) {
      if (ownCards.count(number)) {
        result++;
      }
    }
    return result;
  }

  static int solution() {
    fill(&mem[0], &mem[1000], 0);
    int idx = 0;
    int result = 0;
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      mem[idx] += 1;
      string card = line.substr(line.find(':') + 1);
      int nrOfMatches = numberOfMatches(card);
      for (int i = 0; i < nrOfMatches; i++) {
        mem[idx + i + 1] += mem[idx];
      }
      result += mem[idx];
      idx++;
    }
    return result;
  }
};

int main() {
  cout << Assignment::solution() << endl;
}
