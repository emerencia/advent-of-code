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
#include <cstdio>

using namespace std;
typedef long long LL;
typedef pair<int, int> PII;



class Assignment {
public:

  void stackMove(vector<vector<char> > &s, int nrBoxes, int from, int to) {
    for (int i = 0; i < nrBoxes; i++) {
      char box = s[from].back();
      s[from].pop_back();
      s[to].push_back(box);
    }
  }

  void printt(vector<vector<char> >& s) {
    for (int i = 0; i < s.size(); i++) {
      for (int j=0;j < s[i].size();j++) {
        cout << s[i][j];
      }
      cout << endl;
    }
  }

  string solution() {
    vector<vector<char> > s(9);
    int stage = 1;
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) {
        stage = 2;
        continue;
      }
      if (stage == 1) {
        if (line[1] == '1') continue;
        for (int i =1;i < line.size();i+=4) {
          if (line[i] != ' ') {
            s[(i - 1)/ 4].insert(s[(i - 1)/4].begin(), line[i]);
          }
        }
      } else {
        int nrBoxes, from, to;
        sscanf(line.c_str(), "move %d from %d to %d", &nrBoxes, &from, &to);
        stackMove(s,nrBoxes,from - 1, to - 1);
      }
    }
    string result;
    for (int i = 0;i<s.size(); i++) {
      if (!s[i].empty()) {
        result += s[i].back();
      }
    }
    return result;
  };
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
