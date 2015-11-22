/*
 * Author: vpetrigo
 * Task:
 * В первой строке задано два целых числа 1≤n≤50000 и 1≤m≤50000 — количество отрезков и точек на прямой, соответственно.
 * Следующие n строк содержат по два целых числа ai и bi (ai≤bi) — координаты концов отрезков. Последняя строка содержит
 * m целых чисел — координаты точек. Все координаты не превышают 108 по модулю. Точка считается принадлежащей отрезку,
 * если она находится внутри него или на границе. Для каждой точки в порядке появления во вводе выведите, скольким
 * отрезкам она принадлежит.
 *
 * Sample Input:
 * 2 3
 * 0 5
 * 7 10
 * 1 6 11
 * Sample Output:
 * 1 0 0
 */

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <Prints.hpp>

using namespace std;

constexpr int open = -1;

vector<pair<int, int>> fill_cont(const int n, const int m) {
  vector<pair<int, int>> v;
  long long el = 0;

  for (int i = 0; i < n; ++i) {
    int l, r;

    cin >> l >> r;
    v.push_back(make_pair(l, open));
    // use m as a "close" sign
    v.push_back(make_pair(r, m));
  }

  for (int j = 0; j < m; ++j) {
    int dot;

    cin >> dot;
    v.push_back(make_pair(dot, j));
  }

  return v;
}

template<typename CIt>
int get_it_value(CIt it) {
  return it->first;
}

// naive check (O(n^2))
vector<int> check_range(const vector<pair<int, int>> &arr, const int dot_num) {
  int elem;
  vector<int> res(dot_num);

  for (int i = 0; i < dot_num; ++i) {
    cin >> elem;

    for (auto &range : arr) {
      if (elem >= range.first && elem <= range.second) {
        ++res[i];
      }
    }
  }

  return res;
}

template<typename It>
void insertion_sort(It begin, It end) {
  for (auto iti = begin + 1; iti != end; ++iti) {
    auto itj = iti;
    while (itj != begin && *itj < *(itj - 1)) {
      swap(*itj, *(itj - 1));
      --itj;
    }
  }
}

template<typename It>
It random_delim(It begin, It end) {
  constexpr int zero = 0;
  static random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<int> dis(zero, distance(begin, end - 1));

  return begin + dis(gen);
}

template<typename It>
It partition(It begin, It end) {
  auto delim = begin;
  auto cur = begin;

  for (auto it = begin + 1; it != end; ++it) {
    if (*delim > *it) {
      ++cur;
      iter_swap(cur, it);
    }
  }

  iter_swap(delim, cur);

  return cur;
}

template<typename It>
void quick_sort(It begin, It end) {
  while (distance(begin, end) > 10) {
    auto r_delim = random_delim(begin, end);

    iter_swap(begin, r_delim);
    It mid = partition(begin, end);

    auto size_left = distance(begin, mid);
    auto size_right = distance(mid, end);

    if (size_left > size_right) {
      quick_sort(begin, mid);
      begin = mid + 1;
    }
    else {
      quick_sort(mid + 1, end);
      end = mid;
    }
  }
  insertion_sort(begin, end);
}

template<typename It>
It partition3(It begin, It end, It &gr_part) {
  auto delim = end - 1;
  auto cur_gr = end - 1;
  auto cur_i = begin;
  auto cur_less = begin;

  while (distance(cur_i, cur_gr) > 0) {
    if (*cur_i < *delim) {
      iter_swap(cur_i++, cur_less++);
    }
    else if (*cur_i == *delim) {
      iter_swap(cur_i, --cur_gr);
    }
    else {
      ++cur_i;
    }
  }

  auto middle = min(distance(cur_less, cur_gr), distance(cur_gr, delim) + 1);

  for (auto it = cur_less, sit = delim - middle + 1; it != cur_less + middle; ++it, ++sit) {
    iter_swap(it, sit);
  }

  auto offset = distance(cur_gr, delim);
  gr_part = cur_less + offset;

  return cur_less;
}

template<typename It>
void quick_sort3(It begin, It end) {
  while (distance(begin, end) > 1) {
    auto r_delim = random_delim(begin, end);
    It gr_part;

    iter_swap(r_delim, end - 1);

    It less_part = partition3(begin, end, gr_part);

    auto size_left = distance(begin, less_part);
    auto size_right = distance(gr_part, end);

    if (size_left > size_right) {
      quick_sort3(begin, less_part);
      begin = gr_part + 1;
    }
    else {
      quick_sort3(gr_part + 1, end);
      end = less_part;
    }
  }
}

vector<long long> dots_in_range(const vector<pair<int, int>> &arr, const int m) {
  vector<long long> res(m);
  auto opened = 0;

  for (auto &elem : arr) {
    if (elem.second == open) {
      ++opened;
    }
    else if (elem.second == m) {
      --opened;
    }
    else {
      res[elem.second] += opened;
    }
  }

  return res;
}

int main() {
  int n, m;

  cin >> n >> m;

  auto &&arr = fill_cont(n, m);
  quick_sort3(arr.begin(), arr.end());

  auto &&solution = dots_in_range(arr, m);

  print_cont(solution.begin(), solution.end());

  return 0;
}
