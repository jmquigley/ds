# ds

> Data structures and algorithms implemented in C++

**This repo is a work in progress**

A user implementation of some basic data structures including:

- BitFlags
- BinaryTree
- Buffer
- Deque
- GeneralTree
- List
- LRUCache
- OrderedSet
- Path
- PriorityQueue
- Queue
- RingBuffer
- SortedList
- Stack
- ThreadPool

## Building

The library was developed under Ubuntu linux in a Docker container.  It requires the following libraries and tools to be installed to build:

- build-essential
- llvm-21 (clang++, lldb)
- valgrind (3.25+, needed for clang dwarf-5)
- cmake (3.30+)
- figlet

These tools are only needed if the documenation will be built:

- doxygen
- graphviz
- python3
- miniconda
- jq

The library uses [CMake](https://cmake.org/) (version 3.31+) to build the library.  A bash wrapper script, named `build.sh`, is available to create a single command build.  This is a wrapper around the cmake commands.  To build the code using BASH run:

```bash
./build.sh
```

This will create the release version of the library.  To build unit tests and create Doxygen documentation use:

```bash
./build.sh --debug
```

To build all unit tests and also perform a memory test (valgrind) use:

```bash
./build.sh --debug --memtest
```

This build process will take a few minutes to run with leak detection on.
