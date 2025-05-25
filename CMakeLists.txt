cmake_minimum_required(VERSION 3.28)

file(READ "version.txt" APP_VERSION)

string(REGEX MATCH "([0-9]+)\\.([0-9]+)\\.([0-9]+)" VERSION_MATCH "${APP_VERSION}")
if(VERSION_MATCH)
    set(VERSION_MAJOR "${CMAKE_MATCH_1}")
    set(VERSION_MINOR "${CMAKE_MATCH_2}")
    set(VERSION_PATCH "${CMAKE_MATCH_3}")
endif()

set(VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})

project(
	ds
	VERSION ${VERSION}
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

set(DS_SOURCES
    src/node.cpp
)

set(DS_HEADERS
    include/iterable.h
    include/node.h
    include/constants.h
    include/property.h
)

add_library(ds SHARED ${DS_SOURCES} ${DS_HEADERS})

set_target_properties(ds PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib
    VERSION ${VERSION}
    SOVERSION ${VERSION_MAJOR}
)

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
  ds-unit-tests
  ${TEST_SOURCES}
  ${TEST_HEADERS}
)

target_link_libraries(
  ds-unit-tests
  GTest::gtest_main
  ds
)

target_compile_definitions(ds-unit-tests
    PRIVATE CMAKE_CURRENT_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}"
    PRIVATE ROOT_DIR="${ROOT_DIR}"
)

include(GoogleTest)
gtest_discover_tests(ds-unit-tests)

#
# Installation configuration
#

set(TOOL_DST "bin")
set(INCLUDE_DST "include/ds")
set(MAIN_LIB_DST "lib")

install(TARGETS ds DESTINATION "${MAIN_LIB_DST}")
install(FILES ${DS_HEADERS} DESTINATION "${INCLUDE_DST}")
