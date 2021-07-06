#include <iostream>
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "flow/signal.h"


boost::mutex mtx;
boost::condition_variable cv;
bool ready = false;

void test_thread() {
  int x = 5;
  boost::thread th1(TestAddFunc::print_sth, std::ref(x), "hello boost");
  boost::thread th2(TestAddFunc::print_sth, std::ref(x), "hello thread");
  th1.join();
  th2.detach();
  boost::posix_time::time_duration tm(0,0,3,765); 
  boost::this_thread::sleep(tm);
  // th1.timed_join(boost::posix_time::seconds(3));
}

void print_id (int id) {
  boost::mutex::scoped_lock lock(mtx);
  std::cout << "sub_thread_id = " << boost::this_thread::get_id() << std::endl;
  while (!ready) cv.wait(lock);
  // ...
  std::cout << "thread " << id << '\n';
}

void go() {
  boost::mutex::scoped_lock lock(mtx);
  ready = true;
  cv.notify_all();
}

void test_condthread() {
  boost::thread threads[10];
  // spawn 10 threads:
  for (int i=0; i<10; ++i)
    threads[i] = boost::thread(print_id,i);

  std::cout << "main_thread_id = " << boost::this_thread::get_id() << std::endl;
  std::cout << "10 threads ready to race...\n";
  go(); 

  for (auto& th : threads) 
    th.join();
}

