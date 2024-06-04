#ifndef POLAND_H
#define POLAND_H

#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Stack {
  double num;
  char c;
  Stack* next;
};

void push(double n, char c, Stack*& top) { top = new Stack{n, c, top}; }

void pop(Stack*& top) {
  Stack* t = top;
  top = top->next;
  delete (t);
}

int pr(char c) {
  if (c == '(') {
    return 0;
  } else if (c == '+' || c == '-') {
    return 1;
  } else if (c == '/' || c == '*') {
    return 2;
  } else {
    return 3;
  }
}

bool gcheck(Stack*& top) { return (top != nullptr); }

bool apply(Stack*& top1, Stack*& top2) {
  char t = 'a';
  double a = 0, b = 0;
  if (gcheck(top1)) {
    b = top1->num;
    pop(top1);
  } else {
    return false;
  }
  if (gcheck(top1)) {
    a = top1->num;
    pop(top1);
  } else {
    return false;
  }
  if (gcheck(top2)) {
    t = top2->c;
    pop(top2);
  } else {
    return false;
  }
  if (t == '+') {
    push(a + b, '@', top1);
  } else if (t == '-') {
    push(a - b, '@', top1);
  } else if (t == '*') {
    push(a * b, '@', top1);
  } else if (t == '/') {
    if (b == 0) {
      return false;
    }
    push(a / b, '@', top1);
  } else {
    push(pow(a, b), '@', top1);
  }
  return true;
}

bool applybr(Stack*& top1, int st) {
  double a = 0;
  if (gcheck(top1)) {
    a = top1->num;
    pop(top1);
  } else {
    return false;
  }
  if (st == 0) {
    push(a, '@', top1);
  } else if (st == 1) {
    push(sin(a), '@', top1);
  } else if (st == 2) {
    push(cos(a), '@', top1);
  } else if (st == 3) {
    int h = int(a) % 90, k = int(a) / 90;
    if (h == 0 && k * 90 == a && k % 2 == 1) {
      return false;
    }
    push(tan(a), '@', top1);
  } else if (st == 4) {
    if (a < 0) {
      return false;
    }
    push(sqrt(a), '@', top1);
  } else if (st == 6){
    push(abs(a), '@', top1);
  } else {
    if (a <= 0) {
      return false;
    }
    push(log(a), '@', top1);
  }
  return true;
}


bool calculate (string s, double& res){
  string ns = "", t = "", u = "";
  bool check = false;
  int st = 0;
  cout << s << '\n';
  for (int i = 0; i < int(s.size()); ++i) {
    if (i > 0 && s[i] == ')' && s[i - 1] == '(') {
      return false;
    }
    if (s[i] != ' ') {
      u += s[i];
    }
  }
  cout << u << '\n';

  for (int i = 0; i < int(u.size()); ++i) {
    if (u[i] >= 'a' && u[i] <= 'z') {
      if (u[i] == 'l') {
        if (i <= int(u.size()) - 2 && u[i + 1] == 'n') {
          ++i;
          continue;
        } else {
          return 0;
        }
      } else if (u[i] == 's') {
        if (i <= int(u.size() - 3) && u[i + 1] == 'i' && u[i + 2] == 'n') {
          i += 2;
          continue;
        } else if (i <= int(u.size() - 4) && u[i + 1] == 'q' &&
                   u[i + 2] == 'r' && u[i + 3] == 't') {
          i += 3;
          continue;
        } else {
          return 0;
        }
      } else if (u[i] == 'c') {
        if (i <= int(u.size() - 3) && u[i + 1] == 'o' && u[i + 2] == 's') {
          i += 2;
          continue;
        } else {
          return 0;
        }
      } else if (u[i] == 't') {
        if (i <= int(u.size()) - 2 && u[i + 1] == 'g') {
          ++i;
          continue;
        } else {
          return 0;
        }
      } else if (u[i] == 'a'){
        if (i <= int(u.size() - 3) && u[i + 1] == 'b' && u[i + 2] == 's'){
          i+=2;
          continue;
        } else {
            return 0;
        }
      } else {
        return 0;
      }
    }
  }
  cout << u << '\n';

  s = u;
  cout << s << '\n';
  u = "";

  for (int i = 0; i < int(s.size()); ++i) {
    if (s[i] == '-' && (i == 0 || (s[i - 1] == '('))) {
      ns += "0-";
    } else {
      ns += s[i];
    }
  }
  cout << ns << '\n';

  vector<int> ch(ns.size(), -1);

  for (int i = 0; i < int(ns.size()); ++i) {
    if (ns[i] >= 'a' && ns[i] <= 'z') {
      if (st != 0) {
        continue;
      }
      if (ns[i] == 'c') {
        st = 2;
      } else if (ns[i] == 't') {
        st = 3;
      } else if (ns[i] == 'l') {
        st = 5;
      } else if (ns[i] == 'a'){
        st = 6;
      } else if (ns[i] == 's') {
        if (ns[i + 1] == 'i') {
          st = 1;
        }
        if (ns[i + 1] == 'q') {
          st = 4;
        }
      }
    } else if (ns[i] == '(') {
      ch[i] = st;
      st = 0;
    }
  }
  cout << ns << '\n';
  Stack* top1 = nullptr;
  Stack* top2 = nullptr;
  for (int i = 0; i < int(ns.size()); ++i) {
    if (ns[i] >= 'a' && ns[i] <= 'z') {
      continue;
    }

    if (ns[i] >= '0' && ns[i] <= '9') {
      t += ns[i];
    } else if (ns[i] == '.'){
      t += ns[i];
    } else if (ns[i] == '(') {
      if (t != "") {
        push(stod(t), '@', top1);
        t = "";
      }
      push(ch[i], ns[i], top2);
    } else if (ns[i] == ')') {
      if (t != "") {
        push(stod(t), '@', top1);
        t = "";
      }
      while (top2 != nullptr && top2->c != '(') {
        int g = apply(top1, top2);
        if (!g) {
          check = true;
          break;
        }
      }
      if (gcheck(top2)) {
        int g = applybr(top1, top2->num);
        if (!g) {
          check = true;
        }
        pop(top2);
      } else {
        check = true;
      }
    } else {
      if (t != "") {
        push(stod(t), '@', top1);
        t = "";
      }
      int p = pr(ns[i]);
      while (top2 != nullptr && p <= pr(top2->c)) {
        int g = apply(top1, top2);
        if (!g) {
          check = true;
          break;
        }
      }
      push(0.0, ns[i], top2);
    }

    if (check) {
      break;
    }
  }

  if (t != "") {
    push(stod(t), '@', top1);
    t = "";
  }

  while (top2 != nullptr) {
    int g = apply(top1, top2);
    if (!g) {
      check = true;
      break;
    }
  }

  if (top1 == nullptr || check) {
    return 0;
  }
  res = top1->num;
  return true;
}

#endif // POLAND_H
