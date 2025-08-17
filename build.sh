#!/usr/bin/env -S bash -l

#
# A thin wrapper script used to call cmake commands and build the application.
# The basic build is a single command that will build the release version:
#
#     ./build.sh
#
# To build a debug version, run the unit tests, and build development
# documentation use:
#
#     ./build.sh --debug
#
# To only run a specific unit test case suite use:
#
#     ./build.sh --debug --filter='TestBinaryTree*'
#
# To build and run unit tests, but skip all documentation and installation
# processes use:
#
#     ./build.sh --debug --nodocs --noinstall
#
# To change the number of parallel jobs used to build the project use:
#
#     ./build.sh --jobs=15
#
# To run a debug build while cleaning up all previous artifacts and forcing
# a full rebuild use the clean flag:
#
#     ./build.sh --debug --clean
#
function exitOnError() {
    if [ $1 -ne 0 ]; then
        echo $2
        exit 255
    fi
}

function banner() {
   MSG=$1
   FIGLET_OPTS=-c

   if ! [ -x "$(command -v figlet)" ]; then
       echo "****************************************"
       echo ${MSG}
       echo "****************************************"
   else
       figlet ${FIGLET_OPTS} ${MSG}
   fi
}

SCRIPT_DIR=$(dirname "${BASH_SOURCE[0]}")
BUILD_TYPE=Release
CLEAN_OPT=0
LINT_OPT=0
LLVM_VERSION=21
MEMTEST_OPT=0
NOCOVERAGE_OPT=0
NODOCS_OPT=0
NOINSTALL_OPT=0
NOTEST_OPT=0
PREFIX=${SCRIPT_DIR}
TEST_EXE=./ds-unit-tests
USE_CLANG=0
export GTEST_SHUFFLE=1
export FILTER='*'
export THREADS=10

while :; do
    echo "Processing parameters: $1"
    case $1 in

        -c|--clean)
            CLEAN_OPT=1
            shift
            ;;

        --debug)
            BUILD_TYPE=Debug
            shift
            ;;

        -f|--filter)
            if [ -n "$2" ]; then
                FILTER="$2"
                shift 2
            else
                printf 'ERROR: "--filter" requires a non-empty option argument.\n' >&2
                exit 127
            fi
            ;;

        --filter=?*)
            FILTER=${1#*=}
            shift
            ;;

        -j|--jobs)
            if [ -n "$2" ]; then
                THREADS="$2"
                shift 2
            else
                printf 'ERROR: "--jobs" requires a non-empty option argument.\n' >&2
                exit 127
            fi
            ;;

        --jobs=?*)
            THREADS=${1#*=}
            shift
            ;;

        --lint)
            LINT_OPT=1
            shift
            ;;

        # performs a full valgrind memcheck on all test cases.  This option
        # is very slow.
        --memtest|--memcheck)
            MEMTEST_OPT=1;
            shift
            ;;

        --nocoverage)
            NOCOVERAGE_OPT=1;
            shift
            ;;

        --nodocs)
            NODOCS_OPT=1
            shift
            ;;

        --noinstall)
            NOINSTALL_OPT=1;
            shift
            ;;

        --notest|--notesting)
            NOTEST_OPT=1
            shift
            ;;

        -p|--prefix)
            if [ -n "$2" ]; then
                PREFIX="$2"
                shift 2
            else
                printf 'ERROR: "--prefix" requires a non-empty option argument.\n' >&2
                exit 127
            fi
            ;;

        --prefix=?*)
            PREFIX=${1#*=}
            shift
            ;;

        *) # Default case: If no more options then break out of the loop.
            break
    esac
done

echo "Building dt API library from ${SCRIPT_DIR}"

[[ ! -d "build" ]] && mkdir -p build

pushd build

# Make build type decisions
if [[ "${BUILD_TYPE}" == "Release" ]]; then
    BUILD_TYPE=Release
    USE_TESTING=OFF
    USE_EXTRAS=OFF
else
    BUILD_TYPE=Debug

    if [ ${NOTEST_OPT} == 1 ]; then
        USE_TESTING=OFF
    else
        USE_TESTING=ON
    fi

    if [ ${LINT_OPT} == 1 ]; then
        USE_LINT=ON
    fi

    USE_EXTRAS=ON
fi

USE_INSTALL=ON
if [ ${NOINSTALL_OPT} == 1 ]; then
    USE_INSTALL=OFF
fi

banner ${BUILD_TYPE}

if [ ${CLEAN_OPT} == 1 ] && [ -f "Makefile" ]; then
    banner "Cleaning"
    cmake --build . -v --target clean
fi

#
# Building code with CMake
#

banner "Building"
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=${BUILD_TYPE} -DDS_BUILD_EXTRAS=${USE_EXTRAS} -DDS_BUILD_TESTING=${USE_TESTING} -DDS_BUILD_INSTALL=${USE_INSTALL} -DDS_BUILD_LINT=${USE_LINT} -DBUILD_TESTING=${USE_TESTING} ..
exitOnError $? "Failed to create cmake build files!"

cmake --build . -v -- -j ${THREADS}
exitOnError $? "Error building project, terminating"

#
# Testing
#

if [ "${USE_TESTING}" == "ON" ]; then

    banner "Testing"
    if [ ${MEMTEST_OPT} == 1 ]; then
        cmake -E env FILTER=${FILTER} ctest -T memcheck --output-on-failure -j ${THREADS} --output-log ./log/unit-tests.log
        rc=$?
        if [ $rc -ne 0 ] && [ ${MEMTEST_OPT} == 1 ]; then
            cat Testing/Temporary/MemoryChecker.*.log
        fi

    else
        eval ${TEST_EXE}
        rc=$?
    fi

    exitOnError $rc "Error executing unit tests, terminating"
fi

#
# Creating coverage information
#

if [ "${USE_TESTING}" == "ON" ] && [ ${NOCOVERAGE_OPT} == 0 ]; then
    # NOTE: this coverage only works correctly when the google test suite is
    # is run outside of ctest.  If used with ctest, then only the last suite
    # executed will be included in the coverage data

    banner "Coverage"
    COVERAGE_OUTPUT=./docs/html/coverage

    SRC_FILES=`find ../src -type f -print0 | xargs -0 echo`
    IGNORE=-ignore-filename-regex='.*/tests/.*'
    INSTFILE=-instr-profile=default.profdata

    # Create profile data
    llvm-profdata-${LLVM_VERSION} merge -sparse default.profraw -o default.profdata

    # Take all coverage data and export to a JSON file
    llvm-cov-${LLVM_VERSION} export ${IGNORE} --format=text ${INSTFILE} ${TEST_EXE}  > coverage.json

    if command -v jq &> /dev/null; then
        # Parse the JSON coverage data and show all files that are used
        # if the jq command is available
        echo "Files included:"
        jq -r '.data[0].files[].filename' coverage.json
        echo ""
    fi

    # Create build output for display during the build and also create an
    # output HTML site to include with documentation.
    llvm-cov-${LLVM_VERSION} show ${IGNORE} ${TEST_EXE} ${INSTFILE} ${SRC_FILES} --format html -output-dir=${COVERAGE_OUTPUT}
    llvm-cov-${LLVM_VERSION} report ${IGNORE} ${TEST_EXE} ${INSTFILE}
fi


#
# Installation
#

if [ "${USE_INSTALL}" == "ON" ]; then
    banner "Installation"
    cmake --install . --prefix=${PREFIX}
    exitOnError $? "Error installing project, terminating"
fi

#
# Building documentation
#

if [ "${USE_EXTRAS}" == "ON" ] && [ ${NODOCS_OPT} == 0 ]; then
    banner "Documentation"

    # Build the sphinx documention
    pushd ../docs
    make html
    exitOnError $? "Error creating project documentation, terminating"
    popd

    # Copy the doxygen documentation
    pushd doxygen
    yes | cp -rf html/ ../docs/html/doxygen
    popd

    if [ -d /var/www/html ]; then
        yes | cp -rf docs/html/* /var/www/html/.
        chmod -R 755 /var/www
    fi
fi

popd
