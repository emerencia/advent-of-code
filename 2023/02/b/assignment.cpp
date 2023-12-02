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
  static int minReds;
  static int minGreens;
  static int minBlues;

  static void registerColor(const string& color, int number) {
    if (color == "red") {
      minReds = max(minReds, number);
    } else if (color == "green") {
      minGreens = max(minGreens, number);
    } else if (color == "blue") {
      minBlues = max(minBlues, number);
    }
  }

  static void registerPull(string pull) {
    while (pull.find(';') != string:: npos || !pull.empty()) {
      int pull_end = (int)pull.find(',');
      string colorPull;
      if (pull_end != string::npos) {
        colorPull = pull.substr(0, pull_end);
      } else {
        colorPull = pull;
      }
      int number;
      string color;
      stringstream ss(colorPull);
      ss >> number >> color;
      registerColor(color, number);
      if (pull.find(',') != string::npos) {
        pull = pull.substr(pull.find(',') + 2);
      } else {
        pull = "";
      }
    }
  }

  static void registerGame(string game) {
    while (game.find(';') != string::npos || !game.empty()) {
      int set_end = (int)game.find(';');
      string pull;
      if (set_end != string::npos) {
        pull = game.substr(0, set_end);
      } else {
        pull = game;
      }
      registerPull(pull);
      if (game.find(';') != string::npos) {
        game = game.substr(game.find(';') + 2);
      } else {
        game = "";
      }
    }
  }

  static int solution() {
    int result = 0;
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      // Example line: Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
      int game_end = (int)line.find(':');
      // The remaining text is the game string
      string game = line.substr(game_end + 2);
      minGreens = 0; minReds = 0; minBlues = 0;
      registerGame(game);
      result += minReds * minGreens * minBlues;
    }
    return result;
  }
};

int Assignment::minReds = 0;
int Assignment::minGreens = 0;
int Assignment::minBlues = 0;

int main() {
  cout << Assignment::solution() << endl;
}
