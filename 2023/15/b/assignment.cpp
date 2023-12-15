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
typedef pair<string, int> PSI;

const int NR_BOXES = 256;

class Assignment {
public:
  vector<vector<PSI>> boxes;

  static int hashValue(const string &s) {
    int currentValue = 0;
    for (char i: s) {
      currentValue += i;
      currentValue *= 17;
      currentValue %= NR_BOXES;
    }
    return currentValue;
  }

  int indexInBox(int box, const string &lensLabel) {
    for (int i = 0; i < boxes[box].size(); ++i) {
      if (boxes[box][i].first == lensLabel) {
        return i;
      }
    }
    return -1;
  }

  void removeFromBox(int box, int idx) {
    boxes[box].erase(boxes[box].begin() + idx);
  }

  int focusingPower() {
    int r = 0;
    for (int i = 0; i < boxes.size(); i++) {
      for (int j = 0; j < boxes[i].size(); j++) {
        r += (i + 1) * (j + 1) * boxes[i][j].second;
      }
    }
    return r;
  }

  int solution() {
    // set boxes to have size 256
    boxes.resize(NR_BOXES);
    if (!cin.good()) {
      cout << "cin not good" << endl;
      exit(1);
    }
    string line;
    getline(cin, line);
    if (line.empty()) {
      cout << "line empty" << endl;
      exit(1);
    }
    // split line by commas
    stringstream ss(line);
    string token;
    while (getline(ss, token, ',')) {
      // if token contains an equal sign, split by equal sign
      size_t pos = token.find('=');
      if (pos != string::npos) {
        string lensLabel = token.substr(0, pos);
        int focalLength = stoi(token.substr(pos + 1));
        int box = hashValue(lensLabel);
        int idx = indexInBox(box, lensLabel);
        if (idx != -1) {
          boxes[box][idx].second = focalLength;
        } else {
          boxes[box].emplace_back(lensLabel, focalLength);
        }
      } else {
        size_t pos2 = token.find('-');
        if (pos2 != string::npos) {
          string lensLabel = token.substr(0, pos2);
          int box = hashValue(lensLabel);
          int idx = indexInBox(box, lensLabel);
          if (idx != -1) {
            removeFromBox(box, idx);
          }
        } else {
          cout << "ERROR: unknown token: " << token << endl;
          exit(1);
        }
      }
    }
    return focusingPower();
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
