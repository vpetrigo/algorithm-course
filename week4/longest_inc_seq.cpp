/*
 * Author: vpetrigo
 * Task:
 * Дано целое число 1≤n≤10^3 и массив A[1…n] натуральных чисел, не превосходящих 2⋅10^9. Выведите максимальное 1≤k≤n,
 * для которого найдётся подпоследовательность 1≤i1<i2<…<ik≤n длины k, в которой каждый элемент делится на предыдущий
 * (формально: для  всех 1≤j<k, A[ij]|A[ij+1]).
 *
 * Sample Input:
 * 4
 * 3 6 7 12
 * Sample Output:
 * 3
 */

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <vector>

using namespace std;

// Teacher's unoptimal solution
int get_length_of_longest_divisible_subsequence(const std::vector<int> &numbers) {
  // TODO optimize this function
  int result = 0;
  for (size_t i = 0; i < numbers.size(); i++) {
    int first_number = numbers[i];

    std::vector<int> left_numbers;
    std::remove_copy_if(numbers.begin() + i + 1, numbers.end(), std::back_inserter(left_numbers), [first_number] (int number) { return number % first_number != 0; });
    auto current_result = 1 + get_length_of_longest_divisible_subsequence(left_numbers);
    if (current_result > result) {
      result = current_result;
    }
  }
  return result;
}

// O(n^2)
int LIS_bottom_up(const vector<int>& numbers) {
  const auto len = numbers.size();
  vector<int> D(len, 1);

  for (auto i = 0; i < len; ++i) {
    auto cur_num = numbers[i];
    for (auto j = 0; j < i; ++j) {
      if (cur_num % numbers[j] == 0 && D[j] + 1 > D[i]) {
        D[i] = D[j] + 1;
      }
    }
  }

  auto answer = max_element(D.begin(), D.end());

  return *answer;
}

int main(void) {
  size_t number_count;

  std::cin >> number_count;

  std::vector<int> numbers(number_count);
  for (auto &number : numbers) {
    std::cin >> number;
  }

  std::cout << LIS_bottom_up(numbers);

  return 0;
}

