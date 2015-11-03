//
// Created by vpetrigo
//

#ifndef ALGORITHM_COURSE_PRINTS_H
#define ALGORITHM_COURSE_PRINTS_H

#include <iostream>
#include <iterator>

template <typename Cont>
//  requires Container<Cont>()
void print_vector(const Cont& v) {
  using Cont_type = typename Cont::value_type;

  std::ostream_iterator<Cont_type> os{std::cout, " "};
  std::copy(v.begin(), v.end(), os);
  std::cout << std::endl;
}

#endif //ALGORITHM_COURSE_PRINTS_H
