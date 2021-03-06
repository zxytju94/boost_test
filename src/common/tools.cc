#include <iostream>
#include <boost/lexical_cast.hpp>
#include <boost/date_time/local_time/local_time.hpp> 
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/io/io.hpp>
#include <boost/exception/all.hpp>
#include <boost/system/error_code.hpp>

    
void test_lexical_cast() {
  std::string s = "2.1";
	double d = boost::lexical_cast<double>(s);
	
	std::string ss = "12345";
	int n = boost::lexical_cast<int>(ss);
		
	std::cout << d << " : " << n << std::endl;

	try {
		boost::lexical_cast<int>("abcde");
	}
	catch(const boost::bad_lexical_cast & e)
	{
		std::cout << e.what() << std::endl;
	}
}

void test_local_time() {
  boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
  std::string now_str = to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());

  std::cout << now_str.c_str() << std::endl;
}

void test_geometry() {
  namespace bg  = boost::geometry;
  namespace bgm = bg::model;

  using point = bgm::d2::point_xy<int>;
  using poly  = bgm::polygon<point>;
  using mpoly = bgm::multi_polygon<poly>;
  
  poly a, b, c;
  bg::read_wkt("POLYGON((0 0 0 6 6 6 6 0 0 0))", a);
  bg::read_wkt("POLYGON((4 -1 4 4 5 4 5 -1 4 -1))", b);
  bg::read_wkt("POLYGON((3 -3 3 3 9 3 9 -3 3 -3))", c);

  std::cout << bg::wkt(a) << "\n";
  std::cout << bg::wkt(b) << "\n";
  std::cout << bg::wkt(c) << "\n";

  {
    std::ofstream svg("output.svg");
    boost::geometry::svg_mapper<point> mapper(svg, 400, 400);
    mapper.add(a);
    mapper.add(b);
    mapper.add(c);

    mapper.map(a, "fill-opacity:0.2;fill:rgb(0,0,153);stroke:rgb(0,0,200);stroke-width:2");
    mapper.map(b, "fill-opacity:0.2;fill:rgb(153,0,0);stroke:rgb(200,0,0);stroke-width:2");
    mapper.map(c, "fill-opacity:0.2;fill:rgb(0,153,0);stroke:rgb(0,200,0);stroke-width:2");
  }
}

struct both_exception : virtual boost::exception, virtual std::exception {
};

typedef boost::error_info<struct tag_err_no, int> err_no;
typedef boost::error_info<struct tag_err_str, std::string> err_str;

void test_exception() {
  try 
  {
    try 
    {
      throw both_exception() << err_no(10);
    }
    catch (both_exception& e) {
      std::cout << *boost::get_error_info<err_no>(e) << std::endl;
      std::cout << e.what() << std::endl;
      e << err_str("other info");
      throw;
    }
  }
  catch (both_exception& e)
  {
    std::cout << *boost::get_error_info<err_str>(e) << std::endl;
    std::cout << e.what() << std::endl;
  }
}

void test_error_code() {
  using namespace boost::system;

  error_code ec;
  ec = errc::make_error_code(errc::not_supported);
  std::cout << "err:\"not_supported\" value/category:" << ec.value() << " " << ec.category().name() << std::endl;

  error_condition ecnd = ec.default_error_condition();
  std::cout << "default err_cond: value/category:" << ecnd.value() << " " << ecnd.category().name() << std::endl;
}