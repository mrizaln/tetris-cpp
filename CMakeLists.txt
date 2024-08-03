cmake_minimum_required(VERSION 3.23)
project(tetris-cpp VERSION 0.0.1)

include(cmake/prelude.cmake)
include(cmake/mold.cmake)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(fmt REQUIRED)

# include(cmake/fetched-libs.cmake)

# add_subdirectory(lib)

add_executable(main source/main.cpp)
target_include_directories(main PRIVATE source)
target_link_libraries(main PRIVATE fmt::fmt)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(main PRIVATE -Wall -Wextra -Wconversion -Wswitch-enum)

  # sanitizer
  target_compile_options(main PRIVATE -fsanitize=address,leak,undefined)
  target_link_options(main PRIVATE -fsanitize=address,leak,undefined)

elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_options(main PRIVATE /W4)

  # sanitizer
  target_compile_options(main PRIVATE /fsanitize=address)
  target_link_options(main PRIVATE /fsanitize=address)
endif()
