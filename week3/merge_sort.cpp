/*
 * Author: vpetrigo
 * Task:
 * Первая строка содержит число 1≤n≤10^5, вторая — массив A[1…n], содержащий натуральные числа, не превосходящие 10^9.
 * Необходимо посчитать число пар индексов 1≤i<j≤n, для которых A[i]>A[j]. (Такая пара элементов называется инверсией
 * массива. Количество инверсий в массиве является в некотором смысле его мерой неупорядоченности: например, в
 * упорядоченном по неубыванию массиве инверсий нет вообще, а в массиве, упорядоченном по убыванию, инверсию образуют
 * каждые два элемента.)
 *
 * Sample Input:
 * 5
 * 2 3 9 2 9
 * Sample Output:
 * 2
 */

#include <iostream>
#include <vector>
#include <iterator>
#include <Prints.hpp>

using namespace std;

template <typename Type>
vector<Type> fill_cont() {
  istream_iterator<Type> it{cin};
  istream_iterator<Type> eos;
  vector<Type> v{it, eos};

  return v;
}

template <typename It>
vector<typename It::value_type> merge(const It begin, const It mid, const It end, long long& inv) {
  vector<typename It::value_type> v;
  It first_arr{begin};
  It second_arr{mid};
  const It first_arr_end{mid};
  const It second_arr_end{end};

  while (first_arr != first_arr_end && second_arr != second_arr_end) {
    if (*first_arr <= *second_arr) {
      v.push_back(*first_arr++);
    }
    else {
      v.push_back(*second_arr++);
      inv += distance(first_arr, first_arr_end);
    }
  }

  v.insert(v.end(), first_arr, first_arr_end);
  v.insert(v.end(), second_arr, second_arr_end);

  return v;
}

template <typename It>
auto merge_sort(It begin, It end) -> long long {
  auto size = distance(begin, end);
  long long inv = 0;

  if (size > 1) {
    auto mid = next(begin, size / 2);

    inv += merge_sort(begin, mid);
    inv += merge_sort(mid, end);

    auto &&v = merge(begin, mid, end, inv);
    move(v.begin(), v.end(), begin);
  }

  return inv;
}

int main() {
  int n;

  cin >> n;
  auto v = fill_cont<int>();
  auto res = merge_sort(v.begin(), v.end());
  cout << res << endl;

  return 0;
}