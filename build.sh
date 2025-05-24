#!/usr/bin/env -S bash -l

echo "Building dt api library"

[[ ! -d "build" ]] && mkdir -p build

pushd build

cmake ..
if [ 0 -ne $? ]; then
    echo "Failed to create cmake build files!"
    exit 255
fi

cmake --build .
ctest --output-on-failure -j 10 --output-log ./log/unit-tests.log

popd
