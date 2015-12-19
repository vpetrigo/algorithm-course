/*
 * Author: vpetrigo
 */

#include <iostream>
#include <vector>
#include <numeric>
#include <limits>
#include <iomanip>

using namespace std;

class Partition3 {
 private:
  void print_partition(const vector<int>& S);
 public:
  static constexpr int inf = -1;

  void init_storage(int n, int size);

  int partition_bu(const vector<int> &A, int i, int sum1, int sum2);
  int partition_td(const vector<int> &A, int sum);

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
    p3.init_storage(v.size() + 1, A + 1);
    cout << p3.partition_bu(v, v.size(), A, A) << endl;
    p3.restore_answer(v, A);
    p3.partition_td(v, A);
  }
  else {
    cout << "0";
  }

  return 0;
}

int Partition3::partition_bu(const vector<int> &A, int i, int sum1, int sum2) {
  if (storage[i][sum1][sum2] == inf) {
    if (sum1 == 0 && sum2 == 0) {
      storage[i][sum1][sum2] = 1;
    }
    else if (i == 0) {
      storage[i][sum1][sum2] = (sum1 == 0) && (sum2 == 0);
    }
    else {
      storage[i][sum1][sum2] = partition_bu(A, i - 1, sum1, sum2);
      if (A[i - 1] <= sum1) {
        storage[i][sum1][sum2] = max(storage[i][sum1][sum2], partition_bu(A, i - 1, sum1 - A[i - 1], sum2));
      }
      if (A[i - 1] <= sum2) {
        storage[i][sum1][sum2] = max(storage[i][sum1][sum2], partition_bu(A, i - 1, sum1, sum2 - A[i - 1]));
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
        elem = inf;
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
  int sum1 = sum;
  int sum2 = sum;

  vector<int> A1;
  vector<int> A2;
  vector<int> A3;

  for (int i = A.size(); i > 0; --i) {
    if (A[i - 1] <= sum1 && storage[i - 1][sum1 - A[i - 1]][sum2] != 0) {
      A1.push_back(A[i - 1]);
      sum1 -= A[i - 1];
    }
    else if (A[i - 1] <= sum2 && storage[i - 1][sum1][sum2 - A[i - 1]] != 0) {
      A2.push_back(A[i - 1]);
      sum2 -= A[i - 1];
    }
    else {
      A3.push_back(A[i - 1]);
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

int Partition3::partition_td(const vector<int> &A, int sum) {
  const auto length = A.size() + 1;
  const auto sum_len = sum + 1;
  vector<vector<vector<int>>> result(length, vector<vector<int>> (sum_len, vector<int> (sum_len)));

  // generate distance 3D table
  for (auto& row : result) {
    for (auto& col : row) {
      for (auto& elem : col) {
        elem = 0;
      }
    }
  }

  // fill each dist[i, 0, 0] with 1
  for (int i = 0; i < length; ++i) {
    result[i][0][0] = 1;
  }

  for (int i = 1; i < length; ++i) {
    for (int S1 = 0; S1 < sum_len; ++S1) {
      for (int S2 = 0; S2 < sum_len; ++S2) {
        result[i][S1][S2] = result[i - 1][S1][S2];

        if (A[i - 1] <= S1) {
          result[i][S1][S2] = max(result[i][S1][S2], result[i - 1][S1 - A[i - 1]][S2]);
        }
        if (A[i - 1] <= S2) {
          result[i][S1][S2] = max(result[i][S1][S2], result[i - 1][S1][S2 - A[i - 1]]);
        }
      }
    }
  }

  // restore partitions
  if (result[length - 1][sum][sum] != 0) {
    int s1 = sum;
    int s2 = sum;
    vector<int> part1, part2, part3;

    for (int i = length - 1; i > 0; --i) {
      if (A[i - 1] <= s1 && result[i - 1][s1 - A[i - 1]][s2] != 0) {
        part1.push_back(A[i - 1]);
        s1 -= A[i - 1];
      }
      else if (A[i - 1] <= s2 && result[i - 1][s1][s2 - A[i - 1]] != 0) {
        part2.push_back(A[i - 1]);
        s2 -= A[i - 1];
      }
      else {
        part3.push_back(A[i - 1]);
      }
    }

    print_partition(part1);
    print_partition(part2);
    print_partition(part3);
  }

  return result[length - 1][sum][sum];
}
