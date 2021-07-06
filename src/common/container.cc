#include "common/container.h"
#include <iostream>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/any.hpp>
#include <boost/dynamic_bitset.hpp>
#include "boost/utility/binary.hpp"
#include <boost/exception/to_string.hpp>
#include <boost/logic/tribool.hpp>
#include <unordered_map>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>

void test_shared_ptr() {
  std::string book1("C plus plus");
  boost::shared_ptr<Book> myBook(new Book(book1, 100));
  boost::shared_ptr<Book> myBook1(myBook);
  std::cout << "[From myBook] The ref count of book is " << myBook.use_count() << "." << std::endl;
  myBook.reset();
  std::cout << "[From myBook] The ref count of book is " << myBook.use_count() << "." << std::endl;
  std::cout << "[From myBook] The ref count of book is " << myBook1.use_count() << "." << std::endl;
  Book* cur_book = myBook.get();
  if (cur_book) {
    std::cout << "still bind" << std::endl;
  } else {
    std::cout << "has been released" << std::endl;
  }
  cur_book = myBook1.get();
  if (cur_book) {
    std::cout << cur_book->page_num << std::endl;
  }
}

void test_any() {
	boost::any w;
	boost::any x { 2.0 };
	std::vector<boost::any> y {42, "life"};
	boost::any z = std::string("test");
	
	if (!x.empty()) {
		std::cout << x.type().name() << std::endl;
	}
	
	std::cout << boost::any_cast<int>(y[0]) << std::endl;

	try {
		int b = boost::any_cast<int>(y[1]);	
	}	
  catch (boost::bad_any_cast const & e) {
		std::cout << "wrong type" << std::endl;
	}

	for (auto a : y) {	
		std::cout << "********" <<  a.type().name() << std::endl;
		int * value = boost::any_cast<int>(&a); 
		if (value)
      std::cout << "cast int is: " << *value << std::endl;	

		const char ** text = boost::any_cast<const char*>(&a);
		if (text) 
      std::cout << "cast cchar is: " << *text << std::endl;
	}


	std::vector<boost::any> test;
	test.emplace_back(A{4});
	test.emplace_back(B{"Hello"});	
		
	for (auto const & i : test) {
		std::cout << "********" <<  i.type().name() << std::endl;
		auto * a =  boost::any_cast<B>(&i);
		if (a) 
      std::cout << a->n << std::endl;
	}
}

void test_optional() {
  // optional can contain uninit values but is not NULL, -1, EOF, string::npos, vector::end() etc.
  boost::optional<std::string> ops("test_one");
  std::cout << *ops << std::endl;

	Person p{"John", "Watson"};
	std::cout << (p.m_middleName ? *p.m_middleName : "No middle Name" ) << std::endl;

	p.m_middleName = "Hamish";
	p.m_middleName = "The Gambler";
	std::cout << (p.m_middleName ? *p.m_middleName : "No middle Name" ) << std::endl;
	//need to construct the object, since it is pointer
	p.m_address = Address {"Boulder"} ;
	
	if (p.m_address) {
		std::cout << p.m_address -> m_streetName << std::endl;
	}	
}

void test_dy_bitset() {
  boost::dynamic_bitset<> db(std::string("0100"));
  std::cout << db << std::endl;
  db.set(1);
  db.reset(2);
  std::cout << db.to_ulong() << std::endl;
  db.resize(8, false);

  boost::dynamic_bitset<> db1(8, BOOST_BINARY(11110101));
  std::string str = boost::to_string(db ^ db1);
  std::cout << str << std::endl;
}

void test_logic_tri() {
    using namespace boost;
    tribool tb(true);
    tribool tb2(!tb);

    if (tb)  // tb == true
    { 
      std::cout << "true" << std::endl; 
    }

    tb2 = indeterminate;
    assert(indeterminate(tb2)); 
    std::cout << "tb2 = " << tb2 << std::endl;

    if (indeterminate(tb2))
    {   
      std::cout << "indeterminate" << std::endl;
    }
    std::cout << (tb2 || true ) << std::endl;
    std::cout << (tb2 && false ) << std::endl;
}

void test_unmap() {
  boost::unordered_map<int, int> pistachios;
  pistachios[1] = 2;
  pistachios[2] = 3;
  pistachios[1] = 5;

  for (auto& ite : pistachios)
    std::cout << "key->" << ite.first << " val->" << ite.second << std::endl;

  std::unordered_map<int, std::string> linux_moto;
  linux_moto.emplace(10, "hour");
  linux_moto.emplace(6, "month");
  for (auto& ite : linux_moto)
    std::cout << "key->" << ite.first << " val->" << ite.second << std::endl;
  
  boost::unordered_set<int> ch_heart;
  ch_heart.insert(10);
  ch_heart.insert(6);
  for (auto& ite : ch_heart)
    std::cout << "key->" << ite << std::endl;
}
