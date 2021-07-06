#include "stringutil/tokenizer.h"
#include <boost/tokenizer.hpp>
#include <iostream>

void test_tokenizer() {
  std::string str("Link raise the master-sword.");
 
  boost::tokenizer<> tok(str);
 
	for (auto& x : tok)
	{
    std::cout << "[" << x << "]";
	}
  std::cout << std::endl;



  //Separate by 'o' and keep spaces and keep empty tokens
  std::string s = "To be, or not to be?";
	std::cout << "------------------------------------------" << std::endl;
	boost::char_separator<char> sep("o", " ", boost::keep_empty_tokens);
	
	boost::tokenizer<boost::char_separator<char>> t1(s, sep);
  for (auto const & part : t1)
  {
    std::cout << "<" << part << ">" << std::endl;
  }



  int offsets[] = {1,2,3};
	boost::offset_separator os(offsets, offsets + 3);
	auto start = boost::make_token_iterator<std::string>(s.begin(), s.end(),os);
	auto end = boost::make_token_iterator<std::string>(s.end(), s.end(), os);
	for (; start != end; ++start)
	{
		std::cout << "<" << *start << ">" << std::endl;
	}



  {
    std::string str = "Field 1,\"putting quotes around fields,\t allows commasi\",Field 3"; 
    boost::escaped_list_separator<char>("\\", "\t ", "\"");
    boost::tokenizer<boost::escaped_list_separator<char>> tok(str);  
    for (auto pos = tok.begin(); pos != tok.end(); ++pos)  
      std::cout << "[" << *pos << "]";  
    std::cout << std::endl;  
  }
}

