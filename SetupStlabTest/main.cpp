#include <stlab/future.hpp>
#include <stlab/default_executor.hpp>

#include <iostream>

using namespace stlab;

int main() {
  auto f = stlab::async(default_executor, []{ return 42; } );
  
  while (!f.get_try()) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
  
  std::cout << f.get_try().value() << '\n';
}

