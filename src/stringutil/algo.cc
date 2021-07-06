#include <boost/algorithm/string.hpp>  // split
#include <boost/algorithm/string/trim_all.hpp>  // split
#include <string>
#include "stringutil/algo.h"
#include <iostream>
#include <vector>


void test_algo() {
  std::string s("AbcDeFGHIJklmn");
  s += s;
  s += s;
  std::string s1 = boost::algorithm::replace_all_copy(s, "AbcD", "**");
  std::string s2 = boost::algorithm::replace_first_copy(s, "AbcD", "**");
  std::string s3 = boost::algorithm::replace_last_copy(s, "AbcD", "**");
  std::string s4 = boost::algorithm::replace_nth_copy(s, "AbcD", 1, "**");

	std::string test = "hello  world\r\n";
	//Does not remove the spaces
	boost::algorithm::trim(test);
	std::cout << "<" << test <<">" << std::endl;

	std::string test1 = "hello  world\r\n";
  //Removes double space and replace by single space
	boost::algorithm::trim_all(test1);
  std::cout << "<" << test1 <<">" << std::endl;
}

void test_replace() {
  std::string name = "AXXBXXCXXDXXE";
  boost::erase_all(name, "XX");
  std::cout << name << std::endl;
}

void test_split() {
  std::vector<std::string> vec;  // LTDHWTarget::getTcfSpec
  std::string ip_address("139::186::0::1");
  boost::split(vec, ip_address, boost::is_any_of("::"), boost::token_compress_on);
  for (int i = 0; i < vec.size(); ++i) {
    std::cout << vec[i] << " ";
  }
  std::cout << std::endl;


  {
    std::vector<std::string> lib_dirs;
    std::string env = getenv("LD_LIBRARY_PATH");
    boost::split(lib_dirs, env, boost::is_any_of(":"), boost::token_compress_on);
    for (int i = 0; i < lib_dirs.size(); ++i) {
      std::cout << lib_dirs[i] << " ";
    }
    std::cout << std::endl;
  }
}

