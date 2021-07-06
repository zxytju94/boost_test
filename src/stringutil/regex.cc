#include <string>
#include <boost/regex.hpp>
#include "stringutil/regex.h"
#include <iostream>

void test_regex() {
  test_regex1();
  std::string str = "0000-1111-2222-3333";  // LTDHWObjectManager::isValidTargetName
  boost::regex re("(\\d{4}[- ]){3}\\d{4}");
  boost::smatch what;
  bool res = boost::regex_match(str, what, re);
  std::cout << std::boolalpha << "Matched " << res << std::endl;
  if (res) {
    for (int i = 0; i < what.size(); ++i) {
      std::string msg(what[i].first, what[i].second);
      std::cout<< i << ":" << msg.c_str() << std::endl;
    }
  }
}

void test_regex1() {
  std::string str = "ShaaaangHaiiii";
  boost::regex re("Sha+ngHai*");
  if (boost::regex_match(str, re)) {
    std::cout << "ShangHai matched" << std::endl;
  }

  {
    const char *szStr = "http://www.cppprog.com/2009/0112/48.html";
    boost::regex reg("/");
    boost::cregex_token_iterator itrBegin(szStr, szStr+strlen(szStr), reg, -1);
    boost::cregex_token_iterator itrEnd;

    for (boost::cregex_token_iterator itr = itrBegin; itr != itrEnd; ++itr)
    {
      std::cout << *itr << std::endl;
    }
  }
}
