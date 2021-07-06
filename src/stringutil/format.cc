#include "stringutil/format.h"
#include <boost/format.hpp>
#include <iostream>

void test_format() {
  int a1 = 12;  //labtools LTDHWXsdbSlave::createFakeUUID
  int a2 = 43;
  int a3 = 3;
  int a4 = 1415;
  boost::format fmt("12 in hex as %08X, 43 in bin as %08X, the value of pie is %d.%04d");
  fmt % a1;
  fmt % a2;
  fmt % a3;
  fmt % a4;
  std::cout << fmt.str() << std::endl;

  std::cout << boost::format("\n\n%s"
            "%1t = [%d]\n"
            "%1t = [%5d]\n"
            "%1t = [%05d]\n"
            "%1t = [%x]\n"
            "%1t = [%o]\n"
            "%1t = [%f]\n"
            "%1t = [%3.3f]\n"
            "%1t = [%e]\n"
            ) % "example :\n" % 15 % 15 % 15 % 15 % 15 % 15.01 % 15.01 % 15.01 << std::endl;
}

