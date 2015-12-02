/*
 * Author: vpetrigo
 * Task:
 * В первой строке даны целое число 1≤n≤10^5 и массив A[1…n] из n различных натуральных чисел, не превышающих 10^9, в
 * порядке возрастания, во второй — целое число 1≤k≤105 и k натуральных чисел b1,…,bk, не превышающих 109. Для каждого
 * i от 1 до k необходимо вывести индекс 1≤j≤n, для которого A[j]=bi, или −1, если такого j нет.
 *
 * Sample Input:
 * 5 1 5 8 12 13
 * 5 8 1 23 1 11
 * Sample Output:
 * 3 1 -1 1 -1
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <Prints.hpp>

using namespace std;

vector<int> fill_cont(int n) {
  vector<int> cont(n);

  for (int i = 0; i < n; ++i) {
    int elem;

    cin >> elem;
    cont[i] = elem;
  }

  return cont;
}

template <typename Cont>
//  requires Container<Cont>()
int binary_search(const Cont& arr, const int k) {
  int l = 0;
  int r = arr.size() - 1;

  while (l <= r) {
    auto m = l + (r - l) / 2;

    if (arr[m] == k) {
      // add 1, because numeration is from 0
      return m + 1;
    }
    else if (arr[m] > k) {
      r = m - 1;
    }
    else {
      l = m + 1;
    }
  }

  return -1;
}

template <typename Cont>
//  requires Container<Cont>()
Cont lookup_for_elem(const Cont& origin, const Cont& search_for) {
  Cont res;
  for (const auto& i : search_for) {
    res.push_back(binary_search(origin, i));
  }

  return res;
}

int main() {
  int n, m;

  cin >> n;

  auto array = fill_cont(n);

  cin >> m;

  auto search_for = fill_cont(m);
  auto solution = lookup_for_elem(array, search_for);

  print_cont(solution.begin(), solution.end());

  return 0;
}

