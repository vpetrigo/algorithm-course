/*
 * Author: vpetrigo
 * Task:
 * Первая строка входа содержит целые числа 1≤W≤10^4 и 1≤n≤300 — вместимость рюкзака и число золотых слитков.
 * Следующая строка содержит n целых чисел 0≤w1,…,wn≤10^5, задающих веса слитков. Найдите максимальный вес золота,
 * который можно унести в рюкзаке.
 *
 * Sample Input:
 * 10 3
 * 1 4 8
 * Sample Output:
 * 9
 */

#include <iostream>
#include <vector>
#include <iterator>
#include <cassert>

using namespace std;

void fill_vector(vector<int>& weights) {
  istream_iterator<int> is{cin};
  istream_iterator<int> eos;

  weights.assign(is, eos);
}

int knapsack_bu(const vector<int>& weights, int W) {
  auto q_weights = weights.size() + 1;
  auto knapsack_cap = W + 1;
  vector<vector<int>> max_weight(q_weights);
  for (auto& elem : max_weight) {
    elem.resize(knapsack_cap);
  }

  for (auto i = 0; i < q_weights; ++i) {
    max_weight[i][0] = 0;
  }
  for (int j = 0; j < knapsack_cap; ++j) {
    max_weight[0][j] = 0;
  }

  for (int i = 1; i < q_weights; ++i) {
    for (int w = 1; w < knapsack_cap; ++w) {
      max_weight[i][w] = max_weight[i - 1][w];
      if (weights[i - 1] <= w) {
        auto weight_with_new_item = max_weight[i - 1][w - weights[i - 1]] + weights[i - 1];

        max_weight[i][w] = max(max_weight[i][w], weight_with_new_item);
      }
    }
  }

  return max_weight[q_weights - 1][knapsack_cap - 1];
}

int main() {
  int n, W;
  vector<int> weights;

  cin >> W >> n;
  weights.resize(n);
  fill_vector(weights);
  assert(n == weights.size());
  cout << knapsack_bu(weights, W);

  return 0;
}
