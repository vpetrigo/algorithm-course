/*
 * Author: vpetrigo
 * Task:
 * Восстановите строку по её коду и беспрефиксному коду символов.
 * В первой строке входного файла заданы два целых числа k и l через пробел — количество различных букв, встречающихся
 * в строке, и размер получившейся закодированной строки, соответственно. В следующих k строках записаны коды букв в
 * формате "letter: code". Ни один код не является префиксом другого. Буквы могут быть перечислены в любом порядке.
 * В качестве букв могут встречаться лишь строчные буквы латинского алфавита; каждая из этих букв встречается в строке
 * хотя бы один раз. Наконец, в последней строке записана закодированная строка. Исходная строка и коды всех букв непусты.
 * Заданный код таков, что закодированная строка имеет минимальный возможный размер.
 *
 * В первой строке выходного файла выведите строку s. Она должна состоять из строчных букв латинского алфавита.
 * Гарантируется, что длина правильного ответа не превосходит 10^4 символов.
 * Sample Input 1:
 * 1 1
 * a: 0
 * 0
 * Sample Output 1:
 * a
 *
 * Sample Input 2:
 * 4 14
 * a: 0
 * b: 10
 * c: 110
 * d: 111
 * 01001100100111
 * Sample Output 2:
 * abacabad
 */

#include <iostream>
#include <string>
#include <map>

using namespace std;

map<string, char> read_codes(const int n) {
  map<string, char> code_map;

  for (int i = 0; i < n; ++i) {
    char c, delim;
    string code;

    cin >> c >> delim >> code;
    code_map[code] = c;
  }

  return code_map;
}

int main() {
  int n, size;
  string enc_str;

  cin >> n >> size;
  auto code_map = read_codes(n);
  getline(cin, enc_str);

  string cur_code;
  for (int i = 0; i < size; ++i) {
    cur_code.push_back(cin.get());

    if (code_map.find(cur_code) != code_map.end()) {
      cout << code_map[cur_code];
      cur_code.clear();
    }
  }

  return 0;
}

