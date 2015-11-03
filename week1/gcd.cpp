/*
 * Author: vpetrigo
 * Task:
 * Find a GCD for the numbers 1 <= a, b <= 2 * 10^9
 * Sample Input 1:
 * 18 35
 * Sample Output 1:
 * 1
 *
 * Sample Input 2:
 * 14159572 63967072
 * Sample Output 2:
 * 4
 */

#include <iostream>

using namespace std;

int gcd_rec(int a, int b) {
  if (a == 0) {
    return b;
  }
  else if (b == 0) {
    return a;
  }
  else if (a >= b) {
    return gcd_rec(a % b, b);
  }
  else {
    return gcd_rec(a, b % a);
  }
}

int gcd(int a, int b) {
  if (a == 0) {
    return b;
  }
  else if (b == 0) {
    return a;
  }

  while (a != 0 && b != 0) {
    if (a >= b) {
      a %= b;
    }
    else {
      b %= a;
    }
  }

  int gcd = (a != 0) ? a : b;

  return gcd;
}

int main() {
  int a, b;

  cin >> a >> b;
  cout << gcd(a, b);

  return 0;
}