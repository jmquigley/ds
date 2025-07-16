#!/usr/bin/env -S bash -l

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
BUILD_DOCS=0
RUN_TESTS=0
NOMEM_OPT=0
BUILD_TYPE=Release
PREFIX=${SCRIPT_DIR}
export GTEST_SHUFFLE=1
export FILTER=''
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
            FILTER='*'
            shift
            ;;

        -d|--docs)
            BUILD_DOCS=1
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

        --nomem)
            NOEM_OPT=1
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

        -t|--testing)
            RUN_TESTS=1
            shift
            ;;

        *) # Default case: If no more options then break out of the loop.
            break
    esac
done

echo "Building dt API library from ${SCRIPT_DIR}"

[[ ! -d "build" ]] && mkdir -p build

pushd build

if [[ "${BUILD_TYPE}" == "Release" ]]; then
    BUILD_TYPE=Release
else
    BUILD_TYPE=Debug
fi
banner ${BUILD_TYPE}


if [ ${CLEAN_OPT} == 1 ]; then
    banner "Cleaning"
    cmake --build . -v --target clean
fi

#
# Building code with CMake
#

banner "Building"

cmake -DCMAKE_BUILD_TYPE=${BUILD_TYPE} ..
exitOnError $? "Failed to create cmake build files!"

cmake --build . -v -- -j ${THREADS}
exitOnError $? "Error building project, terminating"

#
# Testing
#

if [ ${RUN_TESTS} == 1 ]; then

    banner "Testing"
    MEMCHECK='-T memcheck'
    if [ ${NOMEM_OPT} == 1 ]; then
        MEMCHECK=''
    fi

    cmake -E env FILTER=${FILTER} ctest ${MEMCHECK} --output-on-failure -j ${THREADS} --output-log ./log/unit-tests.log
    rc=$?
    if [ $rc -ne 0 ]; then
        cat Testing/Temporary/MemoryChecker.*.log
    fi
    exitOnError $rc "Error executing unit tests, terminating"

fi

#
# Creating coverage information
#

if [ ${BUILD_DOCS} == 1 ]; then
    banner "Coverage"
    lcov --capture --directory . --output-file coverage.info --ignore-errors mismatch,mismatch --ignore-errors gcov,gcov
    lcov --quiet --remove coverage.info '/usr/*' --remove coverage.info '*test*' --output-file coverage.info
    genhtml coverage.info -q --demangle-cpp --output-directory docs/html/coverage
fi
#
# Installation
#

#if [[ "${BUILD_TYPE}" == "Debug" ]]; then
banner "Installation"
cmake --install . --prefix=${PREFIX}
exitOnError $? "Error installing project, terminating"
#fi

#
# Building documentation
#

if [ ${BUILD_DOCS} == 1 ]; then
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
