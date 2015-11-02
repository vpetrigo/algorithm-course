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

int large_fib_rem(long long n, int m) {
  vector<int> fib_num {f_1, f_2};
  int cnt = 1;

  for (int i = 2; i < n; ++i) {
    fib_num.push_back((fib_num[i - 2] + fib_num[i - 1]) % m);
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