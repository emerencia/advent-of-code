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

char mem[1000][1000];

class Assignment {
public:
  int highestY;

  void replace_substring(string &s, const string &olds, const string &news) {
    size_t pos = s.find(olds);
    while (pos != string::npos) {
      s = s.substr(0, pos) + news + s.substr(pos + olds.size());
      pos = s.find(olds);
    }
  }

  void drawLineSegment(PII from, PII to) {
    if (from.first == to.first) {
      if (to.second < from.second) swap(from, to);
      for (int y = from.second; y <= to.second; y++) {
        if (y > highestY) highestY = y;
        mem[from.first][y] = '#';
      }
    } else { // from.second == to.second
      if (to.first < from.first) swap(from, to);
      if (from.second > highestY) highestY = from.second;
      for (int x = from.first; x <= to.first; x++) {
        mem[x][from.second] = '#';
      }
    }
  }

  void drawLine(string line) {
    replace_substring(line, " ->", "");
    stringstream s(line);
    int x, y;
    PII previous = {-1, -1};
    PII current;
    while (s >> x) {
      s.ignore();
      s >> y;
      current = {x, y};
      if (previous.first != -1 || previous.second != -1) {
        drawLineSegment(previous, current);
      }
      previous = current;
    }
  }

  bool comesToRest(int x, int y) {
    while (true) {
      if (y > highestY) return false;

      if (mem[x][y + 1] == '.') {
        y++;
        continue;
      }
      if (mem[x-1][y+1] == '.') {
        x--;
        y++;
        continue;
      }
      if (mem[x+1][y+1] == '.') {
        x++;
        y++;
        continue;
      }
      mem[x][y] = 'o';
      break;
    }
    return true;
  }

  int solution() {
    fill(&mem[0][0], &mem[1000][0], '.');
    highestY = 1;
    int result = 0;
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      drawLine(line);
    }

    /*
    for (int y = 0; y < 11; y++) {
      for (int x = 493; x < 505; x++) {
        cout << mem[x][y];
      }
      cout << endl;
    }
    */
    while (comesToRest(500,0)) {
      result++;
    }
    return result;
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
