/* Author: vpetrigo
 * Task:
 * Calculate a Fibonacci number
 * 1 <= n <= 40
 */

#include <iostream>

using namespace std;

// function for calculation small fibonacci numbers (n <= 40)
int fib(int n) {
  if (n <= 1) {
    return n;
  }

  return fib(n - 1) + fib(n - 2);
}

int main() {
  int n;

  cin >> n;
  cout << fib(n);

  return 0;
}