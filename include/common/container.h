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

struct file_node {
  int id;
  std::string path_name;
  long length;
  std::string creator;
  
  file_node( int id , std::string path_name , std::string creator ): 
        id(id) , path_name(path_name) , length(0), creator(creator) {
  }

  inline friend std::ostream & operator<<(std::ostream& os, const file_node& f);
};

std::ostream& operator<<(std::ostream& os, const file_node& f) {
  char file_buffer[1024];
  std::string file_content;
  bool isOpen = false;

  FILE *fp = fopen(f.path_name.c_str() , "r");
  if ( fp != NULL )
    isOpen = true ;

  if ( isOpen ) {
    int ret = fread((void*)file_buffer , sizeof(char) , sizeof(file_buffer)-1 , fp );
    file_buffer[ret] = '\0' ;
    
    file_content+= file_buffer ;

    fclose (fp) ;
  }
  
  else
  {
    file_content = "failed open file "+ f.path_name ;
  }

  os <<"[file path]     " << f.path_name << std::endl
     << "[file index]     " << f.id << std::endl
     <<"[file creator] " << f.creator << std::endl
     <<"[file contents] " << file_content << std::endl << std::endl ; ;
  return os ;
}

void test_shared_ptr();
void test_any();
void test_optional();
void test_dy_bitset();
void test_logic_tri();
void test_unmap();
void test_multi_index();
void test_variant();

#endif
