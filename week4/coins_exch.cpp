/*
 * Author: vpetrigo
 * Task:
 * Приведите алгоритм, который по данному натуральному числу n и набору натуральных чисел C={c1=1,c2,…,ck} находит
 * минимальное число p, такое что n можно представить как сумму p чисел из набора C, за время O(kn) (числа в представлении
 * могут повторяться; хотя бы одно представление всегда есть, поскольку c1=1).
 */

#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <cassert>

using namespace std;

struct Coins {
  int coins_exchange_rec(const vector<int>& coins_val, int n);
  vector<int> coins_exchange_bu(const vector<int>& coins_val, int sum);

  unordered_map<int, int> coin_change;
};

int Coins::coins_exchange_rec(const vector<int>& coins_val, int n) {
  assert(n >= 0);
  if (coin_change.find(n) == coin_change.end()) {
    auto count = n;

    for (const auto& coin : coins_val) {
      if (coin <= n) {
        count = min(count, 1 + coins_exchange_rec(coins_val, n - coin));
      }
    }

    coin_change[n] = count;
  }

  return coin_change[n];
}

vector<int> Coins::coins_exchange_bu(const vector<int> &coins_val, int sum) {
  const auto exchange_len = sum + 1;
  vector<int> coin_amount(exchange_len);

  for (int i = 0; i < exchange_len; ++i) {
    coin_amount[i] = i;
  }

  for (int amount = 0; amount < exchange_len; ++amount) {
    for (const auto coin : coins_val) {
      if (coin <= amount) {
        coin_amount[amount] = min(coin_amount[amount], 1 + coin_amount[amount - coin]);
      }
    }
  }

  vector<int> coins;
  int c_amount = coin_amount[sum] - 1;
  int value = 1;

  for (int i = exchange_len - 2; i >= 0; --i) {
    if (c_amount == coin_amount[i] && find(coins_val.begin(), coins_val.end(), value) != coins_val.end()) {
      --c_amount;
      coins.push_back(value);
      value = 1;
    }
    else {
      ++value;
    }
  }

  return coins;
}

int main() {
  int sum, currency_size;
  vector<int> coins_val;
  Coins result;

  cin >> sum >> currency_size;
  coins_val.resize(currency_size);

  for (auto& elem : coins_val) {
    cin >> elem;
  }

  auto exch = result.coins_exchange_bu(coins_val, sum);

  cout << result.coins_exchange_rec(coins_val, sum) << endl;
  cout << exch.size() << endl;

  return 0;
}
