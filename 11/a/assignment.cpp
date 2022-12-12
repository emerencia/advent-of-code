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
  vector<int> startingItems;
  char operation;
  int operationNumber;
  int divisible;
  int trueIndex;
  int falseIndex;
  int inspectCount;

  static vector<Monkey *> instances;

  Monkey(vector<int> startingItems, char operation, int operationNumber, int divisible, int trueIndex, int falseIndex) :
      startingItems(startingItems), operation(operation), operationNumber(operationNumber), divisible(divisible),
      trueIndex(trueIndex), falseIndex(falseIndex) {
    inspectCount = 0;
    instances.push_back(this);
  }

  void printYoSelf() {
    cout << "  Starting items: ";
    for (int i = 0; i < startingItems.size(); i++) {
      cout << startingItems[i];
      if (i + 1 < startingItems.size()) {
        cout << ", ";
      }
    }
    cout << endl;
    cout << "  Operation: new = old " << operation << " " << operationNumber << endl;
    cout << "  Test: divisible by " << divisible << endl;
    cout << "    If true: throw to monkey " << trueIndex << endl;
    cout << "    If false: throw to monkey " << falseIndex << endl;
  }

  void doTurn() {
    while (startingItems.size() > 0) {
      int worry = startingItems[0];
      startingItems.erase(startingItems.begin());
      cout << "  Monkey inspects an item with a worry level of " << worry << "." << endl;
      inspectCount++;
      if (operation == '*') {
        worry *= (operationNumber == 0 ? worry : operationNumber);
        cout << "    Worry level is multiplied by " << operationNumber << "  to " << worry << "." << endl;
      } else {
        worry += (operationNumber == 0 ? worry : operationNumber);
        cout << "    Worry level increases by " << operationNumber << "  to " << worry << "." << endl;
      }
      worry /= 3;
      cout << "    Monkey gets bored with item. Worry level is divided by 3 to " << worry << "." << endl;
      if (worry % divisible == 0) {
        cout << "    Current worry level is divsible by " << divisible << "." << endl;
        cout << "    Item with worry level " << worry << " is thrown to monkey " << trueIndex << "." << endl;
        instances[trueIndex]->startingItems.push_back(worry);
      } else {
        cout << "    Current worry level is not divisible by " << divisible << "." << endl;
        cout << "    Item with worry level " << worry << " is thrown to monkey " << falseIndex << "." << endl;
        instances[falseIndex]->startingItems.push_back(worry);
      }
    }
  }

  static void printStatus() {
    for (int i = 0; i < instances.size(); i++) {
      cout << "Monkey " << i << ": ";
      for (int j = 0; j < instances[i]->startingItems.size(); j++) {
        cout << instances[i]->startingItems[j];
        if (j + 1 < instances[i]->startingItems.size()) {
          cout << ", ";
        }
      }
      cout << endl;
    }
  }

  static void doRound() {
    for (int i = 0; i < instances.size(); i++) {
      cout << "Monkey " << i << ":" << endl;
      instances[i]->doTurn();
    }
  }

  static vector<int> getInspectCounts() {
    vector<int> inspectCounts;
    for (int i = 0; i < instances.size(); i++) {
      cout << "Monkey " << i << " inspected items " << instances[i]->inspectCount << " times." << endl;
      inspectCounts.push_back(instances[i]->inspectCount);
    }
    return inspectCounts;
  }
};

vector<Monkey *> Monkey::instances;


class Assignment {
public:

  int solution() {
    vector<Monkey *> instances;
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      // line is Monkey operationNumber:
      getline(cin, line);
      string buffer = line.substr(18);
      stringstream items(buffer);
      int item;
      vector<int> startingItems;
      while (items >> item) {
        startingItems.push_back(item);
        if (items.peek() == ',') {
          items.ignore();
        }
      }

      // Operation: new = old * 19
      getline(cin, line);
      char operation;
      char operand[256];
      sscanf(line.c_str(), "  Operation: new = old %c %s", &operation, operand);
      int operationNumber;
      if (strcmp(operand, "old") != 0) {
        stringstream a(operand);
        a >> operationNumber;
      } else {
        operationNumber = 0;
      }

      // Test: divisible by 23
      getline(cin, line);
      int divisible;
      sscanf(line.c_str(), "  Test: divisible by %i", &divisible);

      //     If true: throw to monkey 2
      getline(cin, line);
      int trueIndex;
      sscanf(line.c_str(), "    If true: throw to monkey %i", &trueIndex);

      //     If false: throw to monkey 3
      getline(cin, line);
      int falseIndex;
      sscanf(line.c_str(), "    If false: throw to monkey %i", &falseIndex);

      new Monkey(startingItems, operation, operationNumber, divisible, trueIndex, falseIndex);
    }
    /*
    cout << " ------------------------------- " << endl;
    for (int i =0;i<Monkey::instances.size();i++) {
      cout << "Monkey " << i << ":" << endl;
      Monkey::instances[i]->printYoSelf();
    }
    */
    for (int i = 0; i < 20; i++) {
      Monkey::doRound();
    }
    cout << endl;
    // Monkey::printStatus();
    vector<int> inspectCounts = Monkey::getInspectCounts();
    cout << endl;
    sort(inspectCounts.begin(), inspectCounts.end(), greater<int>());

    return inspectCounts[0] * inspectCounts[1];
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
