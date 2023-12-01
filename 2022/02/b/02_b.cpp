#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>
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

using namespace std;
typedef long long LL;
typedef pair<int, int> PII;


class B02 {
public:

  int calcScore() {
    int score = 0;
    while (cin.good()) {
      string l;
      getline(cin,l);
      if (!l.size()) continue;
      char enemy;
      char us;
      stringstream s(l);
      s >> enemy >> us;
      if (us == 'X') { // i must lose
        if (enemy == 'A') score += 3;
        if (enemy == 'B') score += 1;
        if (enemy == 'C') score += 2;
      }
      if (us == 'Y') { // i must draw
        score += 3;
        if (enemy == 'A') score += 1;
        if (enemy == 'B') score += 2;
        if (enemy == 'C') score += 3;
      }
      if (us == 'Z') { // i must win
        score += 6;
        if (enemy == 'A') score += 2;
        if (enemy == 'B') score += 3;
        if (enemy == 'C') score += 1;
      }
    } while (cin.good());
    return score;
  };
};

using namespace std;

int main() {
  B02 obj;
  cout << obj.calcScore() << endl;
}
