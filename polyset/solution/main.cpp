#include "searchable_bag.hpp"
#include "searchable_array_bag.hpp"
#include "searchable_tree_bag.hpp"
#include "set.hpp"

#include <iostream>
#include <stdlib.h>

int main(int argc, char **argv) {
  if (argc == 1)
    return 1;
  searchable_bag *t = new searchable_tree_bag;
  searchable_bag *a = new searchable_array_bag;

  for (int i = 1; i < argc; i++) {
    t->insert(atoi(argv[i]));
    a->insert(atoi(argv[i]));
  }
  a->print();
  for (int i = 1; i < argc; i++) {
    std::cout << a->has(atoi(argv[i]));
    std::cout << a->has(atoi(argv[i]) - 1);
  }
  std::cout << std::endl;
  t->print();
  for (int i = 1; i < argc; i++) {
    std::cout << t->has(atoi(argv[i]));
    std::cout << t->has(atoi(argv[i]) - 1);
  }
  std::cout << std::endl;

//  t->clear();
  //a->clear();

  const searchable_array_bag tmp(static_cast<searchable_array_bag &>(*a));
  std::cout << "array_bag::print()" << std::endl;
  tmp.print();
  tmp.has(1);

  set sa(*a);
  set st(*t);
  for (int i = 1; i < argc; i++) {
    st.insert(atoi(argv[i]));
    sa.insert(atoi(argv[i]));
    }
  std::cout << "set::print()" << std::endl;
    sa.print();
  for (int i = 1; i < argc; i++) {
    std::cout << sa.has(atoi(argv[i]));
    std::cout << sa.has(atoi(argv[i]) - 1);
  }
	std::cout << std::endl;
    st.print();
  for (int i = 1; i < argc; i++) {
    std::cout << st.has(atoi(argv[i]));
    std::cout << st.has(atoi(argv[i]) - 1);
  }
	std::cout << std::endl;
    sa.print();
    sa.get_bag().print();
    st.print();
//    sa.clear();
    sa.insert((int[]){1, 2, 3, 4}, 4);
    sa.print();
    st.insert((int[]){1, 2, 3, 4}, 4);
    st.print();
    std::cout << std::endl;
  

  return 0;

}
