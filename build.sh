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

echo "Building dt api library from ${SCRIPT_DIR}"

[[ ! -d "build" ]] && mkdir -p build

pushd build

if [[ -z "${DEBUG}" ]]; then
    BUILD_TYPE=Release
else
    BUILD_TYPE=Debug
fi
banner ${BUILD_TYPE}


if [ "$1" == "--clean" ]; then
    banner "Cleaning"
    cmake --build . -v --target clean
fi

#
# Building code with CMake
#

banner "Building"

cmake -DCMAKE_BUILD_TYPE=${BUILD_TYPE} ..
exitOnError $? "Failed to create cmake build files!"

cmake --build . -v
exitOnError $? "Error building project, terminating"

#
# Testing
#

banner "Testing"
ctest -T memcheck --output-on-failure -j 10 --output-log ./log/unit-tests.log -T coverage
rc=$?
if [ $rc -ne 0 ]; then
    cat Testing/Temporary/MemoryChecker.*.log
fi
exitOnError $rc "Error executing unit tests, terminating"

#
# Creating coverage information
#

banner "Coverage"
lcov --capture --directory . --output-file coverage.info --ignore-errors mismatch,mismatch --ignore-errors gcov,gcov
lcov --quiet --remove coverage.info '/usr/*' --remove coverage.info '*test*' --output-file coverage.info
genhtml coverage.info -q --demangle-cpp --output-directory docs/html/coverage

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

banner "Documentation"
pushd ../docs
make html
exitOnError $? "Error creating project documentation, terminating"
popd

popd
