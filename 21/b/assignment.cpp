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

struct Monkey {
  LL number;
  string name;
  char operation;
  string first_operand;
  string second_operand;

  static vector<Monkey *> instances;
  static map<string, Monkey *> lookup;

  Monkey(string name, int number) : number(number), name(name), operation(' ') {
    instances.push_back(this);
    lookup[name] = this;
  }

  Monkey(string name, string first_operand, char operation, string second_operand) :
      number(-1), name(name), operation(operation), first_operand(first_operand), second_operand(second_operand) {
    instances.push_back(this);
    lookup[name] = this;
  }

  LL value() {
    if (number != -1) return number;
    switch (operation) {
      case '+': return number = lookup[first_operand]->value() + lookup[second_operand]->value();
      case '-': return number = lookup[first_operand]->value() - lookup[second_operand]->value();
      case '*': return number = lookup[first_operand]->value() * lookup[second_operand]->value();
      case '/': return number = lookup[first_operand]->value() / lookup[second_operand]->value();
    }
    cout << "ERROR: should never come here" << endl;
    return 0;
  }

  static void reset() {
    for (int i = 0; i < instances.size(); i++) {
      Monkey *monkey = instances[i];
      if (monkey->operation != ' ') {
        monkey->number = -1;
      }
    }
  }
};

vector<Monkey *> Monkey::instances;
map<string, Monkey *> Monkey::lookup;

class Assignment {
public:

  LL solution() {
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      if (line.size() > 10) {
        // read an operation monkey
        string name, first_operand, operation, second_operand;
        stringstream(line) >> name >> first_operand >> operation >> second_operand;
        new Monkey(name.substr(0, 4), first_operand, operation[0], second_operand);
      } else {
        // read a number monkey
        string name;
        int number;
        stringstream(line) >> name >> number;
        new Monkey(name.substr(0, 4), number);
      }
    }
    Monkey *left_operand = Monkey::lookup[Monkey::lookup["root"]->first_operand];
    Monkey *right_operand = Monkey::lookup[Monkey::lookup["root"]->second_operand];
    Monkey *human = Monkey::lookup["humn"];

    // After some testing, I found that only the left side of the
    // equation changes when changing the human number. So we only
    // calculate the right side once. Furthermore, the value of the
    // left side decreases when we increase the human number.
    // Binary search finds the answer.

    LL right_side = right_operand->value();
    LL left = 1;
    // After some testing I found that the left side decreased by about 46 when
    // decreasing the human value by 10. I used this to find an initial
    // upper bound that was sure to be too large, but not large enough
    // that it would cause calculations to go over the long long max limit.
    LL right = 17910080836216;
    while (right - left > 1) {
      LL pivot = (left + right) / 2;
      Monkey::reset();
      human->number = pivot;
      LL value = left_operand->value();
      if (value > right_side) {
        left = pivot + 1;
      } else {
        right = pivot;
      }
    }
    return left;
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
