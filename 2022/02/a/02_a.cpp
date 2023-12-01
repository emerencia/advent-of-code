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


class B01 {
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
      if (us == 'X') {
        score += 1;
        if (enemy == 'A') score += 3;
        if (enemy == 'C') score += 6;
      }
      if (us == 'Y') {
        score += 2;
        if (enemy == 'A') score += 6;
        if (enemy == 'B') score += 3;
      }
      if (us == 'Z') {
        score += 3;
        if (enemy == 'B') score += 6;
        if (enemy == 'C') score += 3;
      }
    } while (cin.good());
    return score;
  };
};

using namespace std;

int main() {
  B01 obj;
  cout << obj.calcScore() << endl;
}
