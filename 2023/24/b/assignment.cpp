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
typedef long double LD;
typedef pair<int, int> PII;

const LD EPS = 1e-2;
const int MAX_SPEED = 500;

struct Hailstone {
  LL posX;
  LL posY;
  LL posZ;
  int velX;
  int velY;
  int velZ;

  Hailstone(LL posX, LL posY, LL posZ, int velX, int velY, int velZ) : posX(posX), posY(posY), posZ(posZ), velX(velX),
                                                                       velY(velY), velZ(velZ) {}

  [[nodiscard]] bool intersectsWith(const Hailstone &other) const {
    // Check for relative motion
    int relVelX = velX - other.velX;
    int relVelY = velY - other.velY;
    int relVelZ = velZ - other.velZ;

    if (relVelX == 0 && relVelY == 0 && relVelZ == 0) {
      // If relative velocities are all zero, check if they start at the same position
      return (posX == other.posX) && (posY == other.posY) && (posZ == other.posZ);
    }

    // Solving for t in each coordinate
    // Check if all t's are the same for the positions to intersect
    LD tx = (relVelX != 0) ? static_cast<LD>(other.posX - posX) / relVelX : -1.0;
    LD ty = (relVelY != 0) ? static_cast<LD>(other.posY - posY) / relVelY : -1.0;
    LD tz = (relVelZ != 0) ? static_cast<LD>(other.posZ - posZ) / relVelZ : -1.0;

    // Check if tx, ty, and tz are all equal (or if they are not applicable due to zero relative velocity)
    bool xEqual = (relVelX == 0) || abs(tx - ty) < EPS || abs(tx - tz) < EPS;
    bool yEqual = (relVelY == 0) || abs(ty - tz) < EPS;

    return xEqual && yEqual;
  }
};


class Assignment {
public:
  vector<Hailstone> hailstones;

  LL solution() {
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      LL posX, posY, posZ;
      int velX, velY, velZ;
      sscanf(line.c_str(), "%lld, %lld, %lld @ %d, %d, %d", &posX, &posY, &posZ, &velX, &velY, &velZ);
      hailstones.emplace_back(posX, posY, posZ, velX, velY, velZ);
    }
    // I make the assumption that the speed vector of the "line that intersects everything" is within -500, 500
    // for x, y, and z. This is from looking at the input data, and the fact that it has to intersect all the
    // lines, so if the speed is too high then in one nanosecond it skips a lot of area, so my idea was that
    // it's probably not that different from the velocity vectors of the hailstones. Also, it was given that
    // the speed was an integer amount, so we can just iterate over all possible values.
    //
    // Given that we can iterate over all possible velocity vectors in a reasonable range, we only need to find
    // the position vector of our "line that intersects everything". So we take any two hailstones a and b, and
    // let our "line that intersects everything" be called c. Then we solve the formulas where:
    //
    // position a + velocity a * t1 = position c + velocity c * t1
    // position b + velocity b * t2 = position c + velocity c * t2
    //
    // The only unknowns here are the position of c and t1 and t2. But each formula
    // gives us three equations (one for x, one for y, and one for z), so in fact there
    // are more equations than unknowns, and we can even sanity check our result.
    //
    // After finding the position of c, we check if it intersects with all other hailstones.
    for (int velX = -MAX_SPEED; velX <= MAX_SPEED; ++velX) {
      for (int velY = -MAX_SPEED; velY <= MAX_SPEED; ++velY) {
        for (int velZ = -MAX_SPEED; velZ <= MAX_SPEED; ++velZ) {
          // randomly pick two hailstones from the hailstones, and determine from that the intersecting line.
          // These can be any two hailstones (because if this is the correct speed vector, then it has to
          // hold for all the hailstones).
          Hailstone a = hailstones[0];
          Hailstone b = hailstones[1];
          // See the_math.jpg for the formulas.
          LD f = static_cast<LD>(a.velX) - velX;
          LD g = static_cast<LD>(a.velY) - velY;
          LD t2 = (f * (b.posY - a.posY) - g * (b.posX - a.posX)) / (g * (b.velX - velX) - f * (b.velY - velY));
          LD t1x = (b.posX + t2 * (b.velX - velX) - a.posX) / f;
          LD t1y = (b.posY + t2 * (b.velY - velY) - a.posY) / g;
          LD t1z = (b.posZ + t2 * (b.velZ - velZ) - a.posZ) / (static_cast<LD>(a.velZ) - velZ);
          if (abs(t1x - t1y) >= EPS || abs(t1x - t1z) >= EPS) {
            continue;
          }
          // We now know that the different values for t1 are not too far apart. To make our estimate
          // even more accurate, calculate the average of the three values (if they are not NaN) and
          // use that as actual t1.
          LL count = 0;
          LD t1 = 0.0;
          // if t1x is not nan
          if (t1x == t1x) {
            t1 += t1x;
            count++;
          }
          // if t1y is not nan
          if (t1y == t1y) {
            t1 += t1y;
            count++;
          }
          // if t1z is not nan
          if (t1z == t1z) {
            t1 += t1z;
            count++;
          }
          if (count == 0) {
            continue;
          }
          t1 /= count;

          // Because we have more formulas than unknowns, we can check if the result is correct.
          LL posxa = static_cast<LL>(round(a.posX + t1 * (a.velX - velX)));
          LL posxb = static_cast<LL>(round(b.posX + t2 * (b.velX - velX)));
          if (posxa != posxb) {
            continue;
          }

          LL posya = static_cast<LL>(round(a.posY + t1 * (a.velY - velY)));
          LL posyb = static_cast<LL>(round(b.posY + t2 * (b.velY - velY)));
          if (posya != posyb) {
            continue;
          }

          LL posza = static_cast<LL>(round(a.posZ + t1 * (a.velZ - velZ)));
          LL poszb = static_cast<LL>(round(b.posZ + t2 * (b.velZ - velZ)));
          if (posza != poszb) {
            continue;
          }

          // hailstone c is "line that intersects everything"
          Hailstone c(posxa, posya, posza, velX, velY, velZ);
          bool intersectsAll = true;
          for (const auto &hailstone: hailstones) {
            if (!c.intersectsWith(hailstone)) {
              intersectsAll = false;
              break;
            }
          }
          if (intersectsAll) {
            // Note that for the given input data, there is only one possible result in the entire search space.
            return posxa + posya + posza;
          }
        }
      }
    }
    return -1;
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
