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

  static int digitsInNumber(LL number) {
    int digits = 0;
    while (number > 0) {
      digits++;
      number /= 10;
    }
    return digits;
  }

  static LL doubleANumber(LL number) {
    LL result = 0;
    int digits = digitsInNumber(number);
    for (int i = 0; i < digits; i++) {
      result *= 10;
      result += (number / (LL)pow(10, digits - 1 - i)) % 10;
    }
    for (int i = 0; i < digits; i++) {
      result *= 10;
      result += (number / (LL)pow(10, digits - 1 - i)) % 10;
    }
    return result;
  }

  static LL commonStartingPrefixOfNumbers(LL first, LL second) {
    LL result = 0;
    int firstDigits = digitsInNumber(first);
    int secondDigits = digitsInNumber(second);
    int minDigits = min(firstDigits, secondDigits);
    for (int i = 0; i < minDigits; i++) {
      LL firstDigit = (first / (LL)pow(10, firstDigits - 1 - i)) % 10;
      LL secondDigit = (second / (LL)pow(10, secondDigits - 1 - i)) % 10;
      if (firstDigit == secondDigit) {
        result *= 10;
        result += firstDigit;
      } else {
        break;
      }
    }
    return result;
  }

  // contatenate two numbers
  static LL concatenateNumbers(LL first, LL second) {
    LL result = first;
    int digits = digitsInNumber(second);
    for (int i = 0; i < digits; i++) {
      result *= 10;
      result += (second / (LL)pow(10, digits - 1 - i)) % 10;
    }
    return result;
  }

  static LL firstHalfOfNumber(LL number) {
    LL result = 0;
    int digits = digitsInNumber(number);
    for (int i = 0; i < digits/2; i++) {
      result *= 10;
      result += (number / (LL)pow(10, digits - 1 - i)) % 10;
    }
    return result;
  }

  static LL firstXPositionsOfNumber(LL number, int positions) {
    LL result = 0;
    int digits = digitsInNumber(number);
    for (int i = 0; i < min(positions, digits); i++) {
      result *= 10;
      result += (number / (LL)pow(10, digits - 1 - i)) % 10;
    }
    return result;
  }

  static bool numberStartsWithNumber(LL number, LL prefix) {
    if (number == 0 || prefix >= number) return true;
    int prefixDigits = digitsInNumber(prefix);
    LL numberPrefix = firstXPositionsOfNumber(number, prefixDigits);
    return numberPrefix == prefix;
  }

  static LL invalidIdsInRange(const string &range) {
    // parse the range
    const size_t dashPos = range.find('-');
    LL start = 0, end = 0;
    if (dashPos == string::npos) {
      cout << "Error: this should not happen, single range: " << range << endl;
      exit(1);
    }
    start = stoll(range.substr(0, dashPos));
    end = stoll(range.substr(dashPos + 1));
    const LL prefix = commonStartingPrefixOfNumbers(start, end);
    cout << "\n\nProcessing range: " << start << " - " << end << endl;
    set<LL> numbers;
    const LL bConst = start;
    for (LL i = 1; i <= bConst; i++) {
      if (i % 100000000 == 0) {
        cout << "  Checked up to: " << i << endl << flush;
      }
      LL cur = doubleANumber(i);
      if (!numberStartsWithNumber(prefix, cur)) {
        continue;
      }
      while (cur < start) {
        cur = concatenateNumbers(cur, i);
        if (!numberStartsWithNumber(prefix, cur)) {
          break;
        }
      }
      if (!numberStartsWithNumber(prefix, cur)) {
        continue;
      }
      while (cur <= end) {
        numbers.insert(cur);
        cur = concatenateNumbers(cur, i);
      }
    }
    LL sum = 0;
    for (const LL number : numbers) {
      cout << "  Invalid ID: " << number << endl;
      sum += number;
    }
    cout << "Found " << numbers.size() << " invalid IDs in range " << range << ", sum: " << sum << endl;
    return sum;
  }

  static LL invalidIds(const string &line) {
    // tokennize the line into ranges by comma's.
    LL result = 0;
    stringstream ss(line);
    string token;
    while (getline(ss, token, ',')) {
      result += invalidIdsInRange(token);
    }
    return result;
  }

  static LL solution() {
    LL result = 0;
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      result += invalidIds(line);
    }
    return result;
  }
};

int main() {
  cout << Assignment::solution() << endl;
}
