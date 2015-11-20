/*
 * Author: vpetrigo
 * Task:
 * Первая строка содержит число 1≤n≤10^5, вторая — массив A[1…n], содержащий натуральные числа, не превосходящие 10^9.
 * Необходимо посчитать число пар индексов 1≤i<j≤n, для которых A[i]>A[j]. (Такая пара элементов называется инверсией
 * массива. Количество инверсий в массиве является в некотором смысле его мерой неупорядоченности: например, в
 * упорядоченном по неубыванию массиве инверсий нет вообще, а в массиве, упорядоченном по убыванию, инверсию образуют
 * каждые два элемента.)
 *
 * Sample Input:
 * 5
 * 2 3 9 2 9
 * Sample Output:
 * 2
 */

#include <iostream>
#include <vector>
#include <iterator>
#include <Prints.hpp>

using namespace std;

template <typename Type>
vector<Type> fill_cont() {
  istream_iterator<Type> it{cin};
  istream_iterator<Type> eos;
  vector<Type> v{it, eos};

  return v;
}

template <typename Type>
class Queue {
 public:
  using iterator = typename vector<Type>::iterator;
  using const_iterator = typename vector<Type>::const_iterator;
  using value_type = typename vector<vector<Type>>::value_type;

  explicit Queue(initializer_list<Type>& il) : storage{il} {}

  Queue(const_iterator begin, const_iterator end) : storage(distance(begin, end)) {
    auto i = 0;

    while (begin != end) {
      storage[i].push_back(*begin++);
      ++i;
    }
  }

  void push_back(const value_type& elem) {
    storage.push_back(elem);
  }

  void push_front(const value_type& elem) {
    storage.insert(storage.begin(), elem);
  }

  const value_type& get_front() const {
    return storage.front();
  }

  value_type& get_front() {
    return storage.front();
  }

  void pop_front() {
    storage.erase(storage.begin());
  }

  const_iterator begin() const {
    return storage.cbegin();
  }

  iterator begin() {
    return storage.begin();
  }

  const_iterator end() const {
    return storage.cend();
  }

  iterator end() {
    return storage.end();
  }

  const size_t size() const {
    return storage.size();
  }

 private:
  vector<vector<Type>> storage;
};

template <typename It>
vector<typename It::value_type> merge(const It begin, const It mid, const It end, long long& inv) {
  vector<typename It::value_type> v;
  It first_arr{begin};
  It second_arr{mid};
  const It first_arr_end{mid};
  const It second_arr_end{end};

  while (first_arr != first_arr_end && second_arr != second_arr_end) {
    if (*first_arr <= *second_arr) {
      v.push_back(*first_arr++);
    }
    else {
      v.push_back(*second_arr++);
      inv += distance(first_arr, first_arr_end);
    }
  }

  v.insert(v.end(), first_arr, first_arr_end);
  v.insert(v.end(), second_arr, second_arr_end);

  return v;
}

template <typename It>
auto merge_sort(It begin, It end) -> long long {
  auto size = distance(begin, end);
  long long inv = 0;

  if (size > 1) {
    auto mid = next(begin, size / 2);

    inv += merge_sort(begin, mid);
    inv += merge_sort(mid, end);

    auto &&v = merge(begin, mid, end, inv);
    move(v.begin(), v.end(), begin);
  }

  return inv;
}

long long inv = 0;

template <typename Cont>
Cont merge_it(const Cont& first, const Cont& second) {
  Cont v;
  auto f_it{first.begin()};
  auto f_end{first.end()};
  auto s_it{second.begin()};
  auto s_end{second.end()};

  while (f_it != f_end && s_it != s_end) {
    if (*f_it <= *s_it) {
      v.push_back(*f_it++);
    }
    else {
      v.push_back(*s_it++);
      inv += distance(f_it, f_end);
    }
  }

  v.insert(v.end(), f_it, f_end);
  v.insert(v.end(), s_it, s_end);

  return v;
}

template <typename CIt>
vector<typename CIt::value_type> iterative_merge_sort(CIt begin, CIt end) {
  Queue<typename CIt::value_type> q{begin, end};

  while(q.size() > 1) {
    auto first = q.get_front();
    q.pop_front();
    auto second = q.get_front();
    q.pop_front();

    q.push_front(merge_it(first, second));
  }

  return q.get_front();
}

int main() {
  int n;

  cin >> n;
  auto v = fill_cont<int>();
//  auto res = merge_sort(v.begin(), v.end());
//  cout << res << endl;
  auto sorted = iterative_merge_sort(v.cbegin(), v.cend());
  print_cont(sorted.begin(), sorted.end());
  cout << inv << endl;

  return 0;
}