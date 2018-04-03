cmake_minimum_required(VERSION 3.9)
project(sasm)

find_package(FLEX)
find_package(BISON)
BISON_TARGET(SASMPARSER parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.c
  DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.h)

FLEX_TARGET(SASMTOKENIZER lexer.lex ${CMAKE_CURRENT_BINARY_DIR}/lexer.c
  DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/lexer.h)

ADD_FLEX_BISON_DEPENDENCY(SASMTOKENIZER SASMPARSER)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_custom_target(
  MV_COMMAND_FILES
  COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/command.* ${CMAKE_CURRENT_SOURCE_DIR}/build
  )

add_executable(
  sasm
  main.c
  command.h
  command.c
  data/list.c
  data/list.h
  ${FLEX_SASMTOKENIZER_OUTPUTS}
  ${BISON_SASMPARSER_OUTPUTS}
  )

add_dependencies(sasm MV_COMMAND_FILES)
