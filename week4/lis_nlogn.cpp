/*
 * Author: vpetrigo
 * Task:
 * Дано целое число 1≤n≤10^5и массив A[1…n], содержащий неотрицательные целые числа, не превосходящие 10^9. Найдите
 * наибольшую невозрастающую подпоследовательность в A. В первой строке выведите её длину k, во второй — её индексы
 * 1≤i1<i2<…<ik≤n (таким образом, A[i1]≥A[i2]≥…≥A[in]).
 * Sample Input:
 * 5
 * 5 3 4 4 2
 * Sample Output:
 * 4
 * 1 3 4 5
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include "Prints.hpp"

using namespace std;

constexpr auto inf_min = numeric_limits<int>::min();
constexpr auto inf_max = numeric_limits<int>::max();
constexpr int no_prev = -1;

vector<int> fill_cont(const int n) {
  vector<int> v(n);

  for (auto& number : v) {
    cin >> number;
  }

  return v;
}

vector<int> build_answer(vector<int>& prevs) {
  const auto len = prevs.size();
  vector<int> res(len, no_prev);

  for (auto i = 0; i < len && prevs[i] != no_prev; ++i) {
    res[i] = len - prevs[i];
  }

  res.erase(remove(res.begin(), res.end(), no_prev), res.end());
  reverse(res.begin(), res.end());

  return res;
}

/*template <typename Cont>
Cont lis_bottom_up(const Cont& numbers) {
  const auto len = numbers.size();
  vector<int> d(len + 1);
  vector<int> prev(len, no_prev);
  d.front() = inf_min;
  fill(d.begin() + 1, d.end(), inf_max);

  for (auto i = 0; i < len; ++i) {
    auto j = distance(d.begin(), upper_bound(d.begin(), d.end(), numbers[i]));

    if (numbers[i] ) {
      if (d[j - 1] <= numbers[i] && numbers[i] < d[j]) {
        d[j] = numbers[i];
        prev[j - 1] = i;
      }
    }
//    }
  }

  auto res = build_answer(prev);

  return res;
}*/

template <typename Cont>
Cont lis_bottom_up(const Cont& numbers) {
  const auto len = numbers.size();
  vector<int> d(len + 1);
  vector<int> prev(len, no_prev);
  fill(d.begin(), d.end(), inf_min);
  d.back() = inf_max;
  cout << "D: ";
  print_cont(d.begin(), d.end());

  for (auto i = 0; i < len; ++i) {
    auto j = distance(d.begin(), upper_bound(d.begin(), d.end(), numbers[i], less_equal<int>{}));
    cout << "NUMBER: " << numbers[i] << endl;
    cout << "j: " << j << endl;
      if (d[j - 1] < numbers[i] && numbers[i] <= d[j]) {
        d[j - 1] = numbers[i];
        prev[j - 1] = i;
      }
    cout << "D: ";
    print_cont(d.begin(), d.end());
//    }
  }

  auto res = build_answer(prev);

  return res;
}

int main() {
  int n;

  cin >> n;

  auto numbers = fill_cont(n);
//  reverse(numbers.begin(), numbers.end());
  auto res = lis_bottom_up(numbers);

  cout << res.size() << endl;
  for (auto& elem : res) {
    cout << elem << ' ';
  }
  cout << endl;

  return 0;
}
