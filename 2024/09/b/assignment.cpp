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

struct Node {
  int id; // -1 for empty
  int len;
  bool moved;
  Node *prev;
  Node *next;

  Node(const int id, const int len, Node *prev, Node *next) : id(id), len(len), prev(prev), next(next) {
    moved = false;
  }

  void removeMe() {
    id = -1;
  }

  // returns the remaining length
  int fillIn(const int oid, const int olen) {
    if (id != -1) {
      cout << "ERROR: fillIn called on a non-empty block" << endl;
      exit(1);
    }
    if (len <= olen) {
      id = oid;
      return olen - len;
    }
    const int remainingLen = len - olen;
    id = oid;
    moved = true;
    len = olen;
    const auto newNode = new Node(-1, remainingLen, this, next);
    if (next != nullptr) {
      next->prev = newNode;
    }
    next = newNode;
    return 0;
  }
};

class Assignment {
public:
  Node *head;
  Node *tail;

  void compactFiles() const {
    Node *right = tail;
    while (right != nullptr && head != right) {
      Node *left = head;
      // downgrade right until we find a block
      if (right->id == -1 || right->moved) {
        right = right->prev;
        continue;
      }
      if (left == right) {
        right = right->prev;
        continue;
      }
      // progress left until we find empty space
      while (left != nullptr && left->next != right && (left->id != -1 || left->len < right->len)) {
        left = left->next;
      }
      if (left == nullptr || left->id != -1 || left->len < right->len) {
        // cout << "Cannot move block " << right->id << " " << right->len << endl;
        right = right->prev;
        continue;
      }

      // if we can fit all the block into the empty space
      left->fillIn(right->id, right->len);
      right->removeMe();
    }
  }

  LL calculateChecksum() const {
    const Node *cur = head;
    LL result = 0;
    int pos = 0;
    while (cur != nullptr) {
      for (int i = 0; i < cur->len; ++i) {
        if (cur->id != -1) {
          result += cur->id * pos;
        }
        pos++;
      }
      cur = cur->next;
    }
    return result;
  }

  LL solution() {
    head = nullptr;
    tail = nullptr;
    LL result = 0;
    while (cin.good()) {
      string line;
      getline(cin, line);
      if (line.empty()) continue;

      Node *prev = nullptr;
      for (int i = 0; i < line.size(); ++i) {
        Node *cur = nullptr;
        if (line[i] == '0') continue;
        if (i % 2 == 0) {
          // adding a block
          cur = new Node(i / 2, line[i] - '0', prev, nullptr);
        } else {
          // adding empty space
          cur = new Node(-1, line[i] - '0', prev, nullptr);
        }
        if (prev == nullptr) {
          head = cur;
        } else {
          prev->next = cur;
        }
        prev = cur;
      }
      tail = prev;
    }
    compactFiles();
    result = calculateChecksum();
    // free memory allocated by the nodes because why not
    const Node *cur = head;
    while (cur != nullptr) {
      const Node *next = cur->next;
      delete cur;
      cur = next;
    }
    return result;
  }
};

int main() {
  Assignment obj;
  cout << obj.solution() << endl;
}
