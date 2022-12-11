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

class Assignment {
public:

  void checkAdd(int cycle, int x) {
    int modCycle = ((cycle - 1)%40)+1;
    // cycle is indexed from 1, while x is indexed from 0
    if (modCycle == x || modCycle == x+1 || modCycle == x+2) {
      cout << "#";
    } else {
      cout << ".";
    }
    if (cycle%40 == 0) {
      cout << endl;
    }
  }

  void solution() {
    int x = 1;
    int cycle = 1;
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      stringstream s(line);
      string operation;
      s >> operation;
      if (operation == "noop") {
        // do nothing
        checkAdd(cycle, x);
        cycle++;
      } else {
        int amount;
        s >> amount;
        checkAdd(cycle, x);
        cycle++;
        checkAdd(cycle, x);
        cycle++;
        x += amount;
      }
    }
  }
};

int main() {
  Assignment obj;
  obj.solution();
  /*
   * This is what it outputs:
   * ####.###..#..#.###..#..#.####..##..#..#.
   * #....#..#.#..#.#..#.#..#....#.#..#.#..#.
   * ###..###..#..#.#..#.####...#..#....####.
   * #....#..#.#..#.###..#..#..#...#....#..#.
   * #....#..#.#..#.#.#..#..#.#....#..#.#..#.
   * #....###...##..#..#.#..#.####..##..#..#.
   *
   * aka: FBURHZCH
   */
}
