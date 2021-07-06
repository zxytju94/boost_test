#include <iostream>
#include "os_stream/stream.h"
#include <boost/program_options.hpp>
#include "boost/iostreams/stream.hpp"
#include "boost/iostreams/device/file.hpp"
#include "boost/iostreams/filtering_stream.hpp"

void check_path(const char* p)
{
	boost::filesystem::path myPath(p);
	
	if(exists(myPath))
	{
		if(is_regular_file(myPath))
		{       //replace extension will replace the extension of the file with the given one, if not given, it will remove it   
			std::cout << "path " << myPath.filename().replace_extension() << " is a regular file of size " << boost::filesystem::file_size(myPath) << std::endl; 
		}
		else if(is_directory(myPath))
		{
			std::cout << "path " << myPath.filename() << " is a directory " << std::endl;
		}
	}
	else 
	{
		std::cout << "path " << myPath << " does not exist" << std::endl;
	}
}

void check_file(boost::filesystem::path p)
{
	auto s = boost::filesystem::status(p);
	auto t = s.type();

	std::cout << "the type is " << t << std::endl;

	auto ps = s.permissions();
	if ((ps & boost::filesystem::owner_write) != boost::filesystem::owner_write)
	{
		std::cout << "no permissions t o write " << std::endl;
	}
}


void dir_nav(boost::filesystem::path dir)
{
	using it = boost::filesystem::directory_iterator;
	it end;
	for(it i(dir); i != end; ++i)
	{
		auto p = i -> path();
		if(is_regular_file(p))
		{
			std::cout << p.filename() << std::endl;
		}
		else if(is_directory(p))
		{
			std::cout << "directory " << p.filename() << "==================================" << std::endl;
			dir_nav(p); 
		}
	}	
}


void test_filesystem(char** argv) {
  //labtools LTDHWDevice::getProbesFilePathStrings
  /*
  boost::filesystem::path old_cpath = boost::filesystem::current_path();
  boost::filesystem::file_status status = boost::filesystem::detail::status(old_cpath, 0);
  if (status.type() <= 1) {
    std::cout << "file status is wrong!" << std::endl;
    if (status.type() == 1) {
      std::cout << "file_status is 1" << std::endl;
    } else {
      std::cout << "file_status is 0" << std::endl;
    }
  } else {
    std::cout << "file_status is " << status.type() << std::endl;
  }
  */
	check_path("foo");
	check_path(argv[0]);
	
	// getting the parent directory
	auto dir = boost::filesystem::path(argv[0]).parent_path();	
	check_path(dir.string().c_str());

	// decompostition
	for (auto & child : dir)
	{
		std::cout << child << std::endl;
	}

	// catching filesystem exceptions
	try
	{
		boost::filesystem::path p("junk");
		std::cout << boost::filesystem::file_size(p) << std::endl;
	}
	catch (const boost::filesystem::filesystem_error & e)
	{
		std::cout << e.what() << std::endl; 
	}
	
	check_file(boost::filesystem::path(argv[0]));

	auto parent = boost::filesystem::path(argv[0]).parent_path().parent_path();

	// dir_nav(parent);
}

void test_iostream() {
//  XHWBinDataReader::readFile
  boost::iostreams::filtering_stream<boost::iostreams::input_seekable> data_stream_in;
  bool is_open = false;

  std::string default_path = "/export/home1/user/xyzhang/workspace/mycpp/second.cc";
  boost::iostreams::file_source source(default_path, BOOST_IOS::ate); //2

  data_stream_in.push(source);
  //if (data_stream_in.is_complete() & 1) {
  //  std::logic_error("chain complete");
  //}
  //

  boost::iostreams::stream_buffer<boost::iostreams::file_source> buffer;
  /*  TODO source is wrong
  data_stream_in.push(buffer);
  if (buffer.is_open() & 1) {
    std::iostream_category();
    std::ios_base::failure("already open");
  }
  */
}

void test_program_option(int argc, char** argv) {
  namespace po = boost::program_options;

	//INSTEAD OF GETTING VALUE, WE DIRECTLY STORE IT
	int value;

	po::options_description desc("Program options");
	desc.add_options()
		("help,h", "print info")
		("filename,F", po::value<std::string>() -> default_value("default.txt"), "file to process")
		("value,v", po::value<int>(&value) -> default_value(42))
		("files,f", po::value<std::vector<std::string>>() -> multitoken(), "input files");

	po::variables_map vm;
	//parse the command line 	
	auto parsed = po::parse_command_line(argc, argv, desc);

	//store the data in variable map
	po::store(parsed, vm);
	
	po::notify(vm);
	
	if(vm.count("help"))
	{
		std::cout << desc << std::endl;
	}

	std::string filename = vm["filename"].as<std::string>();
	
	if(vm.count("files"))
	{
		int i = 0;
		auto files = vm["files"].as<std::vector<std::string>>();
		for( auto s : files)
		{
			std::cout << ++i << ":" << s << std::endl;
		}
	}

	std::cout << "Processing filename : " << filename << std::endl;
	std::cout << "The value is " << value << std::endl;
	std::cout << "Done " << std::endl;	
}

