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

template <typename Cont>
Cont lis_bottom_up(const Cont& numbers) {
  const auto len = numbers.size();
  vector<int> sequences(len + 1, inf_max);
  sequences.front() = inf_min;
  vector<int> positions(len + 1, no_prev);
  vector<int> prev_ind(len, no_prev);
  int max_seq_len = 0;

  for (auto i = 0; i < len; ++i) {
    int j = distance(sequences.begin(), upper_bound(sequences.begin(), sequences.end(), numbers[i]));

    if (sequences[j - 1] <= numbers[i] && numbers[i] < sequences[j]) {
      sequences[j] = numbers[i];
      positions[j] = i;
      prev_ind[i] = positions[j - 1];
      max_seq_len = max(max_seq_len, j);
    }
  }

  vector<int> answer;
  vector<int> ans_ind;
  auto k = positions[max_seq_len];

  while (k != no_prev) {
    answer.push_back(numbers[k]);
    ans_ind.push_back(len - k);
    k = prev_ind[k];
  }

  return ans_ind;
}

int main() {
  int n;

  cin >> n;

  auto numbers = fill_cont(n);
  reverse(numbers.begin(), numbers.end());
  auto res = lis_bottom_up(numbers);

  cout << res.size() << endl;
  for (auto& elem : res) {
    cout << elem << ' ';
  }
  cout << endl;

  return 0;
}
