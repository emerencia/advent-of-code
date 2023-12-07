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
#include <tuple>

using namespace std;
typedef long long LL;
typedef pair<int, int> PII;
typedef tuple<int, int, int, int, int, int> HandStrength;

map<char, int> labelStrength;

struct Hand {
  vector<char> labels;
  int bid;
  HandStrength strength;

  Hand(vector<char> lbls, int bd) : labels(lbls), bid(bd) {
    strength = calculateStrength();
  }

  HandStrength calculateStrength() {
    return make_tuple(handType(),
                      labelStrength[labels[0]],
                      labelStrength[labels[1]],
                      labelStrength[labels[2]],
                      labelStrength[labels[3]],
                      labelStrength[labels[4]]);
  }

  int handType() {
    vector<char> newLabels;
    for (int i = 0; i < labels.size(); i++) {
      newLabels.push_back(labels[i]);
    }

    // replace all J in newLabels with the character that occurs most often in newLabels that isn't J.
    // First, find the most common character in newLabels that isn't J.
    map<char, int> counts;
    for (char label: newLabels) {
      counts[label]++;
    }
    char mostCommon = 'J';
    int mostCommonCount = 0;
    for (auto it = counts.begin(); it != counts.end(); ++it) {
      if (it->first != 'J' && it->second > mostCommonCount) {
        mostCommon = it->first;
        mostCommonCount = it->second;
      }
    }

    // replace all J in newLabels with the mostCommon.
    for (int i = 0; i < newLabels.size(); i++) {
      if (newLabels[i] == 'J') {
        newLabels[i] = mostCommon;
      }
    }

    int uniqueLabels = set<char>(newLabels.begin(), newLabels.end()).size();

    // check for five of a kind
    // if the number of unique items in newLabels is one, then it's a five of a kind.
    if (uniqueLabels == 1) {
      return 7;
    }

    // check for four of a kind
    // if the number of unique items in newLabels is two and one of them has a count of four, then it's a four of a kind.
    if (uniqueLabels == 2) {
      map<char, int> counts;
      for (char label: newLabels) {
        counts[label]++;
      }
      for (auto it = counts.begin(); it != counts.end(); ++it) {
        if (it->second == 4) {
          return 6;
        }
      }
    }

    // check for full house
    // if the number of unique items in newLabels is two and one of them has a count of three, then it's a full house.
    if (uniqueLabels == 2) {
      map<char, int> counts;
      for (char label: newLabels) {
        counts[label]++;
      }
      for (auto it = counts.begin(); it != counts.end(); ++it) {
        if (it->second == 3) {
          return 5;
        }
      }
    }

    // check for three of a kind
    // if the number of unique items in newLabels is three and one of them has a count of three, then it's a three of a kind.
    if (uniqueLabels == 3) {
      map<char, int> counts;
      for (char label: newLabels) {
        counts[label]++;
      }
      for (auto it = counts.begin(); it != counts.end(); ++it) {
        if (it->second == 3) {
          return 4;
        }
      }
    }

    // check for two pair
    // if the number of unique items in newLabels is three and two of them have a count of two, then it's a two pair.
    if (uniqueLabels == 3) {
      map<char, int> counts;
      for (char label: newLabels) {
        counts[label]++;
      }
      int numPairs = 0;
      for (auto it = counts.begin(); it != counts.end(); ++it) {
        if (it->second == 2) {
          numPairs++;
        }
      }
      if (numPairs == 2) {
        return 3;
      }
    }

    // check for one pair
    // if the number of unique items in newLabels is four and one of them has a count of two, then it's a one pair.
    if (uniqueLabels == 4) {
      return 2;
    }

    // else we have a high card
    return 1;
  }

  // Write a comparison operator so we can sort vectors of this struct
  bool operator<(const Hand &other) const {
    return strength < other.strength;
  }
};

class Assignment {
public:

  int solution() {
    labelStrength['A'] = 14;
    labelStrength['K'] = 13;
    labelStrength['Q'] = 12;
    labelStrength['J'] = 1;
    labelStrength['T'] = 10;
    labelStrength['9'] = 9;
    labelStrength['8'] = 8;
    labelStrength['7'] = 7;
    labelStrength['6'] = 6;
    labelStrength['5'] = 5;
    labelStrength['4'] = 4;
    labelStrength['3'] = 3;
    labelStrength['2'] = 2;

    LL result = 0;
    vector <Hand> hands;
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      stringstream ss(line);
      string hand;
      int bid;
      ss >> hand >> bid;
      vector<char> labels;
      for (char c: hand) {
        labels.push_back(c);
      }
      hands.push_back(Hand(labels, bid));
    }

    // sort hands in descending order
    sort(hands.rbegin(), hands.rend());
    for (LL i = 0; i < hands.size(); i++) {
      result += (hands.size() - i) * hands[i].bid;
    }
    return result;
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
