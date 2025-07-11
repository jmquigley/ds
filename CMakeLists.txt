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
set(HEADER_FILES /usr/include/c++/14 /usr/include/x86_64-linux-gnu/c++/14)
set(ROOT_DIR CMAKE_SOURCE_DIR)
set(TEST_FILTER $ENV{FILTER})

message(STATUS "TEST_FILTER: ${TEST_FILTER}")

include_directories(
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/tests
)

set(DS_SOURCES
    src/BaseBitFlag.hpp
    src/BaseIterator.hpp
    src/BaseNodeBuilder.hpp
    src/BaseNode.hpp
    src/BaseTree.hpp
    src/BinaryTree.hpp
    src/Collection.hpp
    src/Comparator.hpp
    src/constants.hpp
    src/cstr.cpp
    src/cstr.h
    src/Deque.hpp
    src/ds.h
    src/entry.cpp
    src/helpers.cpp
    src/helpers.hpp
    src/Iterable.hpp
    src/List.hpp
    src/Match.hpp
    src/Node.hpp
    src/PriorityQueue.hpp
    src/property.hpp
    src/Queue.hpp
    src/SortedList.hpp
    src/Stack.hpp
    src/TreeNode.hpp
)

add_library(${PROJECT_NAME} SHARED ${DS_SOURCES})

target_compile_options(${PROJECT_NAME} PRIVATE
  $<$<CONFIG:Debug>:-g>
  $<$<CONFIG:Debug>:-O0>
  $<$<CONFIG:Debug>:-Wall>
  $<$<CONFIG:Debug>:--coverage>
)

target_link_options(${PROJECT_NAME} PRIVATE
  $<$<CONFIG:Debug>:--coverage>
)

target_include_directories(${PROJECT_NAME}
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}
    ${LIBUUID_LIB}
)

target_sources(${PROJECT_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/ds.h
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)

#
# Setup testing environment
#

set(TEST_SOURCES
  tests/testing_base.h
  tests/test_binarytree.cpp
  tests/test_bitflag.cpp
  tests/test_comparator.cpp
  tests/test_cstr.cpp
  tests/test_deque.cpp
  tests/test_helpers.cpp
  tests/test_iterator.cpp
  tests/test_list.cpp
  tests/test_node.cpp
  tests/test_priorityqueue.cpp
  tests/test_queue.cpp
  tests/test_sortedlist.cpp
  tests/test_stack.cpp
  tests/test_treenode.cpp
)

string(CONCAT TEST_EXE ${PROJECT_NAME} "-unit-tests")

add_executable(
  ${TEST_EXE}
  ${TEST_SOURCES}
)

target_compile_options(${TEST_EXE} PRIVATE
  $<$<CONFIG:Debug>:-O0>
  $<$<CONFIG:Debug>:-Wall>
  $<$<CONFIG:Debug>:-coverage>
)

target_link_options(${TEST_EXE} PRIVATE
  $<$<CONFIG:Debug>:-coverage>
)

target_link_libraries(${TEST_EXE}
  gtest
  GTest::gtest_main
  GTest::gmock
  ${PROJECT_NAME}
)

target_compile_definitions(${TEST_EXE}
    PRIVATE CMAKE_CURRENT_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}"
    PRIVATE ROOT_DIR="${ROOT_DIR}"
)

include(GoogleTest)

gtest_discover_tests(${TEST_EXE}
    TEST_FILTER ${TEST_FILTER}
)

#
# Installation statements
#

install(FILES ${DS_HEADERS} DESTINATION "include/${PROJECT_NAME}")

#
# Extras
#

add_executable(typesizes extras/typesizes.cpp)
target_link_libraries(typesizes
    PRIVATE ${PROJECT_NAME}
)
target_include_directories(typesizes PRIVATE ${PROJECT_NAME})

add_executable(inherit extras/inherit.cpp)
target_link_libraries(inherit
    PRIVATE ${PROJECT_NAME}
)
target_include_directories(inherit PRIVATE ${PROJECT_NAME})

add_executable(crtp extras/crtp.cpp)
target_link_libraries(crtp
    PRIVATE ${PROJECT_NAME}
)
target_include_directories(crtp PRIVATE ${PROJECT_NAME})
