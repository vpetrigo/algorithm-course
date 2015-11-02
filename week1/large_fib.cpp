/*
 * Author: vpetrigo
 * Task:
 * Find the remainder of n-th Fibonacci number by m number
 * Input:
 * 47905881698199969 76940
 * Output:
 * 13794
 */

#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

constexpr int f_1 = 0;
constexpr int f_2 = 1;

void print_vector(const vector<int>& v) {
  ostream_iterator<int> os{cout, " "};
  copy(v.begin(), v.end(), os);
  cout << endl;
}

int large_fib_rem(int n, int m) {
  vector<int> fib_num (2 * m + 1);
  int cnt = 1;

  fib_num[0] = f_1;
  fib_num[1] = f_2;

  for (int i = 2; i < m; ++i) {
    fib_num[i] = (fib_num[i - 2] + fib_num[i - 1]) % m;
    if (fib_num[i] == 1 && fib_num[i - 1] == 0) {
      return fib_num[i - 2];
    }

    ++cnt;
  }

  return fib_num[cnt];
}

int main() {
  int n, m;

  cin >> n >> m;
  cout << large_fib_rem(n, m);
  return 0;
}