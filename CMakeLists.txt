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
option(DS_BUILD_LINT "Flag that turns on the lint processing" OFF)
option(DS_BUILD_ASAN "Flag that enables Address Sanitizer" OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(LLVM_VER 22)

# Adds all 3rd party dependencies to the project
include("CMakeLists.requirements.txt")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(TEST_FILTER $ENV{FILTER})

message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
message(STATUS "CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "CMAKE_INSTALL_INCLUDEDIR: ${CMAKE_INSTALL_INCLUDEDIR}")
message(STATUS "BUILD_TESTING: ${BUILD_TESTING}")
message(STATUS "DS_BUILD_EXTRAS: ${DS_BUILD_EXTRAS}")
message(STATUS "DS_BUILD_INSTALL: ${DS_BUILD_INSTALL}")
message(STATUS "DS_BUILD_LINT: ${DS_BUILD_LINT}")
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
    Buffer.hpp
    Collectable.hpp
    Collection.hpp
    Comparable.hpp
    constants.hpp
    cstr.h
    Deque.hpp
    ds.h
    GeneralTree.hpp
    GeneralTreeNode.hpp
    helpers.hpp
    List.hpp
    LRUCache.hpp
    Match.hpp
    Node.hpp
    OrderedSet.hpp
    Path.hpp
    PriorityQueue.hpp
    property.hpp
    Queue.hpp
    Replicate.hpp
    RingBuffer.hpp
    SortedList.hpp
    Stack.hpp
    str.h
    ThreadPool.hpp
    TreeNode.hpp
)

set(DS_SOURCES
    cstr.cpp
    entry.cpp
    helpers.cpp
    str.cpp
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
  $<$<CONFIG:Release>:-O3>
  $<$<CONFIG:Debug>:-O0>
  $<$<CONFIG:Debug>:-Wall>
  $<$<CONFIG:Debug>:-fprofile-instr-generate>
  $<$<CONFIG:Debug>:-fcoverage-mapping>
)

target_link_options(${PROJECT_NAME} PRIVATE
  $<$<CONFIG:Debug>:-fprofile-instr-generate>
)

target_include_directories(${PROJECT_NAME}
   PRIVATE ${GLOBAL_HEADER_DIRS}
   PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
   PUBLIC $<INSTALL_INTERFACE:include>
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE ${LIBUUID_LIB}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)

#
# Setup testing environment
#

if (DS_BUILD_TESTING)

# enable_testing()
# include(GoogleTest)

set(TEST_SOURCES
  tests/testing_base.h
  tests/test_binarytree.cpp
  tests/test_bitflag.cpp
  tests/test_buffer.cpp
  tests/test_comparable.cpp
  tests/test_cstr.cpp
  tests/test_deque.cpp
  tests/test_generaltree.cpp
  tests/test_generaltreenode.cpp
  tests/test_helpers.cpp
  tests/test_iterator.cpp
  tests/test_list.cpp
  tests/test_lrucache.cpp
  tests/test_match.cpp
  tests/test_node.cpp
  tests/test_orderedset.cpp
  tests/test_path.cpp
  tests/test_priorityqueue.cpp
  tests/test_queue.cpp
  tests/test_ringbuffer.cpp
  tests/test_sortedlist.cpp
  tests/test_stack.cpp
  tests/test_str.cpp
  tests/test_threadpool.cpp
  tests/test_treenode.cpp
)

string(CONCAT TEST_EXE ${PROJECT_NAME} "-unit-tests")

add_executable(
  ${TEST_EXE}
  ${TEST_SOURCES}
)

target_compile_options(${TEST_EXE} PRIVATE
  $<$<CONFIG:Release>:-O3>
  $<$<CONFIG:Debug>:-O0>
  $<$<CONFIG:Debug>:-Wall>
  $<$<CONFIG:Debug>:-fprofile-instr-generate>
  $<$<CONFIG:Debug>:-fcoverage-mapping>
)

target_link_options(${TEST_EXE} PRIVATE
  $<$<CONFIG:Debug>:-fprofile-instr-generate>
)

target_include_directories(${TEST_EXE}
  PRIVATE
  ${GLOBAL_HEADERS}
  ${CMAKE_CURRENT_SOURCE_DIR}/tests
)

target_link_libraries(${TEST_EXE}
  PRIVATE gtest
  PRIVATE GTest::gtest_main
  PRIVATE GTest::gmock
  ${PROJECT_NAME}
)

target_compile_definitions(${TEST_EXE}
    PRIVATE CMAKE_CURRENT_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}"
    TEST_SOURCE_DIR="${CMAKE_SOURCE_DIR}/tests"
    TEST_DATA_DIR="${CMAKE_SOURCE_DIR}/tests/resources"
)

# gtest_discover_tests(${TEST_EXE}
#     TEST_FILTER ${TEST_FILTER}
# )

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

add_executable(crtp extras/crtp.cpp)
target_link_libraries(crtp
    PRIVATE ${PROJECT_NAME}
)
target_include_directories(crtp PRIVATE ${PROJECT_NAME})


add_executable(dfs extras/dfs.cpp)
target_link_libraries(dfs
    PRIVATE ${PROJECT_NAME}
)
target_include_directories(dfs PRIVATE ${PROJECT_NAME})


add_executable(foo extras/foo.cpp)
target_link_libraries(foo
    PRIVATE ${PROJECT_NAME}
)
target_include_directories(foo PRIVATE ${PROJECT_NAME})


add_executable(inherit extras/inherit.cpp)
target_link_libraries(inherit
    PRIVATE ${PROJECT_NAME}
)
target_include_directories(inherit PRIVATE ${PROJECT_NAME})


add_executable(spaceship extras/spaceship.cpp)
target_link_libraries(spaceship
    PRIVATE ${PROJECT_NAME}
)
target_include_directories(spaceship PRIVATE ${PROJECT_NAME})


add_executable(typesizes extras/typesizes.cpp)
target_link_libraries(typesizes
    PRIVATE ${PROJECT_NAME}
)
target_include_directories(typesizes PRIVATE ${PROJECT_NAME})


endif(DS_BUILD_EXTRAS)
