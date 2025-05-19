# About
Some basic classes and constants for scientific calculations in C++.
This is a header-only library, and therefore it can be used without compiling and linking.
Path of the header file can be specified in the following ways.
* **Compiler option** \
One can add an option when a source file is compiled.
For instance, in the case of GNU C++ compiler in a **Linux/Unix** system, `-I` option can be used to specify the include path to look up.
```
$ g++ foo.cpp -c -I[directory for the SciBaseCXX local repo]/include
```
* **Environmental variable** \
An environmental variable `CPLUS_INCLUDE_PATH` can be used to have a compiler automatically looks up specified directory for header files.
One can use `export` and `setenv` commands for **bash/zsh** and **tcsh/csh** shells, respectivley.
```
$ export CPLUS_INCLUDE_PATH=[directory for the SciBaseCXX local repo]/include:$CPLUS_INCLUDE_PATH
$ setenv CPLUS_INCLUDE_PATH [directory for the SciBaseCXX local repo]/include:$CPLUS_INCLUDE_PATH
```
* **CMake** \
In the case of building with **cmake**, it is also possible to import the library via `FetchContent` from the public repository.
If one has a project `proj_foo`, the following statements can be added in CMakeLists.txt to get the header files available.
```
include(FetchContent)
FetchContent_Declare(
    SciBaseCXX
    GIT_REPOSITORY https://github.com/swryu10/SciBaseCXX.git
    GIT_TAG origin/main
)
FetchContent_MakeAvailable(SciBaseCXX)
target_include_directories(proj_foo PUBLIC ${FETCHCONTENT_BASE_DIR}/scibasecxx-src/include)
```
