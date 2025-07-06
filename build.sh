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
NODOCS_OPT=0
NOMEM_OPT=0
NOTEST_OPT=0
BUILD_TYPE=Debug
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

        --nodocs)
            NODOCS_OPT=1
            shift
            ;;

        --nomem)
            NOMEM_OPT=1
            shift
            ;;

        --notest|--notesting)
            NOTEST_OPT=1
            shift
            ;;

        --release)
            BUILD_TYPE=Release
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

if [ ${NOTEST_OPT} == 0 ]; then

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

if [ ${NODOCS_OPT} == 0 ]; then
    banner "Coverage"
    lcov --capture --directory . --output-file coverage.info --ignore-errors mismatch,mismatch --ignore-errors gcov,gcov
    lcov --quiet --remove coverage.info '/usr/*' --remove coverage.info '*test*' --output-file coverage.info
    genhtml coverage.info -q --demangle-cpp --output-directory docs/html/coverage
fi
#
# Installation
#

banner "Installation"
if [[ ! -v ${DEBG} && ${DEBUG} = true ]]; then
   cmake --install . --prefix=${SCRIPT_DIR}/build
else
   cmake --install . --prefix=/usr/local
fi
exitOnError $? "Error installing project, terminating"

#
# Building documentation
#

if [ ${NODOCS_OPT} == 0 ]; then
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
