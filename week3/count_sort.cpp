/*
 * Author: vpetrigo
 * Task:
 * Первая строка содержит число 1≤n≤10^4, вторая — n натуральных чисел, не превышающих 10. Выведите упорядоченную по
 * неубыванию последовательность этих чисел.
 * Sample Input:
 * 5
 * 2 3 9 2 9
 * Sample Output:
 * 2 2 3 9 9
 */

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <numeric>
#include "Prints.hpp"

using namespace std;

template <typename Type>
vector<Type> fill_cont(const int n) {
  istream_iterator<Type> it{cin};
  istream_iterator<Type> eos;

  return vector<Type> {it, eos};
}

template <typename CIt>
vector<typename CIt::value_type> count_sort(CIt begin, CIt end) {
  auto max_value = *max_element(begin, end);
  auto size = distance(begin, end);
  vector<typename CIt::value_type> elem_cnt(max_value + 1);
  vector<typename CIt::value_type> result(size);

  for (auto cit = begin; cit != end; ++cit) {
    ++elem_cnt[*cit];
  }

  partial_sum(elem_cnt.begin(), elem_cnt.end(), elem_cnt.begin());

  for (auto i = 1; i <= size; ++i) {
    result[elem_cnt[*(end - i)] - 1] = *(end - i);
    --elem_cnt[*(end - i)];
  }

  return result;
}

int main() {
  int n;

  cin >> n;

  auto arr = fill_cont<int>(n);
  auto solution = count_sort(arr.cbegin(), arr.cend());
  print_cont(solution.begin(), solution.end());

  return 0;
}