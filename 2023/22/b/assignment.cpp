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

struct Brick {
  int minX;
  int maxX;
  int minY;
  int maxY;
  int minZ;
  int maxZ;
  static int count;
  int id;
  set<int> supports;
  set<int> supportedBy;

  Brick(int minX, int maxX, int minY, int maxY, int minZ, int maxZ) : minX(minX), maxX(maxX), minY(minY), maxY(maxY),
                                                                      minZ(minZ), maxZ(maxZ) {
    id = ++count;
  }

  bool operator<(const Brick &other) const {
    if (minZ != other.minZ) return minZ < other.minZ;
    if (maxZ != other.maxZ) return maxZ < other.maxZ;
    if (minX != other.minX) return minX < other.minX;
    if (maxX != other.maxX) return maxX < other.maxX;
    if (minY != other.minY) return minY < other.minY;
    if (maxY != other.maxY) return maxY < other.maxY;
    return false;
  }

  friend ostream &operator<<(ostream &os, const Brick &brick) {
    os << (char) ('A' + brick.id - 1);
    return os;
  }
};

int Brick::count = 0;

int occupado[10][10][500];

class Assignment {
public:
  vector<Brick> bricks;

  auto &findBrick(int id) {
    for (auto &brick: bricks) {
      if (brick.id == id) return brick;
    }
    throw runtime_error("Brick not found");
  }

  void settleBricks() {
    // bricks are already sorted
    for (auto &brick: bricks) {
      int minX = brick.minX;
      int maxX = brick.maxX;
      int minY = brick.minY;
      int maxY = brick.maxY;
      int minZ = brick.minZ;
      int maxZ = brick.maxZ;

      int levelToSettle = minZ;
      bool allFree = true;
      while (allFree) {
        levelToSettle--;
        for (int i = minX; i <= maxX; ++i) {
          for (int j = minY; j <= maxY; ++j) {
            if (occupado[i][j][levelToSettle] != -1) {
              allFree = false;
              if (occupado[i][j][levelToSettle] != 0) {
                auto &sBrick = findBrick(occupado[i][j][levelToSettle]);
                sBrick.supports.insert(brick.id);
                brick.supportedBy.insert(sBrick.id);
              }
            }
          }
        }
      }
      levelToSettle++;
      brick.maxZ = maxZ - (minZ - levelToSettle);
      brick.minZ = levelToSettle;
      for (int i = minX; i <= maxX; ++i) {
        for (int j = minY; j <= maxY; ++j) {
          for (int k = brick.minZ; k <= brick.maxZ; ++k) {
            occupado[i][j][k] = brick.id;
          }
        }
      }
    }
  }

  int numberOfOtherBricksThatWouldFallIfBrickWereDisintegrated(const Brick &brick) {
    set<int> fallingBricks;
    queue<int> q;
    q.push(brick.id);
    while (!q.empty()) {
      int id = q.front();
      q.pop();
      auto &cBrick = findBrick(id);
      if (fallingBricks.find(id) != fallingBricks.end()) continue;
      fallingBricks.insert(id);
      for (auto &support: cBrick.supports) {
        auto &sBrick = findBrick(support);
        int stillStanding = 0;
        for (auto &supportedBy: sBrick.supportedBy) {
          if (fallingBricks.find(supportedBy) == fallingBricks.end()) {
            stillStanding++;
          }
        }
        if (stillStanding == 0) {
          q.push(support);
        }
      }
    }
    return (int) fallingBricks.size() - 1;
  }

  int sumOfOtherBricksThatWouldFall() {
    int result = 0;
    for (const auto &brick: bricks) {
      result += numberOfOtherBricksThatWouldFallIfBrickWereDisintegrated(brick);
    }
    return result;
  }

  int solution() {
    memset(occupado, -1, sizeof(occupado));
    // the floor occupies the first layer
    for (auto &i: occupado) {
      for (auto &j: i) {
        j[0] = 0;
      }
    }
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      int minX, maxX, minY, maxY, minZ, maxZ;
      sscanf(line.c_str(), "%d,%d,%d~%d,%d,%d", &minX, &minY, &minZ, &maxX, &maxY, &maxZ);
      if (minX > maxX) swap(minX, maxX);
      if (minY > maxY) swap(minY, maxY);
      if (minZ > maxZ) swap(minZ, maxZ);
      bricks.emplace_back(minX, maxX, minY, maxY, minZ, maxZ);
    }
    sort(bricks.begin(), bricks.end());
    settleBricks();
    return sumOfOtherBricksThatWouldFall();
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
