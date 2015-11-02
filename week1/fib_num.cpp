/*
 * Author: vpetrigo
 * Task:
 * Find the last digit number of Fibonacci number
 * 1 <= n <= 10 ^ 7
 */

#include <iostream>

using namespace std;

int last_fib_digit(int n) {
  constexpr int last_dig = 10;
  int f_0 = 1;
  int f_1 = 1;

  for (int i = 2; i < n; ++i) {
    int tmp = f_1;
    f_1 = (f_1 + f_0) % last_dig;
    f_0 = tmp;
  }

  return f_1;
}

int main() {
  int n;

  cin >> n;
  cout << last_fib_digit(n);
  return 0;
}