/*
 * Author: vpetrigo
 * Task:
 * Задача на программирование: различные слагаемые
 * По данному числу 1≤n≤10^9 найдите максимальное число k, для которого n можно представить как сумму k различных
 * натуральных слагаемых. Выведите в первой строке число k, во второй — k слагаемых.
 * Sample Input 1:
 * 4
 * Sample Output 1:
 * 2
 * 1 3
 *
 * Sample Input 2:
 * 6
 * Sample Output 2:
 * 3
 * 1 2 3
 */

#include <iostream>
#include <vector>
#include <Prints.hpp>

using namespace std;

vector<int> calc_dif_components(const int n) {
  vector<int> v;
  int summand = 0;
  int cur = n;

  // greedy algorithm: while current remainder > next term (i + 1)
  // add to the result. Else the following sequence will decrease and
  // numbers will repeat
  while (cur - (summand + 1) > summand + 1) {
    ++summand;
    v.push_back(summand);
    cur -= summand;
  }
  // add the remainder to the result
  v.push_back(cur);

  return v;
}

int main() {
  int n;

  cin >> n;
  auto sol = calc_dif_components(n);
  cout << sol.size() << endl;
  print_cont(sol);

  return 0;
}