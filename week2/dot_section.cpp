/*
 * Author: vpetrigo
 * Task:
 * Задача на программирование: покрыть отрезки точками
 * По данным n отрезкам необходимо найти множество точек минимального размера, для которого каждый из отрезков содержит
 * хотя бы одну из точек.
 * В первой строке дано число 1≤n≤100 отрезков. Каждая из последующих n строк содержит по два числа 0≤l≤r≤109,
 * задающих начало и конец отрезка. Выведите оптимальное число m точек и сами m точек. Если таких множеств точек
 * несколько, выведите любое из них.
 * Sample Input 1:
 * 3
 * 1 3
 * 2 5
 * 3 6
 *
 * Sample Output 1:
 * 1
 * 3
 *
 * Sample Input 2:
 * 4
 * 4 7
 * 1 3
 * 2 5
 * 5 6
 * Sample Output 2:
 * 2
 * 3 6
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <Prints.hpp>

using namespace std;

void fill_section(vector<pair<int, int>>& v, const int n) {
  for(int i = 0; i < n; ++i) {
    int l, r;

    cin >> l >> r;
    v.push_back(make_pair(l, r));
  }
}

bool section_cmp(pair<int, int> a, pair<int, int> b) {
  return a.second < b.second;
}

vector<int> dots_cover(vector<pair<int, int>> &v) {
  sort(v.begin(), v.end(), section_cmp);
  vector<int> dots;
  int i = 0;
  int r = v[i].second;

  dots.push_back(r);

  while (++i < v.size()) {
    if (!(r >= v[i].first && r <= v[i].second)) {
      r = v[i].second;
      dots.push_back(r);
    }
  }

  return dots;
}

int main() {
  vector<pair<int, int>> v;
  int n;

  cin >> n;
  fill_section(v, n);
  auto sol = dots_cover(v);
  cout << sol.size() << endl;
  print_cont(sol);

  return 0;
}