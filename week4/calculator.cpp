/*
 * Author: vpetrigo
 * Task:
 * У вас есть примитивный калькулятор, который умеет выполнять всего три операции с текущим числом x: заменить x на 2x,
 * 3x или x+1. По данному целому числу 1≤n≤10^5 определите минимальное число операций k, необходимое, чтобы получить
 * n из 1. Выведите k и последовательность промежуточных чисел.
 * Sample Input 1:
 * 1
 * Sample Output 1:
 * 0
 * 1
 * Sample Input 2:
 * 5
 * Sample Output 2:
 * 3
 * 1 2 4 5
 *
 * Sample Input 3:
 * 96234
 * Sample Output 3:
 * 14
 * 1 3 9 10 11 22 66 198 594 1782 5346 16038 16039 32078 96234
 */

#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <limits>
#include <cassert>

using namespace std;

struct Calc {
  int num_of_op_td(int number);
  vector<int> num_of_op_bu(int number);

  static constexpr auto inf = numeric_limits<int>::max();

  // for using with the num_of_op_td function
  void print_counted() const;

  // storage for calculated values
  unordered_map<int, int> counted;

 private:
  vector<int> restore_answer(const vector<int>& amount_of_op) const;
};

int main() {
  int n;
  Calc c;

  cin >> n;
//  cout << c.num_of_op_td(n) << endl;
//  c.print_counted();
  auto result = c.num_of_op_bu(n);

  // size() - 1, because we do not have to count initial value 1
  cout << result.size() - 1 << endl;
  for (const auto& elem : result) {
    cout << elem << ' ';
  }
  cout << endl;

  return 0;
}

int Calc::num_of_op_td(int number) {
  if (counted.find(number) == counted.end()) {
    if (number == 1) {
      counted[number] = 0;
    }
    else {
      auto count = 0;
      auto divide_by_two = inf;
      auto divide_by_three = inf;

      if (number % 3 == 0) {
        divide_by_three = 1 + num_of_op_td(number / 3);
      }
      if (number % 2 == 0) {
        divide_by_two = 1 + num_of_op_td(number / 2);
      }
      count = 1 + num_of_op_td(number - 1);

      counted[number] = min({count, divide_by_two, divide_by_three});
    }
  }

  return counted[number];
}

vector<int> Calc::num_of_op_bu(int number) {
  const auto len = number + 1;
  constexpr auto inf = numeric_limits<int>::max();
  vector<int> amount_of_ops(len, 0);

  for (int i = 2; i < len; ++i) {
    auto addition = amount_of_ops[i - 1] + 1;
    auto mul_by_two = inf;
    auto mul_by_three = inf;

    if (i % 2 == 0) {
      mul_by_two = amount_of_ops[i / 2] + 1;
    }
    if (i % 3 == 0) {
      mul_by_three = amount_of_ops[i / 3] + 1;
    }

    amount_of_ops[i] = min({addition, mul_by_two, mul_by_three});
  }

  auto result = restore_answer(amount_of_ops);

  return result;
}

void Calc::print_counted() const {
  // check whether we use the Calc::num_of_op_td or not
  assert(counted.size() > 0);

  vector<pair<int, int>> sequence{counted.begin(), counted.end()};

  sort(sequence.begin(), sequence.end());

  auto back = sequence.back();
  int length = back.second;
  vector<int> result(length + 1, 1);

  while (back.second > 0) {
    result[length--] = back.first;
    back = *find_if(sequence.begin(), sequence.end(),
                    [length, back](const pair<int, int>& elem) { return elem.second == length &&
                        (back.first - 1 == elem.first
                            || back.first / 2 == elem.first
                            || back.first / 3 == elem.first); });
  }

  for (const auto& elem : result) {
    cout << elem << ' ';
  }
  cout << endl;
}

vector<int> Calc::restore_answer(const vector<int> &amount_of_op) const {
  auto length = amount_of_op.size() - 1;
  // number of operations (x + 1, 2 * x or 3 * x) to get to the number X
  auto ops = amount_of_op.back();
  vector<int> result(ops + 1, 1);


  while (length >= 1) {
    result[ops--] = length;
    // the distance from current number to another which could be 3 * (number / 3)
    auto divide_by_three = length / 3;
    // the distance from current number to another which could be 2 * (number / 2)
    auto divide_by_two = length / 2;

    if (length % 3 == 0 && amount_of_op[divide_by_three] == ops) {
      length = divide_by_three;
    }
    else if (length % 2 == 0  && amount_of_op[divide_by_two] == ops) {
      length = divide_by_two;
    }
    else {
      --length;
    }
  }

  return result;
}
