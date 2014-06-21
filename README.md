# C-Hayai - the C benchmarking framework.

_C-Hayai_ is a C framework for writing benchmarks for pieces of code along the lines of the normal approach for unit testing using frameworks such as [googletest](http://code.google.com/p/googletest/). 
_C-Hayai_ is a port in C of [_hayai_](https://github.com/nickbruun/hayai).

## Building C-Hayai

The source code of _C-Hayai_ must be compiled to provide `libchayai`. Compiling the source code requires `CMake` to be present on the system:

    $ cd C-Hayai
    $ mkdir build
    $ cd build
    $ cmake ..
    $ make

You can now run the sample:

    $ sample/sample
    
This will also build the sample available in the `sample/` directory of the repository.

## Differences between C-Hayai and hayai

Due to some limitations of the C language, each benchmarks needs to be registered in the main function to be used. 
There is two new kind of macros `DECLARE_BENCHMARK` and `REGISTER_BENCHMARK`.
Look at the samples on how to use these new macros.

