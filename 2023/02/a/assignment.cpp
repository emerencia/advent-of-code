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

  static bool colorPossible(string color, int number) {
    if (color == "red") return number <= 12;
    if (color == "green") return number <= 13;
    if (color == "blue") return number <= 14;
    return false;
  }

  static bool pullPossible(string pull) {
    bool allPossible = true;
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
      if (!colorPossible(color, number)) {
        allPossible = false;
        break;
      }
      if (pull.find(',') != string::npos) {
        pull = pull.substr(pull.find(',') + 2);
      } else {
        pull = "";
      }
    }
    return allPossible;
  }

  static bool gamePossible(string game) {
    bool allPossible = true;
    while (game.find(';') != string::npos || !game.empty()) {
      int set_end = (int)game.find(';');
      string pull;
      if (set_end != string::npos) {
        pull = game.substr(0, set_end);
      } else {
        pull = game;
      }

      // Split the set by comma
      if (!pullPossible(pull)) {
        allPossible = false;
        break;
      }

      if (game.find(';') != string::npos) {
        game = game.substr(game.find(';') + 2);
      } else {
        game = "";
      }
    }
    return allPossible;
  }

  static int solution() {
    int result = 0;
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      // Example line: Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
      // First determine the game number
      int game_start = (int)line.find("Game ");
      int game_end = (int)line.find(':');
      int game_number = stoi(line.substr(game_start + 5, game_end - game_start - 5));

      // Split the remaining text by semicolon
      string game = line.substr(game_end + 2);
      if (gamePossible(game)) {
        result += game_number;
      }
    }
    return result;
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
