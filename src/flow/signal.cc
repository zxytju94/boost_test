#include <boost/signals2/signal.hpp>
#include "flow/signal.h"


void test_function() {
  boost::function2<void, std::string, int> func = boost::bind(&TestAddFunc::print_sth, _2, _1);
  func("What's wrong with you?", 1);
  func("Ok, I am fine, thanks!", 1);

  boost::function<int (const char*)> f = std::atoi; 
  std::cout << f("1609") << std::endl; 
  f = std::strlen; 
  std::cout << f("1609") << std::endl; 
}

void test_signal() {
  // signal is a 2D list record the sequence of functions execute 
  boost::signals2::signal<void(int&)>* sig1 = new boost::signals2::signal<void(int&)> ;    // LTDHWBitstream
  sig1->connect(1, &TestAddFunc::slots1); // group_id, function
  sig1->connect(2, &TestAddFunc::slots1);
  sig1->connect(2, &TestAddFunc::slots2, boost::signals2::at_front); // insert the function at front in group 2
  int val = 10;
  //sig1(val);  // The slot 1 called 10\n   The slot 2 called 10\n
}

