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

typedef tuple<int, int, int> Junction;
typedef tuple<double, int, int> Edge; // cost, from, to

class Assignment {
  vector<Junction> junctions;
  vector<int> circuits; // at index i, it holds the index of the circuit of the junction at index i.
public:

  double euclideanDistance(int i, int j) {
    return sqrt(
        pow(get<0>(junctions[i]) - get<0>(junctions[j]), 2) +
        pow(get<1>(junctions[i]) - get<1>(junctions[j]), 2) +
        pow(get<2>(junctions[i]) - get<2>(junctions[j]), 2));
  }

  int solution() {
    junctions.clear();
    circuits.clear();
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;
      int x, y, z;
      sscanf(line.c_str(), "%d,%d,%d", &x, &y, &z);
      junctions.push_back(make_tuple(x, y, z));
    }
    priority_queue<Edge, vector<Edge>, greater<>> q;
    for (int i = 0;i<junctions.size();i++) {
      for (int j = i+1;j<junctions.size();j++) {
        if (i == j) continue;
        q.push(make_tuple(
            euclideanDistance(i, j),
            i,
            j));
      }
    }
    circuits = vector<int>(junctions.size());
    for (int i = 0;i<circuits.size();i++) {
      circuits[i] = i;
    }
    int lastI = 0;
    int lastJ = 0;
    while (!q.empty()) {
      Edge e = q.top();
      q.pop();
      int from = get<1>(e);
      int to = get<2>(e);
      if (circuits[from] != circuits[to]) {
        int oldCircuit = circuits[to];
        int newCircuit = circuits[from];
        for (int i = 0;i<circuits.size();i++) {
          if (circuits[i] == oldCircuit) {
            circuits[i] = newCircuit;
          }
        }
        lastI = from;
        lastJ = to;
      }
    }
    return get<0>(junctions[lastI]) * get<0>(junctions[lastJ]);
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
