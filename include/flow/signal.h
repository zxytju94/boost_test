#ifndef SIGNAL_H
#define SIGNAL_H
#include <iostream>
#include <boost/shared_ptr.hpp>
#include <common/container.h>

class TestAddFunc {
 public:
  boost::shared_ptr<Book>* my_sp;

 public:
  static void print_sth(int x, std::string str) {
    for (int i = 0; i < x; i++) {
      // boost::mutex::scoped_lock lock(io_mutex);
      std::cout << "str:" << str << std::endl;
    }
  }

  static void slots1(int& val) {
    std::cout << "The slot 1 called " << val << std::endl;
    val = 20;
  }
 
  static void slots2(int& val) {
    std::cout << "The slot 2 called " << val << std::endl;
  }

};

void test_function();
void test_signal();

#endif
