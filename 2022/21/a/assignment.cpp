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
        if (operation.size() != 1) {
          cout << "ERROR: operation size is not 1: " << operation << endl;
        }
        if (name.size() != 5 || name[4] != ':') {
          cout << "ERROR: name is not valid: " << name << endl;
        }
        new Monkey(name.substr(0, 4), first_operand, operation[0], second_operand);
      } else {
        // read a number monkey
        string name;
        int number;
        stringstream(line) >> name >> number;
        if (name.size() != 5 || name[4] != ':') {
          cout << "ERROR: name is not valid: " << name << endl;
        }
        new Monkey(name.substr(0, 4), number);
      }
    }
    return Monkey::lookup["root"]->value();
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
