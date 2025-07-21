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
CLEAN_OPT=0
MEMTEST_OPT=0
NODOCS_OPT=0
NOINSTALL_OPT=0
NOTEST_OPT=0
BUILD_TYPE=Release
PREFIX=${SCRIPT_DIR}
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

        # performs a full valgrind memcheck on all test cases.  This option
        # is very slow.
        --memtest|--memcheck)
            MEMTEST_OPT=1;
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
cmake -DCMAKE_BUILD_TYPE=${BUILD_TYPE} -DDS_BUILD_EXTRAS=${USE_EXTRAS} -DDS_BUILD_TESTING=${USE_TESTING} -DDS_BUILD_INSTALL=${USE_INSTALL} -DBUILD_TESTING=${USE_TESTING} ..
exitOnError $? "Failed to create cmake build files!"

cmake --build . -v -- -j ${THREADS}
exitOnError $? "Error building project, terminating"

#
# Testing
#

if [ "${USE_TESTING}" == "ON" ]; then

    banner "Testing"
    MEMCHECK=''
    if [ ${MEMTEST_OPT} == 1 ]; then
        MEMCHECK='-T memcheck'
    fi

    cmake -E env FILTER=${FILTER} ctest ${MEMCHECK} --output-on-failure -j ${THREADS} --output-log ./log/unit-tests.log
    rc=$?
    if [ $rc -ne 0 ] && [ ${MEMTEST_OPT} == 1 ]; then
        cat Testing/Temporary/MemoryChecker.*.log
    fi
    exitOnError $rc "Error executing unit tests, terminating"

fi

#
# Creating coverage information
#

if [ "${USE_TESTING}" == "ON" ]; then
    banner "Coverage"
    lcov --capture --directory . --output-file coverage.info --ignore-errors mismatch,mismatch --ignore-errors gcov,gcov
    lcov --quiet --remove coverage.info '/usr/*' --remove coverage.info '*test*' --output-file coverage.info
    genhtml coverage.info -q --demangle-cpp --output-directory docs/html/coverage
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
    fi
fi

popd
