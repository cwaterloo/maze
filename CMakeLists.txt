cmake_minimum_required(VERSION 3.27.0)
project(maze VERSION 0.1.0 LANGUAGES C CXX)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(libmaze cell.h dual_value.h dual_value.cc maze.h path_finder.h path_finder.cc maze_drawer.h maze_drawer.cc)
add_executable(maze main.cc)

enable_testing()

add_executable(
  libmaze_test
  dual_value_test.cc
)
target_link_libraries(
  libmaze_test
  libmaze
)
target_link_libraries(
  libmaze_test
  GTest::gtest_main
)
target_link_libraries(
  maze
  libmaze
)

include(GoogleTest)
gtest_discover_tests(libmaze_test)
