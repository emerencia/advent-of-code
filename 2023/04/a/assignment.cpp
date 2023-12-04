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

  static set<int> readNumbers(const string &line) {
    set<int> result;
    stringstream ss(line);
    int number;
    while (ss >> number) {
      result.insert(number);
    }
    return result;
  }

  static int points(const string &card) {
    int result = 0;
    set<int> winningNumbers = readNumbers(card.substr(0, card.find('|')));
    set<int> ownCards = readNumbers(card.substr(card.find('|') + 1));
    for (const auto &number: winningNumbers) {
      if (ownCards.count(number)) {
        if (result == 0) {
          result = 1;
        } else {
          result *= 2;
        }
      }
    }
    return result;
  }

  static int solution() {
    int result = 0;
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      string card = line.substr(line.find(':') + 1);
      result += points(card);
    }
    return result;
  }
};

int main() {
  cout << Assignment::solution() << endl;
}
