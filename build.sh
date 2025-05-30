#!/usr/bin/env -S bash -l

function exitOnError() {
    if [ $1 -ne 0 ]; then
        echo $2
        exit 255
    fi
}


SCRIPT_DIR=$(dirname "${BASH_SOURCE[0]}")

echo "Building dt api library from ${SCRIPT_DIR}"

[[ ! -d "build" ]] && mkdir -p build

pushd build

cmake ..
exitOnError $? "Failed to create cmake build files!"

cmake --build .
exitOnError $? "Error building project, terminating"

ctest -T memcheck --output-on-failure -j 10 --output-log ./log/unit-tests.log
rc=$?
if [ $rc -ne 0 ]; then
    cat Testing/Temporary/MemoryChecker.*.log
fi
exitOnError $rc "Error executing unit tests, terminating"

if [[ ! -v ${DEBG} && ${DEBUG} = true ]]; then
   cmake --install . --prefix=${SCRIPT_DIR}/build
else
   cmake --install . --prefix=/usr/local
fi
exitOnError $? "Error installing project, terminating"

pushd ../docs
make html
exitOnError $? "Error creating project documentation, terminating"
popd

popd
