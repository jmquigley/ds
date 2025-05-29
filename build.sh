#!/usr/bin/env -S bash -l

SCRIPT_DIR=$(dirname "${BASH_SOURCE[0]}")

echo "Building dt api library from ${SCRIPT_DIR}"

[[ ! -d "build" ]] && mkdir -p build

pushd build

cmake ..
if [ 0 -ne $? ]; then
    echo "Failed to create cmake build files!"
    exit 255
fi

cmake --build .
ctest --output-on-failure -j 10 --output-log ./log/unit-tests.log


if [ ${DEBUG} = false ]; then
   cmake --install . --prefix=/usr/local
fi

popd
