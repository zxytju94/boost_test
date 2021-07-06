#ifndef CONTAINER_H
#define CONTAINER_H
#include <string>
#include <boost/optional.hpp>

class Book {
 public:
  std::string name;
  int page_num;

 public:
  Book(std::string str, int num) {
    name = str;
    page_num = num;
  }
  ~Book() {}
};

struct A 
{
	int n;
};

struct B
{
	std::string n;
};

class Address
{
public:
	Address(std::string const & streetName ):
		m_streetName(streetName){}
	std::string m_streetName;
};

class Person
{
public:
	Person(const std::string & firstName, const std::string & lastName):
			m_firstName(firstName), m_lastName(lastName) {}
	std::string m_firstName;
	std::string m_lastName;
	boost::optional<std::string> m_middleName;
	boost::optional<Address> m_address;
};

void test_shared_ptr();
void test_any();
void test_optional();
void test_dy_bitset();
void test_logic_tri();
void test_unmap();

#endif
