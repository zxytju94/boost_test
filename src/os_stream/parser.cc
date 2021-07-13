#include <iostream>
#include <sstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>


int rjson() {
  using namespace boost::property_tree;

  ptree pt;
  try {    
    read_json("../url.json", pt);
  }
  catch (ptree_error & e) {
    return 1; 
  }

  try {
    int code = pt.get<int>("code");
    ptree image_array = pt.get_child("images");
    
    BOOST_FOREACH (boost::property_tree::ptree::value_type &v, image_array)
    {
      std::stringstream s;
      write_json(s, v.second);
      std::string image_item = s.str();
      std::cout << image_item << std::endl;
    }
  }
  catch (ptree_error & e)
  {
    return 2;
  }
  return 0;
}

void wjson() {
  using namespace boost::property_tree;

  ptree pt;
  ptree children;
  ptree child1, child2, child3;

  child1.put("childkeyA", 1);
  child1.put("childkeyB", 2);

  child2.put("childkeyA", 3);
  child2.put("childkeyB", 4);

  child3.put("childkeyA", 5);
  child3.put("childkeyB", 6);

  children.push_back(std::make_pair("child1", child1));
  children.push_back(std::make_pair("", child2));
  children.push_back(std::make_pair("child3", child3));

  pt.put("testkey", "testvalue");
  pt.add_child("MyArray", children);

  write_json("../test.json", pt);
}

void for_json() {
  rjson();
  wjson();

  std::string const sample = R"(
  {
    "background": {
       "scripts": [ "name1.js", "name2.js", "name3.js" ]
      },
    "default_popup": "popup.html",
    "default_title": "__MSG_name__",
    "content_scripts": [{
        "all_frames": true,
        "js": [ "name4.js", "name5.js", "name6.js" ],
        "match_about_blank": true,
        "matches": [ "http://*/*", "https://*/*" ],
        "run_at": "document_start"
      }, {
        "all_frames": true,
        "js": [ "include.postload.js" ],
        "match_about_blank": true,
        "matches": [ "http://*/*", "https://*/*" ],
        "run_at": "document_end"
      }]
  })"; 
  boost::property_tree::ptree pt;
  std::stringstream stream1(sample);
  boost::property_tree::read_json(stream1, pt);
  
  struct temp_fxn1 {
    //ref: basic_ptree public member functions
    static int ptree_type(const boost::property_tree::ptree &pt) {
      if (pt.size() > 0) {
        if (pt.begin()->first=="") {
          return 1;//array
        } else {
          return 2;//object (key : value)
        }
      } else {
        return 0;//leaf   
      }
    }
  };
    
  for (boost::property_tree::ptree::iterator it = pt.begin(); it != pt.end(); ++it) {
    auto &e = *it;
    printf("===>\n");
    std::cout << e.first << ", ";   // key of children of root node
    std::cout << e.second.get_value<std::string>() << ", ";  // get_value
    std::cout << temp_fxn1::ptree_type(e.second) << "\n";
    printf("~~~~>\n");
    for (auto &c : e.second) {
      std::cout << c.first << "\n";
    }
  }
}

void rxml() {
  boost::property_tree::ptree pt1;
  boost::property_tree::read_xml("../test1.xml", pt1);
   // Traverse property tree example
  BOOST_FOREACH(boost::property_tree::ptree::value_type const& node, pt1.get_child("purchaseOrder.items")) 
  {
    boost::property_tree::ptree subtree = node.second;  
     
    if (node.first == "item") 
    {
      BOOST_FOREACH(boost::property_tree::ptree::value_type const& v, subtree.get_child("")) 
      {
        std::string label = v.first;

        if (label != "<xmlattr>")
        {
          std::string value = subtree.get<std::string>(label);
          std::cout << label << ":  " << value << std::endl;
        }
      }
      std::cout << std::endl;
    }
  }
}

void wxml() {
  /*
  const std::string XML = 
		"<file>"
		  "<people>"
			"<person>"
			  "<forename>Andrew</forename>"
			  "<surname>Jones</surname>"
			"</person>"
			"<person>"
			  "<forename>David</forename>"
			  "<surname>Matthews</surname>"
			"</person>"
			"<person>"
			  "<forename>Jason</forename>"
			  "<surname>Perkins</surname>"
			"</person>"
		  "</people>"
		"</file>";
  boost::property_tree::ptree pt;

	// Put the XML string into a stringstream
	std::stringstream is;
	is << XML;

	// Read the stringstream into a Boost property tree, pt
	boost::property_tree::read_xml( is, pt );

	// Then write the Boost property tree to an output XML file
	//boost::property_tree::xml_writer_settings<char> w( ' ', 2 );  not support this
	//write_xml( "../output.xml", pt, std::locale(), w );
	boost::property_tree::write_xml( "../output.xml", pt );
  */

  boost::property_tree::ptree pt;

  pt.put("file_name", "boost_test");
  pt.put("debug_level", 3);
  pt.add("module_name", "os_stream");
  pt.add("module_name", "common");

  boost::property_tree::write_xml("../output.xml", pt);
}

void for_xml() {
  rxml();
  wxml();
}
