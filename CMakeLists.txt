cmake_minimum_required(VERSION 3.23)
project(tetris-cpp VERSION 0.0.1)

include(cmake/prelude.cmake)
include(cmake/mold.cmake)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SFML REQUIRED)
find_package(asio REQUIRED)
find_package(magic_enum REQUIRED)
find_package(spdlog REQUIRED)
find_package(tl-expected REQUIRED)

# the tetris game
add_library(tet OBJECT source/tet/tetris.cpp source/tet/game_state.cpp
                       source/tet/renderer.cpp source/tet/block.cpp)
target_include_directories(tet PUBLIC source)
target_link_libraries(tet PUBLIC asio::asio sfml::sfml spdlog::spdlog
                                 tl::expected magic_enum::magic_enum)

function(compile name source)
  add_executable(${name} ${source})
  target_link_libraries(${name} PRIVATE tet)

  if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${name} PRIVATE -Wall -Wextra -Wconversion)

    # sanitizer target_compile_options(${name} PRIVATE
    # -fsanitize=address,leak,undefined) target_link_options(${name} PRIVATE
    # -fsanitize=address,leak,undefined)

  elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(${name} PRIVATE /W4)

    # sanitizer
    # ~~~
    # target_compile_options(${name} PRIVATE /fsanitize=address)
    # target_link_options(${name} PRIVATE /fsanitize=address)
  endif()
endfunction()

# the main executable
compile(main source/main.cpp)

# block test
compile(block_test test/block_test.cpp)
