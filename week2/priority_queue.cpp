/*
 * Author: vpetrigo
 * Task:
 * Первая строка входа содержит число операций 1≤n≤10^5. Каждая из последующих n строк задают операцию одного из
 * следующих двух типов:
 * Insert x, где 0≤x≤10^9 — целое число;
 * ExtractMax.
 * Первая операция добавляет число x в очередь с приоритетами, вторая — извлекает максимальное число и выводит его.
 *
 * Sample Input:
 * 6
 * Insert 200
 * Insert 1
 * ExtractMax
 * Insert 5
 * Insert 500
 * ExtractMax
 *
 * Sample Output:
 * 200
 * 500
 */

#include <iostream>
#include <vector>
#include <functional>

using namespace std;

template <typename Type, typename Container = vector<Type>,
    typename Compare = less<typename Container::value_type>>
struct Priority_queue {
  using value_type = Type;

  static constexpr int root_index = 0;

  Priority_queue() {}

  void insert(const Type& elem) {
    queue.push_back(elem);

    if (queue.size() > 1) {
      sift_up(queue.size() - 1);
    }
  }

  value_type& get_first() {
    return queue[root_index];
  }

  const value_type& get_first() const {
    return queue[root_index];
  }

  value_type extract_first() {
    value_type elem = queue[root_index];
    queue[root_index] = queue.back();
    queue.pop_back();
    sift_down(root_index);

    return elem;
  }

 protected:
  void sift_up(int index) {
    auto parent = (index - 1) / 2;
    while (parent >= 0 && Comp(queue[index], queue[parent])) {
      swap(queue[index], queue[parent]);
      index = parent;
      parent = (index -  1) / 2;
    }
  }

  void sift_down(int index) {
    while (2 * index + 1 < queue.size()) {
      int left_ch = 2 * index + 1;
      int right_ch = 2 * index + 2;

      int elem_to_swap = left_ch;
      if (right_ch < queue.size() && Comp(queue[right_ch], queue[left_ch])) {
        elem_to_swap = right_ch;
      }

      if (queue[index] >= queue[elem_to_swap]) {
        break;
      }

      swap(queue[index], queue[elem_to_swap]);
      index = elem_to_swap;
    }
  }

 protected:
  Compare Comp;

 private:
  Container queue;
};

int main() {
  Priority_queue<int, vector<int>, greater<int>> pq;
  int n;
  string command;

  cin >> n;

  for (int i = 0; i < n; ++i) {
    cin >> command;

    if (command.compare("Insert") == 0) {
      int val;

      cin >> val;
      pq.insert(val);
    }
    else if (command.compare("ExtractMax") == 0) {
      cout << pq.extract_first() << endl;
    }
  }

  return 0;
}