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
typedef tuple<LL, LL, LL> TLLL;


const LD EPS = 1e-2;

LL areaMin = 200000000000000;
LL areaMax = 400000000000000;

const int MAX_SPEED = 1000;

struct Hailstone {
  LL posX;
  LL posY;
  LL posZ;
  int velX;
  int velY;
  int velZ;

  Hailstone(LL posX, LL posY, LL posZ, int velX, int velY, int velZ) : posX(posX), posY(posY), posZ(posZ), velX(velX),
                                                                       velY(velY), velZ(velZ) {}

  [[nodiscard]] bool isParallelWith(const Hailstone &other) const {
    LD factor = static_cast<LD>(velX) / other.velX;
    return abs(factor * other.velY - velY) < EPS && abs(factor * other.velZ - velZ) < EPS;
  }

  [[nodiscard]] static TLLL crossProduct(const TLLL &a, const TLLL &b) {
    return make_tuple(
        get<1>(a) * get<2>(b) - get<2>(a) * get<1>(b),
        get<2>(a) * get<0>(b) - get<0>(a) * get<2>(b),
        get<0>(a) * get<1>(b) - get<1>(a) * get<0>(b));
  }

  [[nodiscard]] static LL dotProduct(const TLLL &a, const TLLL &b) {
    return get<0>(a) * get<0>(b) + get<1>(a) * get<1>(b) + get<2>(a) * get<2>(b);
  }

  [[nodiscard]] bool sharesAPlane(const Hailstone &other) const {
    // Two lines lie in the same plane if and only if the direction vectors are coplanar with the vector
    // connecting any point on one line to any point on the other line. We use the cross product of the
    // direction vectors to find a normal vector to the plane formed by these two lines.
    // Then we check if the vector connecting the two points is perpendicular to this normal
    // vector (using the dot product).
    TLLL direction_vector1 = make_tuple(velX, velY, velZ);
    TLLL direction_vector2 = make_tuple(other.velX, other.velY, other.velZ);
    TLLL plane_vector = make_tuple(other.posX - posX, other.posY - posY, other.posZ - posZ);

    TLLL normal_vector = crossProduct(direction_vector1, direction_vector2);
    LL result = dotProduct(plane_vector, normal_vector);
    if (result < 100) {
      // cout << "found small result: " << result << endl;
    }
    return result == 0;
  }

  [[nodiscard]] bool parallelInTwoOutOfThreeDimensions(const Hailstone &other) const {
    LD factor = static_cast<LD>(velX) / other.velX;
    if (abs(factor * other.velY - velY) < EPS || abs(factor * other.velZ - velZ) < EPS) return true;
    factor = static_cast<LD>(velY) / other.velY;
    if (abs(factor * other.velX - velX) < EPS || abs(factor * other.velZ - velZ) < EPS) return true;
    factor = static_cast<LD>(velZ) / other.velZ;
    if (abs(factor * other.velX - velX) < EPS || abs(factor * other.velY - velY) < EPS) return true;
    return false;
  }

  static TLLL subtractVectors(const TLLL &a, const TLLL &b) {
    return make_tuple(
        get<0>(a) - get<0>(b),
        get<1>(a) - get<1>(b),
        get<2>(a) - get<2>(b));
  }

  // Function to find the line of intersection between two planes
  static pair<TLLL, TLLL> findIntersectionLine(
      const Hailstone &h1, const Hailstone &h2, const Hailstone &h3, const Hailstone &h4) {

    // Calculate direction vectors of each hailstone
    TLLL D1 = make_tuple(h1.velX, h1.velY, h1.velZ);
    TLLL D2 = make_tuple(h2.velX, h2.velY, h2.velZ);
    TLLL D3 = make_tuple(h3.velX, h3.velY, h3.velZ);
    TLLL D4 = make_tuple(h4.velX, h4.velY, h4.velZ);

    // Find normal vectors of the planes
    TLLL N1 = crossProduct(D1, D2);
    TLLL N2 = crossProduct(D3, D4);

    // Direction vector of the line of intersection
    TLLL lineDirection = crossProduct(N1, N2);

    // Find a point on each plane (using positions of h1 and h3)
    TLLL P1 = make_tuple(h1.posX, h1.posY, h1.posZ);
    TLLL P2 = make_tuple(h3.posX, h3.posY, h3.posZ);

    // Solve the system of equations to find a point on the line of intersection
    // (using Cramer's rule)
    TLLL P21 = subtractVectors(P2, P1);
    TLLL N21 = subtractVectors(N2, N1);
    TLLL P21crossN21 = crossProduct(P21, N21);
    LD denominator = dotProduct(lineDirection, lineDirection);
    LD t1 = static_cast<LD>(dotProduct(P21crossN21, N2)) / denominator;
    // LD t2 = static_cast<LD>(dotProduct(P21crossN21, N1)) / denominator;
    // return the point of intersection
    TLLL linePoint = make_tuple(
        static_cast<LL>(round(h1.posX + t1 * h1.velX)),
        static_cast<LL>(round(h1.posY + t1 * h1.velY)),
        static_cast<LL>(round(h1.posZ + t1 * h1.velZ)));


    cout << " INTERSECTION DIRECTION: " << get<0>(lineDirection) << " " << get<1>(lineDirection) << " "
         << get<2>(lineDirection) << endl;
    cout << " INTERSECTION POINT: " << get<0>(linePoint) << " " << get<1>(linePoint) << " " << get<2>(linePoint)
         << endl;

    // Return the line as a pair of point and direction
    return make_pair(linePoint, lineDirection);
  }

  bool intersectsWith(const Hailstone &other) {
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

  bool operator<(const Hailstone &other) const {
    if (posX == other.posX) {
      if (posY == other.posY) {
        return posZ < other.posZ;
      }
      return posY < other.posY;
    }
    return posX < other.posX;
  }
};


class Assignment {
public:
  vector<Hailstone> hailstones;
  set<Hailstone> intersectingHailstones;

  bool intersects(const Hailstone &a, const Hailstone &b) {
    LD tb = (static_cast<LD>(a.velY * b.posX) - a.velY * a.posX - a.velX * b.posY + a.velX * a.posY) /
            (a.velX * b.velY - a.velY * b.velX);
    LD ta = (static_cast<LD>(b.posY) + b.velY * tb - a.posY) / a.velY;
    if (ta < 0 || tb < 0) return false;
    LD xa = a.posX + a.velX * ta;
    LD ya = a.posY + a.velY * ta;
    LD xb = b.posX + b.velX * tb;
    LD yb = b.posY + b.velY * tb;
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

  void findParallellHailstones() {
    // find any pair of hailstones that are parallel in 3d-space
    // and print them.
    // edit: This did not give any results.
    for (int i = 0; i < (int) hailstones.size(); i++) {
      for (int j = i + 1; j < (int) hailstones.size(); j++) {
        if (hailstones[i].isParallelWith(hailstones[j])) {
          cout << hailstones[i].posX << " " << hailstones[i].posY << " " << hailstones[i].posZ << " "
               << hailstones[i].velX << " " << hailstones[i].velY << " " << hailstones[i].velZ << endl;
          cout << "is parallel with" << endl;
          cout << hailstones[j].posX << " " << hailstones[j].posY << " " << hailstones[j].posZ << " "
               << hailstones[j].velX << " " << hailstones[j].velY << " " << hailstones[j].velZ << endl;
          cout << endl;
        }
      }
    }
  }

  void printHailstones() {
    /* outputs like:
     data = {
        {{19, 13, 30}, {-2, 1, -2}},
        {{18, 19, 22}, {-1, -1, -2}},
        {{20, 25, 34}, {-2, -2, -4}},
        {{12, 31, 28}, {-1, -2, -1}},
        {{20, 19, 15}, {1, -5, -3}}
      };
     */
    cout << "data = {" << endl;
    for (auto &hailstone: intersectingHailstones) {
      cout << "  {{" << hailstone.posX << ", " << hailstone.posY << ", " << hailstone.posZ << "}, {"
           << hailstone.velX << ", " << hailstone.velY << ", " << hailstone.velZ << "}}," << endl;
    }
    cout << "};" << endl;
  }

  void findHailstonePlanes() {
    // find any pair of hailstones that share a plane in 3d-space
    // and print them.
    // edit: This did not give any results either.
    for (int i = 0; i < (int) hailstones.size(); i++) {
      for (int j = i + 1; j < (int) hailstones.size(); j++) {
        if (hailstones[i].sharesAPlane(hailstones[j])) {
          cout << hailstones[i].posX << " " << hailstones[i].posY << " " << hailstones[i].posZ << " "
               << hailstones[i].velX << " " << hailstones[i].velY << " " << hailstones[i].velZ << endl;
          cout << "shares a plane with" << endl;
          cout << hailstones[j].posX << " " << hailstones[j].posY << " " << hailstones[j].posZ << " "
               << hailstones[j].velX << " " << hailstones[j].velY << " " << hailstones[j].velZ << endl;
          cout << endl;
        }
      }
    }
  }

  LL gcd(LL a, LL b) {
    if (b == 0) return a;
    return gcd(b, a % b);
  }

  void findParallellInTwoOutOfThreeDimensions() {
    // find any pair of hailstones that are parallel in two out of three dimensions
    // and print them.
    for (int i = 0; i < (int) hailstones.size(); i++) {
      for (int j = i + 1; j < (int) hailstones.size(); j++) {
        if (hailstones[i].parallelInTwoOutOfThreeDimensions(hailstones[j])) {

          cout << hailstones[i].posX << " " << hailstones[i].posY << " " << hailstones[i].posZ << " "
               << hailstones[i].velX << " " << hailstones[i].velY << " " << hailstones[i].velZ << endl;
          cout << "is parallel in two out of three dimensions with" << endl;
          cout << hailstones[j].posX << " " << hailstones[j].posY << " " << hailstones[j].posZ << " "
               << hailstones[j].velX << " " << hailstones[j].velY << " " << hailstones[j].velZ << endl;
          cout << endl;

          intersectingHailstones.insert(hailstones[i]);
          intersectingHailstones.insert(hailstones[j]);
        }
      }
    }
  }

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
    if (hailstones.size() < 10) {
      areaMin = 7;
      areaMax = 27;
    }
    // findParallellHailstones();
    // findHailstonePlanes();
    // findParallellInTwoOutOfThreeDimensions();
    // printHailstones();

    // we have our first plane defined by
    //  {{274398685610431, 223930178332215, 310958347169513}, {89, 133, -89}},
    //  {{350319329813041, 199257804608985, 240601588254983}, {60, 352, -60}},
    //  {{378474845971131, 285516010119715, 213570667836013}, {-25, -53, 25}},
    // (probably just two of those is enough)
    // Then if we have a second plane defined by:
    // 292396778257401 271883737118025 272444274199903 @ 10 18 30
    // 227077422437462 292755203727942 358470242728266 @ 8 -12 -20
    // Then the intersection of the two planes is:
    /*
    Hailstone h1(274398685610431, 223930178332215, 310958347169513, 89, 133, -89);
    Hailstone h2(350319329813041, 199257804608985, 240601588254983, 60, 352, -60);
    Hailstone h3(292396778257401, 271883737118025, 272444274199903, 10, 18, 30);
    Hailstone h4(227077422437462, 292755203727942, 358470242728266, 8, -12, -20);

    Hailstone::findIntersectionLine(h1, h2, h3, h4);
    */

    // INTERSECTION DIRECTION: -10273120 6163872 10273120
    // INTERSECTION POINT: 274398688567541 223930182751267 310958344212403

    // cout << "gcd: " << gcd(10273120, 6163872) << endl;

    // cout << 10273120 / gcd(10273120, 6163872) << " " << 6163872 / gcd(10273120, 6163872) << endl;

    // THE INTERSECTION DIRECTION IS ACTUALLY -5 3 5
    // edit: it's not.

    // NEW IDEA: because it has so many possible intersections, the speed vector has to be small since it has to
    // hit all the lines at different times. So just iterate over all possible speed vectors and see if they intersect everything.

    // We can solve this because we have 3 equations and 2 unknowns, see the_math.jpg for the formulas,
    // but the ideas is as follows.
    // Given that we can iterate over all possible velocity vectors in a reasonable range, we only need to find
    // the position vector. So we take any two hailstones a and b, and let our "line that intersects everything"
    // be called c. Then we solve the formulas where:
    //
    // position a + velocity a * t1 = position c + velocity b * t1
    // position b + velocity b * t2 = position c + velocity c * t2
    //
    // The only unknowns here are the position of c and t1 and t2. But each formula
    // gives us three equations (one for x, one for y, and one for z), so in fact there
    // are more equations than unknowns, and we can even sanity check our result.
    for (int countx = 0; countx <= MAX_SPEED; ++countx) {
      int velX = (countx % 2 == 0) ? countx / 2 : (-countx / 2);
      for (int county = 0; county <= MAX_SPEED; ++county) {
        int velY = (county % 2 == 0) ? county / 2 : (-county / 2);
        for (int countz = 0; countz <= MAX_SPEED; ++countz) {
          int velZ = (countz % 2 == 0) ? countz / 2 : (-countz / 2);
          // randomly pick two hailstones from the hailstones, and determine from that the intersecting hailstone
          Hailstone a = hailstones[0];
          Hailstone b = hailstones[1];
          LD f = static_cast<LD>(a.velX) - velX;
          // cout << "f: " << f << endl;
          LD g = static_cast<LD>(a.velY) - velY;
          // cout << "g: " << g << endl;
          LD t2 = (f * (b.posY - a.posY) - g * (b.posX - a.posX)) / (g * (b.velX - velX) - f * (b.velY - velY));
          LD t1x = (b.posX + t2 * (b.velX - velX) - a.posX) / f;
          LD t1y = (b.posY + t2 * (b.velY - velY) - a.posY) / g;
          LD t1z = (b.posZ + t2 * (b.velZ - velZ) - a.posZ) / (static_cast<LD>(a.velZ) - velZ);
          if (abs(t1x - t1y) >= EPS || abs(t1x - t1z) >= EPS) {
            // cout << "ERROR: t1x != t1y != t1z: " << t1x << " " << t1y << " " << t1z << endl;
            continue;
          }
          // take the average to make it more accurate (hopefully)
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
            // cout << "ERROR: count == 0" << endl;
            continue;
          }
          t1 /= count;

          /*
          cout << "aposx: " << a.posX << " aposy: " << a.posY << " aposz: " << a.posZ << " avelx: " << a.velX << " avely: " << a.velY << " avelz: " << a.velZ << endl;
          cout << "velx: " << velX << " vely: " << velY << " velz: " << velZ << endl;
          cout << "t1: " << t1 << " t2: " << t2 << endl;
          */

          LL posxa = static_cast<LL>(round(a.posX + t1 * (a.velX - velX)));
          LL posxb = static_cast<LL>(round(b.posX + t2 * (b.velX - velX)));
          if (posxa != posxb) {
            // cout << "ERROR: posxa != posxb: " << posxa << " " << posxb << endl;
            continue;
          }

          LL posya = static_cast<LL>(round(a.posY + t1 * (a.velY - velY)));
          LL posyb = static_cast<LL>(round(b.posY + t2 * (b.velY - velY)));
          if (posya != posyb) {
            // cout << "ERROR: posya != posyb: " << posya << " " << posyb << endl;
            continue;
          }

          LL posza = static_cast<LL>(round(a.posZ + t1 * (a.velZ - velZ)));
          LL poszb = static_cast<LL>(round(b.posZ + t2 * (b.velZ - velZ)));
          if (posza != poszb) {
            // cout << "ERROR: posza != poszb: " << posza << " " << poszb << endl;
            continue;
          }

          // hailstone c is our intersection
          Hailstone c(posxa, posya, posza, velX, velY, velZ);
          bool intersectsAll = true;
          for (const auto &hailstone: hailstones) {
            if (!c.intersectsWith(hailstone)) {
              /*
              cout << "ERROR: hailstone does not intersect: " << hailstone.posX << " " << hailstone.posY << " "
                   << hailstone.posZ << " " << hailstone.velX << " " << hailstone.velY << " " << hailstone.velZ
                   << endl;
               */
              intersectsAll = false;
              break;
            }
          }
          if (intersectsAll) {
            /* This finds exactly one result:
             FOUND INTERSECTION: 420851642592931 273305746686315 176221626745613 -261 15 233
             added up position: 870379016024859
            */
            cout << "FOUND INTERSECTION: " << posxa << " " << posya << " " << posza << " " << velX << " " << velY << " "
                 << velZ << endl;
            cout << "added up position: " << posxa + posya + posza << endl;
            return posxa + posya + posza;
          }
        }
      }
    }

    // return numberOfIntersections();
    return -1;
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
