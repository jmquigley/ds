cmake_minimum_required(VERSION 3.31)

file(STRINGS "version.txt" APP_VERSION)
project(
	ds
	VERSION "${APP_VERSION}"
	DESCRIPTION "Data structures and algorithms implemented in C++"
	LANGUAGES CXX
)

message(STATUS "PROJECT_BINARY_DIR: ${PROJECT_BINARY_DIR}")
message(STATUS "PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")
message(STATUS "PROJECT_NAME: ${PROJECT_NAME}")
message(STATUS "PROJECT_VERSION: ${PROJECT_VERSION}")

# Setup memory testing parameters
set(MEMORYCHECK_COMMAND_OPTIONS "")
string(JOIN " " MEMORYCHECK_COMMAND_OPTIONS
    "--tool=memcheck"
    "--error-exitcode=1"
    "--leak-check=full"
    "--errors-for-leak-kinds=definite"
    "--show-leak-kinds=definite"
)
message(STATUS "MEMORYCHECK_COMMAND_OPTIONS: " ${MEMORYCHECK_COMMAND_OPTIONS})

set(CTEST_MEMORYCHECK_TYPE Valgrind)
set(CTEST_MEMORYCHECK_COMMAND valgrind)

# Adds all 3rd party dependencies to the project
include("CMakeLists.requirements.txt")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(HEADER_FILES /usr/include/c++/14 /usr/include/x86_64-linux-gnu/c++/14)
set(ROOT_DIR CMAKE_SOURCE_DIR)

include_directories(
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/tests
)

set(DS_SOURCES
    src/entry.cpp
    src/helpers.cpp
)

set(DS_HEADERS
    include/collection.hpp
    include/comparator.hpp
    include/ds.h
    include/constants.hpp
    include/helpers.hpp
    include/iterable.hpp
    include/iterator.hpp
    include/list.hpp
    include/node.hpp
    include/property.hpp
    include/stack.hpp
)

add_library(${PROJECT_NAME} SHARED ${DS_SOURCES} ${DS_HEADERS})

target_include_directories(${PROJECT_NAME}
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}
    ${LIBUUID_LIB}
)

target_sources(${PROJECT_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/ds.h
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)

#
# Setup testing environment
#

set(TEST_SOURCES
  tests/test_comparator.cpp
  tests/test_helpers.cpp
  tests/test_iterator.cpp
  tests/test_list.cpp
  tests/test_node.cpp
  tests/test_stack.cpp
)

set(TEST_HEADERS
  tests/testing_base.h
  tests/test_objects.h
)

add_executable(
  ds-unit-tests
  ${TEST_SOURCES}
  ${TEST_HEADERS}
)

target_link_libraries(ds-unit-tests
  GTest::gtest_main
  ${PROJECT_NAME}
)

target_compile_definitions(ds-unit-tests
    PRIVATE CMAKE_CURRENT_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}"
    PRIVATE ROOT_DIR="${ROOT_DIR}"
)

include(GoogleTest)
gtest_discover_tests(ds-unit-tests)

#
# Installation statements
#

install(FILES ${DS_HEADERS} DESTINATION "include/ds")
