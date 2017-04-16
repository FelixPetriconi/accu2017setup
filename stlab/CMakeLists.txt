project(stlab C CXX)

set(HEADERS
  channel.hpp
  config.hpp
  default_executor.hpp
  executor_base.hpp
  expected.hpp
  future.hpp
  immediate_executor.hpp
  main_executor.hpp
  progress.hpp
  traits.hpp
  tuple_algorithm.hpp
  system_timer.hpp
  utility.hpp)

include_directories(${Boost_INCLUDE_DIRS})

add_library(stlab INTERFACE)

target_sources(stlab INTERFACE ${HEADERS})

