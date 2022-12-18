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

vector<vector<string>> rocks = {{"####"},

                                {".#.",
                                 "###",
                                 ".#."},

                                {"..#",
                                 "..#",
                                 "###"},

                                {"#",
                                 "#",
                                 "#",
                                 "#"},

                                {"##",
                                 "##"}};

const int CHAMBER_WIDTH = 7;
char grid[10000][CHAMBER_WIDTH];

class Assignment {
public:

  void addToGrid(int rockIdx, int topLeftX, int topLeftY) {
    // precondition: it won't collide
    vector<string> &rock = rocks[rockIdx];
    for (int i = 0; i < rock.size(); i++) {
      for (int j = 0; j < rock[i].size(); j++) {
        int y = topLeftY - i;
        int x = topLeftX + j;
        if (rock[i][j] == '#') {
          grid[y][x] = '#';
        }
      }
    }
  }

  bool collides(int rockIdx, int topLeftX, int topLeftY) {
    if (topLeftX < 0 || topLeftX >= CHAMBER_WIDTH) return true;
    // the topLeftY case == 0 is covered because we fill the floor
    if (topLeftY < 0) return true;

    vector<string> &rock = rocks[rockIdx];
    for (int i = 0; i < rock.size(); i++) {
      for (int j = 0; j < rock[i].size(); j++) {
        int y = topLeftY - i;
        int x = topLeftX + j;
        if (x >= CHAMBER_WIDTH || y < 0) return true;
        if (rock[i][j] == '#' && grid[y][x] == '#') return true;
      }
    }
    return false;
  }

  // chamber is 7 units wide
  // 0123456
  // .......
  //   ^ rock appears
  // bottom edge is 0 above the floor or highest rock.
  int towerHeight(const string &pattern) {
    fill(&grid[0][0], &grid[10000][0], '.');
    // set the floor.
    for (int i = 0; i < CHAMBER_WIDTH; i++) {
      grid[0][i] = '#';
    }
    int highestPoint = 0;
    int patternIdx = 0;
    int rockIdx = -1;
    for (int i = 0; i < 2022; i++) {
      rockIdx = (rockIdx + 1) % rocks.size();
      // drop a rock it spawns
      int topLeftY = highestPoint + 3 + rocks[rockIdx].size();
      int topLeftX = 2;
      bool done = false;
      while (!done) {
        // first left or right
        char patternMove = pattern[patternIdx];
        patternIdx = (patternIdx + 1) % pattern.size();
        int potentialNextTopLeftX = patternMove == '<' ? topLeftX - 1 : topLeftX + 1;
        int potentialNextTopLeftY = topLeftY;
        if (!collides(rockIdx, potentialNextTopLeftX, potentialNextTopLeftY)) {
          topLeftX = potentialNextTopLeftX;
          topLeftY = potentialNextTopLeftY;
        }
        // then down
        potentialNextTopLeftX = topLeftX;
        potentialNextTopLeftY = topLeftY - 1;
        if (!collides(rockIdx, potentialNextTopLeftX, potentialNextTopLeftY)) {
          // update the position to go one down
          topLeftX = potentialNextTopLeftX;
          topLeftY = potentialNextTopLeftY;
        } else {
          // add the rock to the grid
          addToGrid(rockIdx, topLeftX, topLeftY);
          // update the highest point if it changed.
          if (topLeftY > highestPoint) highestPoint = topLeftY;
          // signal to go to the next rock
          done = true;
        }
      }
    }
    return highestPoint;
  }

  int solution() {
    while (cin.good()) {
      string pattern;
      getline(cin, pattern);
      if (pattern.empty()) continue;

      return towerHeight(pattern);
    }
    return 0;
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
