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

struct Hailstone {
  LL posX;
  LL posY;
  LL posZ;
  int velX;
  int velY;
  int velZ;

  Hailstone(LL posX, LL posY, LL posZ, int velX, int velY, int velZ) : posX(posX), posY(posY), posZ(posZ), velX(velX),
                                                                       velY(velY), velZ(velZ) {}
};

const long double EPS = 1e-2;

LL areaMin = 200000000000000;
LL areaMax = 400000000000000;

class Assignment {
public:
  vector<Hailstone> hailstones;

  static bool intersects(const Hailstone &a, const Hailstone &b) {
    long double tb = (static_cast<long double>(a.velY * b.posX) - a.velY * a.posX - a.velX * b.posY + a.velX * a.posY) /
                     (a.velX * b.velY - a.velY * b.velX);
    long double ta = (static_cast<long double>(b.posY) + b.velY * tb - a.posY) / a.velY;
    if (ta < 0 || tb < 0) return false;
    long double xa = a.posX + a.velX * ta;
    long double ya = a.posY + a.velY * ta;
    long double xb = b.posX + b.velX * tb;
    long double yb = b.posY + b.velY * tb;
    if (abs(xa - xb) >= EPS || abs(ya - yb) >= EPS) {
      cout << "ERROR: lines don't intersect: " << xa << " " << ya << " " << xb << " " << yb << endl;
      cout << abs(xa - xb) << " " << abs(ya - yb) << endl;
      exit(1);
    }
    return (xa >= areaMin && xa <= areaMax && ya >= areaMin && ya <= areaMax);
  }

  int numberOfIntersections() {
    int ans = 0;
    for (int i = 0; i < (int) hailstones.size(); i++) {
      for (int j = i + 1; j < (int) hailstones.size(); j++) {
        if (intersects(hailstones[i], hailstones[j])) {
          ans++;
        }
      }
    }
    return ans;
  }

  int solution() {
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      LL posX, posY, posZ;
      int velX, velY, velZ;
      sscanf(line.c_str(), "%lld, %lld, %lld @ %d, %d, %d", &posX, &posY, &posZ, &velX, &velY, &velZ);
      hailstones.emplace_back(posX, posY, posZ, velX, velY, velZ);
    }
    if (hailstones.size() < 10) {
      areaMin = 7;
      areaMax = 27;
    }
    return numberOfIntersections();
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
