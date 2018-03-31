cmake_minimum_required(VERSION 3.9)
project(simple-vm)

set(CMAKE_CXX_FLAGS "-std=c++14")

add_compile_options(-Wall)

add_executable (
  simple-vm
  stack/stack-vm.hpp
  stack/stack-vm.cpp
  main.cpp
  )
