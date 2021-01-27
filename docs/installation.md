# Installation

{{sciplot}} is a header-only library that needs a C++14-capable compiler.

It has no external dependencies for compiling! The only external runtime dependencies are [gnuplot-palettes] for providing color palettes (automatically handled for you) and a [gnuplot] executable.

Thus, please install [Gnuplot](http://www.gnuplot.info/)!.

Installing {{sciplot}} is easy, since it is a *header-only library*. Follow the steps below.

## Download

Download {{sciplot}} by either git cloning its [GitHub repository][github]:

~~~
git clone https://github.com/sciplot/sciplot
~~~

or by [clicking here][zip] to start the download of a zip file, which
you should extract to a directory of your choice.

## Installation by copying

Assuming the git cloned repository or extracted source code resides in a
directory named `sciplot`, you can now copy the directory `sciplot/sciplot`
to somewhere in your project directory and directly use {{sciplot}}.

This quick and dirty solution should suffice in most cases. If this solution
bothers you, read the next section!

## Installation using CMake

If you have `cmake` installed in your system, you can then install {{sciplot}}
(and also build its tests and examples) as follows:

~~~
mkdir build && cd build
cmake ..
cmake --build . --target install
~~~

!!! attention ""

    We assume above that you are in the root of the source code directory, under
    `sciplot`! The build directory will be created at `sciplot/build`.

The previous installation commands will require administrative rights in most
systems. To install {{sciplot}} locally, use:

~~~
cmake .. -DCMAKE_INSTALL_PREFIX=/some/local/dir
~~~


[github]: https://github.com/sciplot/sciplot
[zip]: https://github.com/sciplot/sciplot/archive/master.zip

## Installation failed. What do I do?

Create a [new issue][issues], and let us know what happened and possibly how we
can improve the installation process of {{sciplot}}.

[issues]: https://github.com/sciplot/sciplot/issues/new
