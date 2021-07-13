#include <iostream>
#include "common/container.h"
#include "common/tools.h"
#include "stringutil/algo.h"
#include "stringutil/format.h"
#include "stringutil/regex.h"
#include "stringutil/tokenizer.h"
#include "os_stream/stream.h"
#include "os_stream/parser.h"
#include "flow/signal.h"
#include "flow/thread.h"

int main(int argc, char** argv) {
  std::cout << "************** common container **************" << std::endl;
  test_any();
  test_shared_ptr();
  test_optional();
  test_dy_bitset();
  test_logic_tri();
  test_unmap();
  test_multi_index();
  test_variant();
  
  std::cout << "************** common tools **************" << std::endl;
  test_lexical_cast();
  test_local_time();
  test_geometry();
  test_exception();
  test_error_code();

  std::cout << "************** stringutil **************" << std::endl;
  test_regex();
  test_format();
  test_algo();
  test_split();
  test_tokenizer();

  std::cout << "************** os_stream **************" << std::endl;
  test_filesystem(argv);
  test_iostream();
  test_program_option(argc, argv);

  for_json();
  for_xml();

  std::cout << "************** flow **************" << std::endl;
  test_thread();
  test_condthread();
  test_function();
  test_signal();

  return 0;
}

