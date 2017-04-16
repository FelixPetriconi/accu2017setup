PROJECT(SetupNanaTest)

set(SOURCE
  main.cpp
)

set(HEADERS
)

add_executable(SetupNanaTest ${SOURCE} ${HEADERS})

include_directories(${Boost_INCLUDE_DIRS})

target_link_libraries(
    SetupNanaTest
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_THREAD_LIBRARY}
    ${CMAKE_THREAD_LIBS_INIT}
    nana)

set_property(TARGET SetupNanaTest PROPERTY CXX_STANDARD 14)
set_property(TARGET SetupNanaTest PROPERTY CXX_STANDARD_REQUIRED ON)
