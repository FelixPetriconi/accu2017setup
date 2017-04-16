PROJECT(SetupStlabTest)

set(SOURCE
  main.cpp
)

set(HEADERS
)

add_executable(SetupStlabTest ${SOURCE} ${HEADERS})

include_directories(${Boost_INCLUDE_DIRS})

target_link_libraries(
    SetupStlabTest
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_THREAD_LIBRARY}
    ${CMAKE_THREAD_LIBS_INIT})

set_property(TARGET SetupStlabTest PROPERTY CXX_STANDARD 14)
set_property(TARGET SetupStlabTest PROPERTY CXX_STANDARD_REQUIRED ON)
