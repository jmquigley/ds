cmake_minimum_required(VERSION 3.28)

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

# Adds all 3rd party dependencies to the project
include("CMakeLists.requirements.txt")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")
set(HEADER_FILES /usr/include/c++/14 /usr/include/x86_64-linux-gnu/c++/14)
set(ROOT_DIR CMAKE_SOURCE_DIR)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/lib)

include_directories(
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/tests
)

set(DS_SOURCES
    src/collection.cpp
    src/stack.cpp
)

set(DS_HEADERS
    include/collection.h
    include/comparator.h
    include/constants.h
    include/iterable.h
    include/node.h
    include/property.h
    include/stack.h
)

add_library(${PROJECT_NAME} SHARED ${DS_SOURCES} ${DS_HEADERS})

target_link_libraries(${PROJECT_NAME}
    ${LIBUUID_LIB}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)

install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

#
# Setup testing environment
#

set(TEST_SOURCES
  tests/test_node.cpp
)

set(TEST_HEADERS
  tests/testing_base.h
  tests/test_node.h
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

# #
# # Installation configuration
# #

# # set(TOOL_DST "bin")
# # set(INCLUDE_DST "include/ds")
# # set(MAIN_LIB_DST "lib")

# # install(TARGETS ds DESTINATION "${MAIN_LIB_DST}")
# # install(FILES ${DS_HEADERS} DESTINATION "${INCLUDE_DST}")
