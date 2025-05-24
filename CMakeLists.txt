cmake_minimum_required(VERSION 3.28)

project(
	ds
	VERSION 0.0.1
	DESCRIPTION "Data structures and algorithms implemented in C++"
	LANGUAGES CXX
)

# Adds all 3rd party dependencies to the project
include("CMakeLists.requirements.txt")

# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(CMAKE_LIBS_DIR ${CMAKE_SOURCE_DIR}/build/lib)
set(LIBRARY_OUTPUT_PATH ${CMAKE_LIBS_DIR})

set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(TESTING_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/tests)

include_directories("${PROJECT_INCLUDE_DIR}" "${TESTING_INCLUDE_DIR}")

set(COMMON_SOURCES
    src/node.cpp
)

set(COMMON_HEADERS
    include/iterable.h
    include/node.h
    include/constants.h
    include/property.h
)

add_library(ds SHARED ${COMMON_SOURCES} ${COMMON_HEADERS})

set_target_properties(ds PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

#
# Setup testing environment
#

set(TEST_SOURCES
  tests/test_node.cpp
)

set(TEST_HEADERS
  tests/testing_base.h
)

add_executable(
  ds_unit_tests
  ${TEST_SOURCES}
  ${TEST_HEADERS}
)

target_link_libraries(
  ds_unit_tests
  GTest::gtest_main
  ds
)

target_compile_definitions(ds_unit_tests
    PRIVATE CMAKE_CURRENT_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}"
    PRIVATE ROOT_DIR="${ROOT_DIR}"
)

include(GoogleTest)
gtest_discover_tests(ds_unit_tests)
