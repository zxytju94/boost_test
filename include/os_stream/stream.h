#ifndef STREAM_H
#define STREAM_H

#include <iostream>
#include <boost/filesystem.hpp>

void check_path(const char* );
void check_file(boost::filesystem::path);
void dir_nav(boost::filesystem::path dir);


void test_filesystem(char**);
void test_iostream();
void test_program_option(int, char**);

#endif
