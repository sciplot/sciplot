# Installation

{{sciplot}} is a header-only library that needs a C++17-capable compiler.

It has no external dependencies for compiling! The only external runtime dependencies are [gnuplot-palettes] for providing color palettes (automatically handled for you) and a [gnuplot] executable.

Thus, please install [Gnuplot](http://www.gnuplot.info/)!.

Installing {{sciplot}} is easy, since it is a *header-only library*. Follow the steps below.

## Download

Download {{sciplot}} by git cloning its [GitHub repository][github]:

~~~shell
git clone https://github.com/sciplot/sciplot --recursive
~~~

## Installation by copying

Assuming the git cloned repository or extracted source code resides in a
directory named `sciplot`, you can now copy the directory `sciplot/sciplot`
to somewhere in your project directory and directly use {{sciplot}}.

This quick and dirty solution should suffice in most cases. If this solution
bothers you, read the next section!

## Installation using CMake

If you have `cmake` installed in your system, you can then install {{sciplot}}
(and also build its tests and examples) as follows:

~~~shell
mkdir build && cd build
cmake ..
cmake --build . --target install
~~~

!!! attention ""

    We assume above that you are in the root of the source code directory, under
    `sciplot`! The build directory will be created at `sciplot/build`.

The previous installation commands will require administrative rights in most
systems. To install {{sciplot}} locally, use:

~~~shell
cmake .. -DCMAKE_INSTALL_PREFIX=/some/local/dir
~~~

[github]: https://github.com/sciplot/sciplot
[zip]: https://github.com/sciplot/sciplot/archive/master.zip

## Installation failed. What do I do?

Check the [known issues](known_issues.md) and if your problem persists, create a [new issue][issues], and let us know what happened and possibly how we can improve the installation process of {{sciplot}}.

[issues]: https://github.com/sciplot/sciplot/issues/new
