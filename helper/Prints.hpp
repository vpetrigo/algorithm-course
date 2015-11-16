//
// Created by vpetrigo
//

#ifndef ALGORITHM_COURSE_PRINTS_H
#define ALGORITHM_COURSE_PRINTS_H

#include <iostream>
#include <iterator>
#include <utility>
#include <vector>

template <typename Cont>
//  requires Container<Cont>()
void print_cont(const Cont &v) {
  using Cont_type = typename Cont::value_type;

  std::ostream_iterator<Cont_type> os{std::cout, " "};
  std::copy(v.begin(), v.end(), os);
  std::cout << std::endl;
}

template <typename First, typename Second>
void print_pairs(const std::vector<std::pair<First, Second>>& v) {
  for (int i = 0; i < v.size(); ++i) {
    std::cout << v[i].first << ' ' << v[i].second << std::endl;
  }
}

#endif //ALGORITHM_COURSE_PRINTS_H
