/*
 * Author: vpetrigo
 * Task:
 * Вычислите расстояние редактирования двух данных непустых строк длины не более 10^2, содержащих строчные буквы
 * латинского алфавита.
 *
 * Sample Input 1:
 * ab
 * ab
 * Sample Output 1:
 * 0
 * Sample Input 2:
 * short
 * ports
 * Sample Output 2:
 * 3
 */

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int get_levenshtein_distance(const std::string &str1, const std::string &str2) {
  // TODO optimize this function
  size_t size1 = str1.size();
  size_t size2 = str2.size();
  if (str1.empty() || str2.empty()) {
    return size1 + size2;
  }

  int insert_distance = get_levenshtein_distance(str1, str2.substr(1)) + 1;
  int delete_distance = get_levenshtein_distance(str1.substr(1), str2) + 1;
  int match_distance = get_levenshtein_distance(str1.substr(1), str2.substr(1)) + (str1[0] != str2[0]);
  return std::min({insert_distance, delete_distance, match_distance});
}

int edit_dist_bu(const string& str1, const string& str2) {
  vector<vector<int>> dist;
  auto len1 = str1.size() + 1;
  auto len2 = str2.size() + 1;

  dist.resize(len1);
  for (auto& row : dist) {
    row.resize(len2);
  }

  for (int i = 0; i < len1; ++i) {
    dist[i][0] = i;
  }
  for (int j = 0; j < len2; ++j) {
    dist[0][j] = j;
  }

  for (int i = 1; i < len1; ++i) {
    for (int j = 1; j < len2; ++j) {
      auto diff_cost = static_cast<int> (str1[i - 1] != str2[j - 1]);
      auto insertion_cost = dist[i - 1][j] + 1;
      auto delete_cost = dist[i][j - 1] + 1;
      auto eq_cost = dist[i - 1][j - 1] + diff_cost;

      dist[i][j] = min({insertion_cost, delete_cost, eq_cost});
    }
  }

  return dist[len1 - 1][len2 - 1];
}

int main(void) {
  std::string str1;
  std::string str2;

  std::cin >> str1 >> str2;

  std::cout << get_levenshtein_distance(str1, str2) << std::endl;
  std::cout << edit_dist_bu(str1, str2) << std::endl;

  return 0;
}