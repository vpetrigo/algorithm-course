/*
 * Author: vpetrigo
 * Task:
 * Дана число 1≤n≤102 ступенек лестницы и целые числа −104≤a1,…,an≤104, которыми помечены ступеньки. Найдите
 * максимальную сумму, которую можно получить, идя по лестнице снизу вверх (от нулевой до n-й ступеньки), каждый раз
 * поднимаясь на одну или две ступеньки.
 * Sample Input 1:
 * 2
 * 1 2
 * Sample Output 1:
 * 3
 *
 * Sample Input 2:
 * 2
 * 2 -1
 * Sample Output 2:
 * 1
 *
 * Sample Input 3:
 * 3
 * -1 2 1
 * Sample Output 3:
 * 3
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

struct Stair {
  int count_val_bu(const vector<int> &step_val);
  int count_val_bu_opt(const vector<int> &step_val);
  int count_val_td(const vector<int>& step_val, int step);

  unordered_map<int, int> counted_step;
};

int Stair::count_val_bu(const vector<int> &step_val) {
  const auto stair_len = step_val.size() + 1;
  vector<int> sum(stair_len);

  for (auto& elem : sum) {
    elem = 0;
  }

  sum[1] = step_val[0];

  for (int step = 2; step < stair_len; ++step) {
    sum[step] = step_val[step - 1] + max(sum[step - 1], sum[step - 2]);
  }

  return sum[stair_len - 1];
}

int Stair::count_val_bu_opt(const vector<int> &step_val) {
  const auto stair_len = step_val.size() + 1;

  auto prev = 0;
  auto cur = step_val[0];

  for (auto step = 2; step < stair_len; ++step) {
    auto new_cur = step_val[step - 1] + max(prev, cur);
    prev = cur;
    cur = new_cur;
  }

  return cur;
}

int Stair::count_val_td(const vector<int> &step_val, int step) {
  if (counted_step.find(step) == counted_step.end()) {
    if (step == 0) {
      counted_step[step] = 0;
    }
    else if (step == 1) {
      counted_step[step] = step_val[step - 1];
    }
    else {
      auto one_step = count_val_td(step_val, step - 1);
      auto two_step = count_val_td(step_val, step - 2);

      counted_step[step] = step_val[step - 1] + max(one_step, two_step);
    }
  }

  return counted_step[step];
}

int main() {
  vector<int> step_val;
  int n;
  Stair s;

  cin >> n;
  step_val.resize(n);

  for (auto& elem : step_val) {
    cin >> elem;
  }

  cout << s.count_val_td(step_val, n) << endl;
  cout << s.count_val_bu(step_val) << endl;
  cout << s.count_val_bu_opt(step_val) << endl;

  return 0;
}

