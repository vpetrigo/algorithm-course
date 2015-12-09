/*
 * Author: vpetrigo
 */

#include <iostream>
#include <vector>
#include <numeric>
#include <limits>
#include <set>
#include <iomanip>

using namespace std;

class Partition3 {
 private:
  void print_partition(const vector<int>& S);
 public:
  static constexpr int inf = -1;

  void init_storage(int n, int size);

  int partition(const vector<int> &A, int i, int sum1, int sum2);

  void print_storage() const;

  void restore_answer(const vector<int>& A, int sum);

  vector<vector<vector<int>>> storage;
};

int main() {
  int n;

  cin >> n;
  vector<int> v(n);

  for (auto& elem : v) {
    cin >> elem;
  }

  auto sum = accumulate(v.begin(), v.end(), 0);

  Partition3 p3;

  if (sum % 3 == 0) {
    auto A = sum / 3;
    p3.init_storage(v.size(), A + 1);
    cout << p3.partition(v, v.size() - 1, A, A) << endl;
    p3.restore_answer(v, A);
  }
  else {
    cout << "0";
  }

  return 0;
}

int Partition3::partition(const vector<int> &A, int i, int sum1, int sum2) {
  if (storage[i][sum1][sum2] == inf) {
    if (sum1 == 0 && sum2 == 0) {
      storage[i][sum1][sum2] = 1;
    }
    else if (i == 0) {
      storage[i][sum1][sum2] = (sum1 == 0) && (sum2 == 0);
    }
    else {
      storage[i][sum1][sum2] = partition(A, i - 1, sum1, sum2);
      if (A[i] <= sum1) {
        storage[i][sum1][sum2] = max(storage[i][sum1][sum2], partition(A, i - 1, sum1 - A[i], sum2));
      }
      if (A[i] <= sum2) {
        storage[i][sum1][sum2] = max(storage[i][sum1][sum2], partition(A, i - 1, sum1, sum2 - A[i]));
      }
    }
  }

  return storage[i][sum1][sum2];
}

void Partition3::init_storage(int n, int size) {
  storage.resize(n);
  for (auto& row : storage) {
    row.resize(size);
    for (auto& col : row) {
      col.resize(size);
      for (auto& elem : col) {
        elem = -1;
      }
    }
  }
}

void Partition3::print_storage() const {
  for (const auto& table : storage) {
    cout << "-------------------------" << endl;
    for (const auto& row : table) {
      for (const auto& elem : row) {
        cout << elem << ' ';
      }
      cout << endl;
    }
    cout << "-------------------------" << endl;
    cout << endl;
  }
}

void Partition3::restore_answer(const vector<int> &A, int sum) {
  int j = sum;
  int k = sum;

  vector<int> A1;
  vector<int> A2;
  vector<int> A3;

  for (int i = A.size() - 1; i >= 0; --i) {
    if (storage[i][j][k] != inf) {
      if (A[i] <= j) {
        if (i == 0 || storage[i - 1][j - A[i]][k] != inf) {
          A1.push_back(A[i]);
          j -= A[i];
        }
      }
      else if (A[i] <= k) {
        if (i == 0 || storage[i - 1][j][k  - A[i]] != inf) {
          A2.push_back(A[i]);
          k -= A[i];
        }
      }
      else {
        A3.push_back(A[i]);
      }
    }
    else {
      A3.push_back(A[i]);
    }
  }

  print_partition(A1);
  print_partition(A2);
  print_partition(A3);
}

void Partition3::print_partition(const vector<int> &S) {
  const auto length = S.size();
  cout << "{";

  for (auto i = 0; i < length; ++i) {
    cout << S[i];
    if (i != length - 1) {
      cout << ", ";
    }
  }

  cout << "}" << endl;
}
