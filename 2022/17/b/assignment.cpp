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
const int GRID_SIZE = 10000000;
const LL TOTAL_ROCKS = 1000000000000;
char grid[GRID_SIZE][CHAMBER_WIDTH];

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
  int towerHeight(const string &pattern, int numberOfRocks) {
    fill(&grid[0][0], &grid[GRID_SIZE][0], '.');
    // set the floor.
    for (int i = 0; i < CHAMBER_WIDTH; i++) {
      grid[0][i] = '#';
    }
    int highestPoint = 0;
    int patternIdx = 0;
    int rockIdx = -1;
    for (int i = 0; i < numberOfRocks; i++) {
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

  LL solution() {
    while (cin.good()) {
      string pattern;
      getline(cin, pattern);
      if (pattern.empty()) continue;

      // This solution is brute force.
      // My idea was that at some point, there would be a repeating pattern, where:
      // if you simulate a tower with height X
      // then simulate a tower with height 2*X
      // Comparing two times the height X tower against a tower of height 2*X would
      // give difference of Y, where the towers "overlap".
      // and then you could predict the length of a tower of height 3*X by
      // calculating 3*X - 2*Y.
      // The solution below finds a repeating pattern at i = 1750, which resulted
      // in the correct answer.

      const int CONFIRMATION_DISTANCE = 4;
      const int CONFIRMATION_DISTANCE2 = 3;
      LL realOverlap = 0;
      LL realPatternLength = 0;
      LL realSimH = 0;
      for (int i = 1; i < 80000; i++) {
        if (i % 100 == 0) cout << '.' << flush;
        if (i % 1000 == 0) cout << endl << flush;
        LL simHeight = towerHeight(pattern, i);
        LL simHeight2 = towerHeight(pattern, 2 * i);
        LL overLap = 2 * simHeight - simHeight2;
        LL simHeight4 = towerHeight(pattern, CONFIRMATION_DISTANCE * i);
        LL expectedHeight4 = CONFIRMATION_DISTANCE * simHeight - (CONFIRMATION_DISTANCE - 1) * overLap;
        LL simHeight3 = towerHeight(pattern, CONFIRMATION_DISTANCE2 * i);
        LL expectedHeight3 = CONFIRMATION_DISTANCE2 * simHeight - (CONFIRMATION_DISTANCE2 - 1) * overLap;
        if (simHeight4 == expectedHeight4 && simHeight3 == expectedHeight3) {
          cout << endl << "repeating pattern length: " << i << endl;
          cout << "overLap: " << overLap << endl;
          bool good = true;
          for (LL factor = 2; factor < 20; factor++) {
            cout << "factor: " << factor << endl;
            LL simH = towerHeight(pattern, factor * i);
            LL exH = factor * simHeight - (factor - 1) * overLap;
            if (simH != exH) {
              cout << "proven WRONG at factor " << factor << endl;
              good = false;
              break;
            } else {
              cout << "passed at factor: " << factor << endl;
            }
          }
          if (good) {
            realOverlap = overLap;
            realPatternLength = i;
            realSimH = simHeight;
            break;
          }
        }
      }

      LL timesFitting = TOTAL_ROCKS / realPatternLength;
      cout << "timesFitting: " << timesFitting << endl;
      LL totalHeight = (timesFitting - 1) * (realSimH - realOverlap);
      cout << "total height (without remainder): " << totalHeight << endl;
      LL sizeRemaining = TOTAL_ROCKS % realPatternLength;
      LL remainder = towerHeight(pattern, realPatternLength + sizeRemaining);
      cout << "remaining size of things to do: " << remainder << endl;
      LL grandTotal = totalHeight + remainder;
      cout << "GRAND TOTAL: " << grandTotal << endl;
      return grandTotal;
    }
    return 0;
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
