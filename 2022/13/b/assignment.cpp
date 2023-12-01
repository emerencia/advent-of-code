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

struct Packet {
  string myStr;

  Packet(string myStr) : myStr(myStr) {
  }


  bool isInt(string str, int idx) const {
    return (idx < str.size() && str[idx] >= '0' && str[idx] <= '9');
  }

  int readInt(string str, int &idx) const {
    string result;
    while (isInt(str, idx)) {
      result += str[idx++];
    }
    stringstream s(result);
    int i;
    s >> i;
    return i;
  }

  void checkInCorrectOrder(int &result, string &stringL, int &idxL, string &stringR, int &idxR) const {
    while (result == 2) {
      // correct because equal(?)
      if (idxL >= stringL.size() && idxR >= stringR.size()) {
        result = 1;
        break;
      }
      if (idxR >= stringR.size()) {
        result = 0;
        break;
      }
      if (idxL >= stringL.size()) {
        result = 1;
        break;
      }

      // both are ints
      if (isInt(stringL, idxL) && isInt(stringR, idxR)) {
        int leftInt = readInt(stringL, idxL);
        int rightInt = readInt(stringR, idxR);
        if (leftInt < rightInt) {
          result = 1;
          break;
        }
        if (leftInt > rightInt) {
          result = 0;
          break;
        }
        continue;
      }

      // both are lists
      if (stringL[idxL] == '[' && stringR[idxR] == '[') {
        // enter loop
        idxL++;
        idxR++;
        //checkInCorrectOrder(result, stringL, idxL, stringR, idxR);
        continue;
      }

      // Handle seeing Left list and Right integer
      if (stringL[idxL] == '[' && isInt(stringR, idxR)) {
        int oldR = idxR;
        int rightInt = readInt(stringR, idxR);
        stringstream s;
        s << rightInt;
        stringR.replace(oldR, s.str().size(), string("[") + s.str() + "]");
        idxR = oldR;
        continue; // go into loop the next time
      }

      // Handle seeing right list and left integer
      if (stringR[idxR] == '[' && isInt(stringL, idxL)) {
        int oldL = idxL;
        int leftInt = readInt(stringL, idxL);
        stringstream s;
        s << leftInt;
        stringL.replace(oldL, s.str().size(), string("[") + s.str() + "]");
        idxL = oldL;
        continue; // go into loop the next time
      }

      // handle seeing both commas
      if (stringL[idxL] == ',' && stringR[idxR] == ',') {
        // compare the next number
        idxL++;
        idxR++;
        continue;
      }

      // break at the end of lists
      if (stringR[idxR] == ']' && stringL[idxL] == ']') {
        idxL++;
        idxR++;
        break;
      }

      // Left list longer than right list
      if (stringL[idxL] != ']' && stringR[idxR] == ']') {
        result = 0;
        break;
      }

      // Right list longer than left list
      if (stringR[idxR] != ']' && stringL[idxL] == ']') {
        result = 1;
        break;
      }

      cout << "ERROR: you should never make it here: " << endl;
      cout << "stringL: " << endl;
      cout << stringL << endl;
      cout << "idxL: " << idxL << endl;
      cout << "stringR: " << endl;
      cout << stringR << endl;
      cout << "idxR: " << idxR << endl;
      cout << endl;
    }
  }

  bool operator<(const Packet& other) const {
    int idxL = 0;
    int idxR = 0;
    string otherStr = other.myStr;
    int r = 2;
    string thisStr = myStr;
    checkInCorrectOrder(r, thisStr, idxL, otherStr, idxR);
    return r != 0;
  }
};

class Assignment {
public:

  int solution() {

    vector<Packet> packets;
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      // hope that this works
      packets.push_back(Packet(line));
    }
    packets.push_back(Packet("[[2]]"));
    packets.push_back(Packet("[[6]]"));
    sort(packets.begin(), packets.end());
    int result = 1;
    for (int i = 0;i<packets.size();i++) {
      if (packets[i].myStr == "[[2]]" || packets[i].myStr == "[[6]]") {
        result *= i + 1;
      }
    }
    return result;
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
