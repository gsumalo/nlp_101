# nlp_101

This project is a demo of C++ skills.

## Description

A filter for transforming text containing numbers to its numeric representation
has been developed. 

It contains some code taking advantage of modern C++ (C++11 / C++14 / C++17)
features and Boost C++ libraries (filesystem, program_options and spirit).

Suitable tests based on Google Test Framework are provided.

## Building the project

In order to build the project from the sources, the following tools are
required:
* A recent version of CMake (at least version 3.10.2)
* A C++17-enabled toolchain

Precompiled libraries for the supported toolchain-environment tuples are
provided

### Supported toolchains

The following compilers have been officially tested:
* Linux: GCC 7.3.0
* Microsoft Windows: Visual Studio 2019 (16.6.5)

Other toolchains are likely to be able to build the project, but they were
untested due the scope of this demo

### Supported environments

The project has been officially tested on the following operating systems:
* OpenSUSE 15.1 (64 bits)
* Microsoft Windows 10 (Version 1909, OS Build 18363.959, 64 bits)

32-bit environments are not supported, neither tested.

Other environment are likely to be able to build and run the project, but they
were untested due the scope of this demo.

### Build steps

1. Grab a copy of the source code.
1. __Optional:__  Create an output directory (out-of-tree builds) and go to the 
   output directory
1. Run CMake pointing to the location where the directory source is located.
   For instance, you can do it with `cmake -DCMAKE_BUILD_TYPE=Release source`.
1. Run the build process. For instance, you can do it with `cmake -build .`.   

As a result of a successful build, you will get two binaries (ommiting the .exe
extension for simplicity):
* __app/nlp_101:__  The amazing filter developed for this demo 
* __test/nlp_test:__  The test runner for validation of the filter

## Usage

The filter can be run straight forward. It reads the data provided to its
standard input and outputs the filtered / transformed data to its standard
output. This turns it suitable for streaming.

For instance, you can run the command `echo I have one hundred apples | nlp_101`
and you should expect it outputs `I have 100 apples`

## Testing

Tests based on Google Test Framework were provided.
Just run the  __nlp_test__  binary providing the path to the  __nlp_101__ 
application with the mandatory --app flag.

For instance, assuming both binaries are in the same folder, you can run
`nlp_test --app nlp_101` and it will run all the test cases.
