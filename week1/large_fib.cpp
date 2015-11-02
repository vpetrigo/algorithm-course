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

using namespace std;

constexpr int f_1 = 0;
constexpr int f_2 = 1;

// Because of modulo operation under the Fibonacci numbers causes to periodical
// sequence (https://en.wikipedia.org/wiki/Pisano_period) it is possible to
// calculate untill n-th Fibonacci number reached or sequence starts again from F(k) = 0, F(k + 1) = 1
int large_fib_rem(long long n, int m) {
  vector<int> fib_num {f_1, f_2};
  int cnt = 1;

  for (int i = 2; i < n; ++i) {
    fib_num.push_back((fib_num[i - 2] + fib_num[i - 1]) % m);
    // if the sequence repeats then exit the loop
    if (fib_num[i] == 1 && fib_num[i - 1] == 0) {
      break;
    }

    ++cnt;
  }

  auto offset = n % cnt;

  return fib_num[offset];
}

int main() {
  long long n;
  int m;

  cin >> n >> m;
  cout << large_fib_rem(n, m);

  return 0;
}