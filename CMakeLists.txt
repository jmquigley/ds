cmake_minimum_required(VERSION 3.31)

file(STRINGS "version.txt" APP_VERSION)
project(
	ds
	VERSION "${APP_VERSION}"
	DESCRIPTION "Data structures and algorithms implemented in C++"
	LANGUAGES CXX
)

option(DS_BUILD_EXTRAS "Flag to build extra testing programs" OFF)
option(DS_BUILD_TESTING "Flag to build and run unit testing" OFF)
option(DS_BUILD_INSTALL "Flag that performs the install proces" ON)

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
# set(CMAKE_C_COMPILER "clang")
# set(CMAKE_CXX_COMPILER "clang++")
set(HEADER_FILES /usr/include/c++/14 /usr/include/x86_64-linux-gnu/c++/14)
set(ROOT_DIR CMAKE_SOURCE_DIR)
set(TEST_FILTER $ENV{FILTER})

message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
message(STATUS "CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "CMAKE_INSTALL_INCLUDEDIR: ${CMAKE_INSTALL_INCLUDEDIR}")
message(STATUS "BUILD_TESTING: ${BUILD_TESTING}")
message(STATUS "DS_BUILD_EXTRAS: ${DS_BUILD_EXTRAS}")
message(STATUS "DS_BUILD_INSTALL: ${DS_BUILD_INSTALL}")
message(STATUS "DS_BUILD_TESTING: ${DS_BUILD_TESTING}")
message(STATUS "PROJECT_BINARY_DIR: ${PROJECT_BINARY_DIR}")
message(STATUS "PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")
message(STATUS "PROJECT_NAME: ${PROJECT_NAME}")
message(STATUS "PROJECT_VERSION: ${PROJECT_VERSION}")
message(STATUS "TEST_FILTER: ${TEST_FILTER}")
message(STATUS "INSTALL_GTEST: ${INSTALL_GTEST}")

set(DS_INCLUDES
    BaseBitFlag.hpp
    BaseIterator.hpp
    BaseNodeBuilder.hpp
    BaseNode.hpp
    BaseTree.hpp
    BinaryTree.hpp
    Collection.hpp
    Comparator.hpp
    constants.hpp
    cstr.h
    Deque.hpp
    ds.h
    GeneralTree.hpp
    GeneralTreeNode.hpp
    helpers.hpp
    Iterable.hpp
    List.hpp
    Match.hpp
    Node.hpp
    PriorityQueue.hpp
    property.hpp
    Queue.hpp
    SortedList.hpp
    Stack.hpp
    TreeNode.hpp
)

set(DS_SOURCES
    cstr.cpp
    entry.cpp
    helpers.cpp
)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/${PROJECT_NAME}/)
list(TRANSFORM DS_INCLUDES PREPEND ${SRC_DIR})
list(TRANSFORM DS_SOURCES PREPEND ${SRC_DIR})

add_library(${PROJECT_NAME} SHARED)

target_sources(${PROJECT_NAME}
    PRIVATE ${DS_SOURCES}
    PUBLIC ${DS_INCLUDES}
)

target_compile_options(${PROJECT_NAME} PRIVATE
  $<$<CONFIG:Debug>:-O0>
  $<$<CONFIG:Debug>:-Wall>
  $<$<CONFIG:Debug>:--coverage>
)

target_link_options(${PROJECT_NAME} PRIVATE
  $<$<CONFIG:Debug>:--coverage>
)

target_include_directories(${PROJECT_NAME}
   PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
   PUBLIC $<INSTALL_INTERFACE:include>
)

target_link_libraries(${PROJECT_NAME}
    ${LIBUUID_LIB}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)

#
# Setup testing environment
#

if (DS_BUILD_TESTING)

set(TEST_SOURCES
  tests/testing_base.h
  tests/test_binarytree.cpp
  tests/test_bitflag.cpp
  tests/test_comparator.cpp
  tests/test_cstr.cpp
  tests/test_deque.cpp
  tests/test_generaltree.cpp
  tests/test_generaltreenode.cpp
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

target_include_directories(${TEST_EXE}
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/tests
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
)

include(GoogleTest)

gtest_discover_tests(${TEST_EXE}
    TEST_FILTER ${TEST_FILTER}
)

endif(DS_BUILD_TESTING)

#
# Installation statements
#

if (DS_BUILD_INSTALL)

install(FILES ${DS_INCLUDES} DESTINATION "include/${PROJECT_NAME}")
install(TARGETS ${PROJECT_NAME} DESTINATION lib)

endif(DS_BUILD_INSTALL)

#
# Extras
#

if (DS_BUILD_EXTRAS)

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

endif(DS_BUILD_EXTRAS)
