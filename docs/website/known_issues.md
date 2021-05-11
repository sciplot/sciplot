# Known issues

## I get compiler errors when compiling for Windows

Make sure you include `windows.h` **AFTER** including {{sciplot}}:

```c++
#include <sciplot/sciplot.hpp> // FIRST THINGS FIRST!
#include <windows.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int CmdShow)
{
    //...
}
```

See issue [#70](https://github.com/sciplot/sciplot/issues/70).

## I have problems setting a grid for my plot

This might be a [bug](https://sourceforge.net/p/gnuplot/bugs/2414/) in some versions of gnuplot. See issue [#73](https://github.com/sciplot/sciplot/issues/73).

## I have a different issue

Make sure you check already [closed issues](https://github.com/sciplot/sciplot/issues?q=is%3Aissue+is%3Aclosed) too.
