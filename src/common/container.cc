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
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/variant.hpp>

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

struct path_name {} ;  
struct creator {} ;

typedef boost::multi_index_container<
  file_node, // table element 
  boost::multi_index::indexed_by<
    boost::multi_index::ordered_unique< 
      boost::multi_index::tag<path_name>,
      BOOST_MULTI_INDEX_MEMBER(file_node, std::string, path_name)
    >, // this is for file's path_name , like primary-key in database table
   
    boost::multi_index::ordered_non_unique<
      boost::multi_index::tag<creator>,
      BOOST_MULTI_INDEX_MEMBER(file_node, std::string, creator)
    > // second index file node's creator
  > // end indexed by
> file_node_table;

typedef boost::shared_ptr<file_node_table> ftPtr ;

void test_multi_index() {
  using namespace boost::multi_index;

  ftPtr file_table_ptr(new file_node_table);
  std::string file_path, author;
  file_path = "/data/rsa_key";
  author = "kokia";

  file_table_ptr->insert( file_node (1200, "/tmp/rsa_key.pub", "Aimer") );
  for (int i = 0; i < 5; i++) {
    char no = i + '0';
    file_table_ptr->insert( file_node(5 - i, file_path + no + ".txt", author));
  }
  std::cout << "++++++++++ print files by author +++++++++++" << std::endl;
  file_node_table::index<creator>::type & index_by_author = file_table_ptr->get<creator>();
  file_node_table::index<creator>::type::iterator creator_it = index_by_author.begin();

  while (creator_it != index_by_author.end()) {
    std::cout << *creator_it << std::endl;
    creator_it++;
  }

  std::cout << "++++++++++ print files by path name +++++++++++" << std::endl;
  file_node_table::index<path_name>::type & file_table_view_index_by_path_name =
            file_table_ptr->get<path_name>() ;

  // path_it points to the first element in the VIEW which sorted by path_name
  file_node_table::index<path_name>::type::iterator
         path_it = file_table_view_index_by_path_name.begin () ;

  for ( ; path_it != file_table_view_index_by_path_name.end() ; path_it++ )
  {
    // call operator<< method of each object which pointed by iterator of path name
    std::cout << *path_it << std::endl ;
  }

  std::cout << "---------- test find method ------------" << std::endl;

  file_node_table::index<creator>::type::iterator 
      itr(file_table_ptr->get<creator>().find("Aimer"));
  if (itr != file_table_ptr->get<creator>().end()) {
    std::cout << "find file node " << std::endl;
    std::cout << *itr << std::endl;
  }
  else {
    std::cout << "file node not find" << std::endl;
  }
}

void test_variant() { // like a union, but the types are different
  boost::variant<int, std::string, double> u;
  u = 4;
  int i = boost:: get<int >(u);
  std::cout << "int : " << i << std ::endl;

  u = "Hello world!";
  std::string s = boost::get<std::string>(u);
  std::cout << "std::string : " << s << std::endl;
  
  u = 3.30;
  double d = boost::get<double>(u);
  std::cout << "double : " << d << std::endl;
}