cmake_minimum_required (VERSION 3.3)

project(boost_test)
set(CMAKE_C_COMPILER "/home/fpga/lib/gcc-5.4.0/bin/gcc")
set(CMAKE_CXX_COMPILER "/home/fpga/lib/gcc-5.4.0/bin/g++")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")  # add all signal table
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O2 -Wall")

set(PROJECT_ROOT_PATH "${CMAKE_SOURCE_DIR}")  
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_ROOT_PATH}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_ROOT_PATH}/lib)
LINK_DIRECTORIES("${PROJECT_ROOT_PATH}/lib/")

set(BOOST_ROOT "/home/fpga/lib/boost_1_64_0")
set(Boost_NO_SYSTEM_PATHS ON)

find_package(Boost REQUIRED COMPONENTS
  thread
  regex
  filesystem
  date_time
  program_options
)
 
if(NOT Boost_FOUND)
  message("NOT found Boost")
endif()

if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS}
      ${PROJECT_SOURCE_DIR}/include)
  
  MESSAGE( STATUS "Boost_INCLUDE_DIRS = ${Boost_INCLUDE_DIRS}.")
  MESSAGE( STATUS "Boost_LIBRARIES = ${Boost_LIBRARIES}.")
  MESSAGE( STATUS "Boost_LIB_VERSION = ${Boost_LIB_VERSION}.")
  
  add_subdirectory(src)

  add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/src/main.cc)
  target_link_libraries (${PROJECT_NAME}
    stringutil
    common
    os_stream
    flow
    ${Boost_LIBRARIES})
else()
  MESSAGE( WARNING "Not found Boost")
endif()
