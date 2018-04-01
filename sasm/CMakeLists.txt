cmake_minimum_required(VERSION 3.9)
project(simple-vm)

set(CMAKE_CXX_FLAGS "-std=c++14")

add_compile_options(-Wall)

file(GLOB_RECURSE
  ALL_CXX_SOURCE_FILES
  *.[chi]pp *.[chi]xx *.cc *.hh *.ii *.[CHI]
  )

# Adding clang-format target if executable is found
find_program(CLANG_FORMAT "clang-format")
if(CLANG_FORMAT)
  add_custom_target(
    clang-format
    COMMAND /usr/bin/clang-format
    -i
    -style=Google
    ${ALL_CXX_SOURCE_FILES}
    )
endif()

add_executable (
  sasm
  lexer.hpp
  lexer.cpp
  sasm.cpp
  )
