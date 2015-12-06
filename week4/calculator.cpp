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

using namespace std;

struct Calc {
  int num_of_op_td(int number);
  int num_of_op_bu(int number);

  static constexpr auto inf = numeric_limits<int>::max();

  // for using with the num_of_op_td function
  void print_counted() const;

  unordered_map<int, int> counted;

 private:
  void restore_answer(const vector<int>& amount_of_op);
};

int main() {
  int n;
  Calc c;

  cin >> n;
  cout << c.num_of_op_td(n) << endl;
  c.print_counted();
  cout << c.num_of_op_bu(n) << endl;

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

int Calc::num_of_op_bu(int number) {
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

  return 0;
}

void Calc::print_counted() const {
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

void Calc::restore_answer(const vector<int> &amount_of_op) {
  const auto length = amount_of_op.size();
  const auto last_elem = amount_of_op.back();
  vector<int> result(last_elem, 1);

  for (int i = length; i >= 1; --i) {
    if ()
  }
}
