
# CMake-Based Project Using sciplot

## Introduction
This example demonstrates how CMake's command `find_package` can be used to
resolve the dependency of an executable `app` on **sciplot**, a header-only
C++17 library.

The source file `main.cpp` includes the header-file `sciplot/forward.hpp` and
uses a forward mode automatic differentiation algorithm to compute the derivatives of a scalar function.

The `CMakeLists.txt` file uses the command:

```cmake
find_package(sciplot)
```

to find the **sciplot** header files. The executable target `app` is then
linked against the imported target `sciplot::sciplot`:

```cmake
target_link_libraries(app sciplot::sciplot)
```

## Building and Executing the Application
To build the application, do:

```bash
cd cmake-project
mkdir build && cd build
cmake .. -DCMAKE_PREFIX_PATH=/path/to/sciplot/install/dir
make
```

To execute the application, do:

```bash
./app
```

Note: If **sciplot** has been installed system-wide, then the CMake argument
`CMAKE_PREFIX_PATH` should not be needed. Otherwise, you will need to specify
where **sciplot** is installed in your machine. For example:

```cmake
cmake .. -DCMAKE_PREFIX_PATH=$HOME/local
```

assuming directory `$HOME/local` is where **sciplot** was installed to, which should then contain the following directory:

```
$HOME/local/include/sciplot/
```

where the **sciplot** header files are located.
