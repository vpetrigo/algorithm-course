/*
 * Author: vpetrigo
 * Task:
 * Задача на программирование: непрерывный рюкзак
 * Первая строка содержит количество предметов 1≤n≤10^3 и вместимость рюкзака 0≤W≤2⋅10^6. Каждая из следующих n строк
 * задаёт стоимость 0≤ci≤2⋅10^6 и объём 0<wi≤2⋅10^6 предмета (n, W, ci, wi — целые числа). Выведите максимальную
 * стоимость частей предметов (от каждого предмета можно отделить любую часть, стоимость и объём при этом
 * пропорционально уменьшатся), помещающихся в данный рюкзак, с точностью не менее трёх знаков после запятой.
 * Sample Input:
 * 3 50
 * 60 20
 * 100 50
 * 120 30
 * Sample Output:
 * 180.000
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

void fill_section(vector<pair<double, double>>& v, const int n) {
  for(int i = 0; i < n; ++i) {
    double l, r;

    cin >> l >> r;
    v.push_back(make_pair(l, r));
  }
}

bool weight_cmp(const pair<double, double>& a, const pair<double, double>& b) {
  return (a.first / a.second) > (b.first / b.second);
}

double calc_cost(const pair<double, double>& c_w) {
  return c_w.first / c_w.second;
}

double fill_knapsack(vector<pair<double, double>>& kn, int w) {
  double sum_cost = 0;
  sort(kn.begin(), kn.end(), weight_cmp);

  for (int i = 0; i < kn.size() && w > 0; ++i) {
    auto item_weight = kn[i].second;
    auto item_cost = kn[i].first;

    if (w >= item_weight) {
      sum_cost += item_cost;
      w -= item_weight;
    }
    else {
      sum_cost += calc_cost(kn[i]) * w;
      w = 0;
    }
  }

  return sum_cost;
}

int main() {
  int n, w;
  vector<pair<double, double>> v;

  cin >> n >> w;
  fill_section(v, n);
  auto sum = fill_knapsack(v, w);
  cout << fixed << setprecision(3) << sum;

  return 0;
}
