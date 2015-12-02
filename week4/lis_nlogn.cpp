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

vector<int> fill_cont(const int n) {
  vector<int> v(n);

  for (auto& number : v) {
    cin >> number;
  }

  return v;
}

template <typename Cont>
Cont lis_bottom_up(const Cont& numbers) {
  constexpr int no_prev = -1;
  const auto len = numbers.size();
  vector<int> d(len);
  vector<int> prev(len, no_prev);
  d.front() = numeric_limits<int>::min();
  fill(d.begin() + 1, d.end(), numeric_limits<int>::max());

  for (auto i = 0; i < len; ++i) {
    auto j = distance(d.begin(), upper_bound(d.begin(), d.end(), numbers[i]));

    if (d[j - 1] < numbers[i] && numbers[i] < d[j]) {
      d[j] = numbers[i];
      prev[j] = i;
    }
  }

  print_cont(prev.begin(), prev.end());
  return d;
}

int main() {
  int n;

  cin >> n;

  auto numbers = fill_cont(n);
  auto res = lis_bottom_up(numbers);

  print_cont(res.begin(), res.end());

  return 0;
}
